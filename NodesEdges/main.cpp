// 53:02 bbbgk



#include <iostream>

#include "NeuralNet.h"
#include "FileReader.h"

int main()
{

	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Daten werden eingelesen\n";

	vector<unsigned> layout;
	layout.push_back(4);
	layout.push_back(15);
	layout.push_back(15);
	layout.push_back(1);
	NeuralNet myNet(layout);

	vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");
	cout << sampleData.size() << endl;
	unsigned stepcounter = 0;
	double fail=1.0 , step=0.0;
	unsigned x , a ;
	cout << "How many Steps would you like me to do?" << endl;
	cin >> a;
	for (unsigned j = 0; j < a; ++j) {
		//for (unsigned n = 0; n < sampleData.size() - 1; ++n) {
		++step;
		if (step > 500) {

			system("cls");
			cout << fail / step <<"\n" << stepcounter << endl;
			fail = 0;
			step = 0;
		}

			vector<double> inputWerte;
			x = rand() % sampleData.size() ;
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

			if (/*stepcounter>10000 && */stepcounter % 1 == 0) {
				if (sqrt((ergebnis[0] - sampleData[x][4])*(ergebnis[0] - sampleData[x][4])) /*- sqrt((sampleData[x][4])*(sampleData[x][4]))*/ < 0.1) {
					//cout << "OKAY"/*------" << sqrt((ergebnis[0])*(ergebnis[0])) - sqrt((sampleData[x][4])*(sampleData[x][4]))*/ << endl;

					
				}
				else
					++fail;
					//cout /*<< sampleData[x][4]*/ << (fail / stepcounter) /*--------------" << sqrt((ergebnis[0])*(ergebnis[0])) - sqrt((sampleData[x][4])*(sampleData[x][4])) << ------FAIL                     X"*/ <<   endl;
			}
		}
	//}

	myfile.close();


	//myNet.printNet();

	return 0;
}








