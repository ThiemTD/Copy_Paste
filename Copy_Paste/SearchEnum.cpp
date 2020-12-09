#include "SearchEnum.h"


SearchEnum::SearchEnum()
{
	Initialize();
	GetLineFromInFiles();
	GetFIDList(sampleLine);
	WriteToFile(targetFile);
}

SearchEnum::~SearchEnum()
{
	sampleLine.clear();
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

	inSampleFile.close();
	inSourceFile.close();
}

//Get FID list from source code
void SearchEnum::GetFIDList(SVECT vt_line)
{
	string fid;
	int startPosition;
	int endPosition;
	for (int i = 0; i < vt_line.size(); i++)
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

void SearchEnum::WriteToFile(string fileName)
{
	fstream outFile;
	outFile.open(fileName, ios::out);
	cout << "Write data into file: " << fileName << endl;
	
	outFile << "FID\t\t\t\tFID_NAME" << endl;
	outFile << "===\t\t\t\t========" << endl;
	ISMAP mapOut;
	for (int i = 0; i < fidList.size(); i++)
	{
		for (ISMAP::iterator it = m_mapEnum.begin(); it != m_mapEnum.end(); ++it)
		{
			if (fidList[i] == it->second)
			{
				mapOut[it->first] = it->second;
			}
		}
	}

	for (ISMAP::iterator it = mapOut.begin(); it != mapOut.end(); ++it)
	{
		outFile << it->first << "\t\t\t\t" << it->second << endl;
	}
	outFile.close();
}