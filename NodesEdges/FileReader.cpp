#include "FileReader.h"

FileReader::FileReader()
{

}

vector<vector<double>> FileReader::readData(string fileName) {

	vector < vector <double> > daten;

	ifstream myFile(fileName);

	if (myFile.is_open()) {



		while (!myFile.eof()) {

			string aLine;

			getline(myFile, aLine);

			int kommaPosition;

			vector <double> temp;

			while ((kommaPosition = aLine.find(',', 0)) > 0) {

				//cout << aLine << comma_pos << endl;

				temp.push_back(atof(aLine.substr(0, kommaPosition).c_str()));
				aLine = aLine.substr(kommaPosition + 1, aLine.length() - 1);

			}

			temp.push_back(atof(aLine.c_str()));

			daten.push_back(temp);


		}
		cout << "Datei erfolgreich eingelesen!\n";
	}
	else {

		cout << "Fehler beim Einlesen!\n";

	}

	return daten;
}


FileReader::~FileReader()
{
}