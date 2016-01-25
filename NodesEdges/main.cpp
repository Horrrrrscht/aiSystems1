// 53:02 bbbgk



#include <iostream>

#include "NeuralNet.h"
#include "FileReader.h"
#include "Menu.h"

int main()
{
	Menu menu;

	while (menu.go() != 1) { menu.ui(); }
	
	ofstream myfile;

	myfile.open("example.txt");


	NeuralNet myNet(menu.getLayout(), menu.getLearningVals());


	vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");
	
	int stepcounter = 0;
	for (unsigned j = 0; j < menu.getReps(); ++j) {


			vector<double> inputWerte;
			unsigned x = rand() % sampleData.size();

		/*	for (unsigned int n = 0; n < (menu.getLayout()[0]); ++n)
			{
				inputWerte.push_back(sampleData[x][n]);
			}*/

			inputWerte.push_back(sampleData[x][0]);
			inputWerte.push_back(sampleData[x][1]);
			inputWerte.push_back(sampleData[x][2]);
			inputWerte.push_back(sampleData[x][3]);
			vector<double> zielWerte;
			zielWerte.push_back(sampleData[x][4]);
			++stepcounter;

			myNet.feedForward(inputWerte);

			myNet.backProp(zielWerte);

			vector<double> ergebnis;
			myNet.getResults(ergebnis);

			myfile << "Step " << stepcounter << "Input : " << sampleData[x][0] << " " << sampleData[x][1] << " " << sampleData[x][2] << " " << sampleData[x][3] << "Ziel : " << sampleData[x][4] << " " << "Ergebnis : " << ergebnis[0] << endl;




			
		//}
	}

	myfile.close();


	//myNet.printNet();

	return 0;
}








