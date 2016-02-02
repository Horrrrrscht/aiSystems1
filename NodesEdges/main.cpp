// 53:02 bbbgk



#include <iostream>

#include "NeuralNet.h"
#include "FileReader.h"
#include "Menu.h"

int main()
{
	Menu menu;
	menu.ui();
	ofstream myfile;
	myfile.open("example.txt");

	/*vector<unsigned> layout;
	layout.push_back(4);
	layout.push_back(25);
	layout.push_back(1);*/
	NeuralNet myNet(menu.getLayout());

	vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");
	
	int stepcounter = 0;
	for (unsigned j = 0; j < menu.getReps(); ++j) {

		/*for (unsigned n = 0; n < sampleData.size() - 1; ++n) {*/

			vector<double> inputWerte;
			unsigned x = rand() % sampleData.size();
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








