#include "Menu.h"
//bl
#include <iostream>
#include <iomanip>



ofstream myfile;

using namespace std;

void Menu::chart(const char* Funktion ,  int Eingabe)
{
	cout << "| " << std::setw(25) << Funktion << " | "
		<< std::setw(5) << Eingabe << " | " << ::endl;

}
void Menu::ui()
{
	int a;
	system("cls");
	Menu::chart("Set layout", 1);
	Menu::chart("Set lerning-values", 2);
	Menu::chart("Set number of repititions", 3);
	Menu::chart("Set own input", 4);
	Menu::chart("Create NeuralNet", 5);
	Menu::chart("Sart learning", 6);
	Menu::chart("exit", 7);
	cin >> a ;
	switch (a) {
	case 1: setLayout();
		break;
	case 2: setLearningVals();
		break;
	case 3: setReps();
		break;
	case 4: setOwnInput();
		break;
	case 5: makeNeuralNet();
		break;
	case 6: startLearning();
		break;
	case 7: m_exit=1;
		break;
	}


}
void Menu::setLayout()
{
	if (m_layout.size() > 0) {
		m_layout.clear();
	}
	unsigned input, hidden, output, numhidden;
	cout << "Number of Input Neurons:" << endl;
	cin >> input;
	m_layout.push_back(input);
	cout << "Number of Hidden Layers:" << endl;
	cin >> numhidden;
	for (unsigned i = 0; i < numhidden; ++i) {
		cout << "Number of Hidden Neurons:" << endl;
		cin >> hidden;
		m_layout.push_back(hidden);
	}
	cout << "Number of Output Neurons:" << endl;
	cin >> output;
	m_layout.push_back(output);
}


void Menu::setOwnInput()
{
	double x;
	if (m_ownInput.size() > 0) {
		m_ownInput.clear();
	}
	for (unsigned n = 0; n < m_layout[0]; n++) 
	{
		cout << "Input " << n+1 << endl;
		cin >> x;
		m_ownInput.push_back(x);
		
		
	}

	Nets[0].feedForward(m_ownInput);
	vector<double> ergebnis;
	Nets[0].getResults(ergebnis);
	system("cls");
	for (int x = 0; x<ergebnis.size(); x++) {
		if ((int)round(ergebnis[x]) == 1) cout << x << endl;
		
	}
	Menu::chart("Weiter", 1);
	Menu::chart("Ende", 0);
	int a;
	cin >>  a;
	switch (a) {
	case 1: m_exit = 0;
		break;
	case 2: m_exit = 1;
		break;
	}

}

void Menu::setReps()
{
	cout << "How many repetitions shall the net do to learn the dataset?" << endl;
	cin >> m_reps;
}

void Menu::setLearningVals()
{
	double x;
	if (m_learningVals.size() > 0) {
		m_learningVals.clear();
	}
	cout << "learning rate:" << endl;
	cin >> x;
	m_learningVals.push_back(x);
	cout << "alpha:" << endl;
	cin >> x;
	m_learningVals.push_back(x);
}

Menu::Menu()
{
	m_layout.push_back(4);
	m_layout.push_back(15);
	m_layout.push_back(4);
	m_reps = 50000;
	m_startLearning = 0;
	m_learningVals.push_back(0.5);
	m_learningVals.push_back(0.0005);
}

Menu::~Menu()
{
}


void Menu::startLearning()
{
	if (m_startLearning == 1) {
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		myfile.open("example.txt");
		vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");

		int stepcounter = 0, fehlercounter = 0;
		for (unsigned j = 0; j < m_reps; ++j) {


			vector<double> inputWerte;
			
			
			
			
			unsigned x = rand() % sampleData.size();

			for (unsigned int n = 0; n < (m_layout[0]); ++n)
			{
				inputWerte.push_back(sampleData[x][n]);
			}

			vector<double> zielWerte;
			for (unsigned y = 0; y < m_layout.back(); ++y)
				if (y == ((sampleData[x][4]))) {
					zielWerte.push_back(1);
				}
				else zielWerte.push_back(0);
				++stepcounter;

				Nets[0].feedForward(inputWerte);

				Nets[0].backProp(zielWerte);

				vector<double> ergebnis;
				Nets[0].getResults(ergebnis);

				
				if (zielWerte[1] != (int)round(ergebnis[1]) || zielWerte[2] != (int)round(ergebnis[2]) || zielWerte[3] != (int)round(ergebnis[3])) {
					myfile << "Step " << stepcounter << "Input : " << inputWerte[0] << " " << inputWerte[1] << " " << inputWerte[2] << " " << inputWerte[3] << "Ziel : " /*<< zielWerte[0] << " "*/ << zielWerte[1] << " " << zielWerte[2] << " " << zielWerte[3] << " " << "Ergebnis : " << /*ergebnis[0] <<*/ " " << (int)round(ergebnis[1]) << " " << (int)round(ergebnis[2]) << " " << (int)round(ergebnis[3]) << endl;

					fehlercounter++;
				}
				
				if (stepcounter % 1000 == 0) {
					system("cls");
					cout << "Step: "<< stepcounter << endl;
					cout <<"Genauigkeit: "<< 100-(fehlercounter / 10) <<"%"<< endl;
					fehlercounter = 0;

				}








		}
		myfile.close();
	}
	else cout << "Bitte zunächst das Neuronale Netz erstellen!" << endl;
}

void Menu::makeNeuralNet()
{
	Nets.clear();
	m_startLearning = 1;
	Nets.push_back(NeuralNet(m_layout, m_learningVals));
}
