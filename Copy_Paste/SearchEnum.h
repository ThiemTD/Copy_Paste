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
};

