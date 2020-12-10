#include "SearchEnum.h"


SearchEnum::SearchEnum()
{
	Initialize();
	ReadListFileInFolder(inSample);
	ProcessWriteFile();
}

SearchEnum::~SearchEnum()
{
	fidList.clear();
	m_mapEnum.clear();
}

void SearchEnum::Initialize()
{
	char temp[256];
	GetPrivateProfileString("Settings", "StartFilter", "", temp, sizeof(temp), ".\\CPConfig.ini");
	startFilter = temp;
	GetPrivateProfileString("Settings", "EndFilter", "", temp, sizeof(temp), ".\\CPConfig.ini");
	endFilter = temp;
	GetPrivateProfileString("Settings", "InputFolder", "", temp, sizeof(temp), ".\\CPConfig.ini");
	inSample = temp;
	GetPrivateProfileString("Settings", "InSourceFile", "", temp, sizeof(temp), ".\\CPConfig.ini");
	inSource = temp;
	GetPrivateProfileString("Settings", "OutputFolder", "", temp, sizeof(temp), ".\\CPConfig.ini");
	targetFile = temp;
	SetMapEnum();
}

void SearchEnum::ReadListFileInFolder(string inputFolder)
{
	string pattern(inputFolder);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			string fileName = data.cFileName;
			int pos = fileName.find(".");
			string name;
			string type;
			name = fileName.substr(0, pos);
			type = fileName.substr(pos + 1);
			if (name.empty()) continue;
			m_listFile.push_back(make_pair(name, type));
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

void SearchEnum::SetMapEnum()
{
	int key;
	string value;
	string line;
	fstream inSourceFile;
	inSourceFile.open(inSource, ios::in);
	while (getline(inSourceFile, line))
	{
		if (line.find(startFilter) != -1)
		{
			sourceLine << line;
			sourceLine >> key >> value;
			m_mapEnum[key] = value;
			sourceLine.str("");
		}
	}
}

SVECT SearchEnum::ReadDataFile(string fileName)
{
	string line;
	fstream inFile;
	SVECT vt_line;

	inFile.open(inSample + "\\" + fileName, ios::in);
	if (!inFile) return vt_line;
	while (getline(inFile, line))
	{
		if (!line.empty())
		{
			vt_line.push_back(line);
		}
	}
	inFile.close();
	return vt_line;
}

//Get FID list from source code
void SearchEnum::GetFIDList(SVECT vt_line)
{
	string fid;
	int startPosition;
	int endPosition;

	for (int i = 0; i < (int)vt_line.size(); i++)
	{
		startPosition = vt_line[i].find(startFilter);
		endPosition = vt_line[i].find(endFilter);
		if (startPosition != -1 && endPosition != -1)
		{
			fid = vt_line[i].substr(startPosition, endPosition - startPosition);
			if (fid.find(startFilter) != -1)
			{
				fidList.push_back(fid);
			}
		}
	}
}
void SearchEnum::ProcessWriteFile()
{
	for (int i = 0; i < (int)m_listFile.size(); i++)
	{
		string filePath = m_listFile[i].first + "." + m_listFile[i].second;
		SVECT vt_line = ReadDataFile(filePath);
		GetFIDList(vt_line);
		WriteToFile(m_listFile[i].first);
	}
}

void SearchEnum::WriteToFile(string fileName)
{
	if (fileName.empty() || fidList.empty())
	{
		return;
	}
	fstream outFile;
	fileName = targetFile + fileName + ".csv";

	outFile.open(fileName, ios::out);
	cout << "Write data into file: " << fileName << endl;
	
	outFile << "FID\t\t\t\tFID_NAME" << endl;
	outFile << "===\t\t\t\t========" << endl;
	ISMAP mapOut;
	for (int i = 0; i < (int)fidList.size(); i++)
	{
		for (ISMAP::iterator it = m_mapEnum.begin(); it != m_mapEnum.end(); ++it)
		{
			if (fidList[i] == it->second)
			{
				mapOut[it->first] = it->second;
			}
		}
	}
	//Writr data to output file.
	for (ISMAP::iterator it = mapOut.begin(); it != mapOut.end(); ++it)
	{
		outFile << it->first << "\t\t\t\t" << it->second << endl;
	}
	fidList.clear();
	outFile.close();
}