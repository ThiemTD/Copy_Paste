#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
using namespace std;

typedef map<int, string> ISMAP;
typedef vector<string> SVECT;
typedef vector<pair<string, string>> PSSVECT;

class SearchEnum
{
public:
	SearchEnum();
	~SearchEnum();

	string startFilter;
	string endFilter;
	string inSample;
	string inSource;
	string targetFile;

	SVECT fidList;
	stringstream sourceLine;
	PSSVECT m_listFile;
	ISMAP m_mapEnum;
	
	void Initialize();
	void GetFIDList(SVECT line);
	void ProcessWriteFile();
	SVECT ReadDataFile(string fileName);
	void ReadListFileInFolder(string inputFolder);
	void SetMapEnum();
	void WriteToFile(string fileName);
};

