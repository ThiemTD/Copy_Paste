#include "SearchEnum.h"


SearchEnum::SearchEnum()
{
	Initialize();
<<<<<<< HEAD
	ReadListFileInFolder(inSample);
	ProcessWriteFile();
=======
	GetLineFromInFiles();
	GetFIDList(sampleLine);
	WriteToFile(targetFile);
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
}

SearchEnum::~SearchEnum()
{
<<<<<<< HEAD
=======
	sampleLine.clear();
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
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
<<<<<<< HEAD
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
	ifstream inSourceFile;
=======
	GetPrivateProfileString("Settings", "InSample", "", temp, sizeof(temp), ".\\CPConfig.ini");
	inSample = temp;
	GetPrivateProfileString("Settings", "InSource", "", temp, sizeof(temp), ".\\CPConfig.ini");
	inSource = temp;
	GetPrivateProfileString("Settings", "TargetFile", "", temp, sizeof(temp), ".\\CPConfig.ini");
	targetFile = temp;
}

void SearchEnum::GetLineFromInFiles()
{	
	string line;
	ifstream inSampleFile, inSourceFile;
	inSampleFile.open(inSample, ios::in);

	while (getline(inSampleFile, line))
	{
		if (line.find(startFilter) != -1)
		{
			sampleLine.push_back(line);
		}
	}

	int key;
	string value;
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
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
<<<<<<< HEAD
	inSourceFile.close();
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
=======

	inSampleFile.close();
	inSourceFile.close();
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
}

//Get FID list from source code
void SearchEnum::GetFIDList(SVECT vt_line)
{
	string fid;
	int startPosition;
	int endPosition;
<<<<<<< HEAD
	for (int i = 0; i < (int)vt_line.size(); i++)
=======
	for (int i = 0; i < vt_line.size(); i++)
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
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

<<<<<<< HEAD
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
=======
void SearchEnum::WriteToFile(string fileName)
{
	fstream outFile;
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
	outFile.open(fileName, ios::out);
	cout << "Write data into file: " << fileName << endl;
	
	outFile << "FID\t\t\t\tFID_NAME" << endl;
	outFile << "===\t\t\t\t========" << endl;
	ISMAP mapOut;
<<<<<<< HEAD
	for (int i = 0; i < (int)fidList.size(); i++)
=======
	for (int i = 0; i < fidList.size(); i++)
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
	{
		for (ISMAP::iterator it = m_mapEnum.begin(); it != m_mapEnum.end(); ++it)
		{
			if (fidList[i] == it->second)
			{
				mapOut[it->first] = it->second;
			}
		}
	}
<<<<<<< HEAD
	//Writr data to output file.
=======

>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
	for (ISMAP::iterator it = mapOut.begin(); it != mapOut.end(); ++it)
	{
		outFile << it->first << "\t\t\t\t" << it->second << endl;
	}
<<<<<<< HEAD
	fidList.clear();
=======
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
	outFile.close();
}