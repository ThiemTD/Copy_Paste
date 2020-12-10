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
<<<<<<< HEAD
typedef vector<pair<string, string>> PSSVECT;
=======
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96

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

<<<<<<< HEAD
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
=======
	SVECT sampleLine;
	SVECT fidList;
	stringstream sourceLine;
	vector<pair<string, string>> m_listFile;
	ISMAP m_mapEnum;
	
	void Initialize();
	void GetLineFromInFiles();
	void GetFIDList(vector<string> line);
	void SearchDataFromSource(string line);
	void WriteToFile(string output);
>>>>>>> 45062c4d20dde0b0c6124a8c2b904e3a945f1f96
};

