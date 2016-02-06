#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//der FileReader ist für das Einlesen einer csv-Datei zuständig

class FileReader
{
public:
	FileReader();

	static vector<vector<double>> readData(string fileName);

	~FileReader();

private:

};





#endif
