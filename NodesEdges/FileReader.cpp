#include "FileReader.h"


FileReader::FileReader()
{
	
}

vector<vector<double>> FileReader::readData(string fileName) {

	vector < vector <double> > data;

	ifstream myFile(fileName);

	if (myFile.is_open()) {

		cout << "Successfully opened the file\n";

		while (!myFile.eof()) {

			string aLine;

			getline(myFile, aLine);

			int comma_pos;

			vector <double> temp;
				
			while ((comma_pos = aLine.find(',', 0)) > 0) {
			
				//cout << aLine << comma_pos << endl;

				temp.push_back(atof(aLine.substr(0, comma_pos).c_str()));
				aLine = aLine.substr(comma_pos + 1, aLine.length() - 1);

			 } 
			
			 temp.push_back(atof(aLine.c_str()));

		/*	string xst, yst, ost, substring;

			xst = aLine.substr(0, comma_pos);
			substring = aLine.substr(comma_pos + 1, aLine.length() - 1);

			comma_pos = substring.find(',', 0);
			yst = substring.substr(0, comma_pos);

			substring = substring.substr(comma_pos + 1, substring.length() - 1);

			comma_pos = substring.find(',', 0);
			ost = substring.substr(0, comma_pos);		

			//cout << xst << yst << endl;

			double xt, yt, ot;

			xt = atof(xst.c_str());
			yt = atof(yst.c_str());
			ot = atof(ost.c_str());

			vector <double> temp;

			temp.push_back(xt);
			temp.push_back(yt);
			temp.push_back(ot);*/

			data.push_back(temp);


		}

	}
	else {

		cout << "Unable to open the file!\n";

	}
	
	return data;
}


FileReader::~FileReader()
{
}