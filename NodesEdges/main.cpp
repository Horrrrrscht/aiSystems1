


#include <iostream>

#include "NeuralNet.h"
#include "FileReader.h"
#include "Menu.h"

int main()
{
	Menu menu;
	//NeuralNet myNet(menu.getLayout(), menu.getLearningVals());
	while (menu.exit() != 1) { menu.ui(); }
	
//	ofstream myfile;
//
//	myfile.open("example.txt");
//
//
////	NeuralNet myNet(menu.getLayout(), menu.getLearningVals());
//
//
//	vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");
//	
//	int stepcounter = 0 , fehlercounter=0;
//	for (unsigned j = 0; j < menu.getReps(); ++j) {
//
//
//			vector<double> inputWerte;
//			unsigned x = rand() % sampleData.size();
//
//			for (unsigned int n = 0; n < (menu.getLayout()[0]); ++n)
//			{
//				inputWerte.push_back(sampleData[x][n]);
//			}
//
//			vector<double> zielWerte;
//			for (unsigned y = 0; y < menu.getLayout().back(); ++y)
//				if (y == ((sampleData[x][4]) )) {
//					zielWerte.push_back(1);
//				}
//				else zielWerte.push_back(0);
//			++stepcounter;
//
//			myNet.feedForward(inputWerte);
//
//			myNet.backProp(zielWerte);
//
//			vector<double> ergebnis;
//			myNet.getResults(ergebnis);
//
//			myfile << "Step " << stepcounter << "Input : " << inputWerte[0] << " " << inputWerte[1] << " " << inputWerte[2] << " " << inputWerte[3] << "Ziel : " /*<< zielWerte[0] << " "*/ << zielWerte[1] << " " << zielWerte[2] << " " << zielWerte[3] << " " << "Ergebnis : " << /*ergebnis[0] <<*/ " " << (int)round(ergebnis[1]) << " " << (int)round(ergebnis[2]) << " " << (int)round(ergebnis[3]) << endl;
//
//			if (zielWerte[1] != (int)round(ergebnis[1]) || zielWerte[2] != (int)round(ergebnis[2]) || zielWerte[3] != (int)round(ergebnis[3])) fehlercounter++;
//			if (stepcounter % 1000 == 0) {
//				system("cls");
//				cout << fehlercounter/10 << endl;
//				fehlercounter = 0;
//
//			}
//
//
//
//
//
//
//			
//		//}
//	}
//
//	myfile.close();
//
//
//	myNet.printNet();

	return 0;
}








