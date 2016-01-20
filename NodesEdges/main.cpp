#include <iostream>
#include "FileReader.h"
#include "NeuralNet.h"

int main()
{


	///////////////////////////////////////////////////////////////////

	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Daten werden eingelesen\n";
	

	///////////////////////////////////////////////////////////////////
	
	vector<unsigned> layout;
	layout.push_back(4);
	layout.push_back(10);
	layout.push_back(1);
	NeuralNet myNet(layout);

 	vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");

	cout << "Vektor erstellt" << endl;

	int stepcounter = 0;
	for (unsigned j = 0; j < 100; ++j) {

		for (unsigned n = 0; n < sampleData.size() - 1; ++n) {

			// cout << stepcounter << endl;
			//for (unsigned n = 0; n < 5; ++n) {

			vector<double> inputWerte;
			inputWerte.push_back(sampleData[n][0]);
			inputWerte.push_back(sampleData[n][1]);
			inputWerte.push_back(sampleData[n][2]);
			inputWerte.push_back(sampleData[n][3]);
			vector<double> zielWerte;
			zielWerte.push_back(sampleData[n][4]);
			++stepcounter;
			//cout << "------------------------------------------------------" << endl;
			//cout << "Step " << stepcounter << endl;
			
			myNet.feedForward(inputWerte);

			myNet.backProp(zielWerte);

			vector<double> ergebnis;
			myNet.getResults(ergebnis);

			myfile << "Step " << stepcounter << "Input : " << sampleData[n][0] << " " << sampleData[n][1] << " " << sampleData[n][2] << " " << sampleData[n][3] << "Ziel : " << sampleData[n][4] << " " << "Ergebnis : " << ergebnis[0] << endl;
			
			
				
			
			
			
			//cout << "Target Value : " << sampleData[n][2] << endl;
			//cout << "Output Value : " << resultVals[0] << endl;


			//cout << "------------------------------------------------------" << endl;




			//for (unsigned k = 0; k < sampleData[n].size(); ++k) {

			//	cout << sampleData[n][k] ;
			//}

			//cout << endl;
		}
	}

	///////////////////////////////////////////////////////////////////

	



	//





	myfile.close();
	// vector<double> resultVals;
	// myNet.getResults(resultVals);

	 




	return 0;
}



