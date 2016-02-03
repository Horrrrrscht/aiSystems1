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

	Menu::chart("Set layout", 1);
	Menu::chart("Set lerning-values", 2);
	Menu::chart("Set number of repititions", 3);
	Menu::chart("Set own input", 4);
	Menu::chart("Start learning process", 5);
	cin >> a ;
	switch (a) {
	case 4: setOwnInput();
		break;
	case 3: setReps();
		break;
	case 1: setLayout();
		break;
	case 2: setLearningVals();
		break;
	case 5: m_startLearning = 1;
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
	for (unsigned n = 1; n < m_layout[0]; n++) 
	{
		cout << "Input " << n << endl;
		cin >> x;
		m_ownInput.push_back(x);
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
	m_layout.push_back(15);
	m_layout.push_back(15);
	m_layout.push_back(4);
	m_reps = 1000;
	m_startLearning = 0;
	m_learningVals.push_back(0.005);
	m_learningVals.push_back(0.0005);
	Nets.push_back(NeuralNet(m_layout, m_learningVals));
}

Menu::~Menu()
{
}


void Menu::startLearning()
{

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

			Nets[1].feedForward(inputWerte);

			Nets[1].backProp(zielWerte);

			vector<double> ergebnis;
			Nets[1].getResults(ergebnis);

			myfile << "Step " << stepcounter << "Input : " << inputWerte[0] << " " << inputWerte[1] << " " << inputWerte[2] << " " << inputWerte[3] << "Ziel : " /*<< zielWerte[0] << " "*/ << zielWerte[1] << " " << zielWerte[2] << " " << zielWerte[3] << " " << "Ergebnis : " << /*ergebnis[0] <<*/ " " << (int)round(ergebnis[1]) << " " << (int)round(ergebnis[2]) << " " << (int)round(ergebnis[3]) << endl;

			if (zielWerte[1] != (int)round(ergebnis[1]) || zielWerte[2] != (int)round(ergebnis[2]) || zielWerte[3] != (int)round(ergebnis[3])) fehlercounter++;
			if (stepcounter % 1000 == 0) {
				system("cls");
				cout << fehlercounter / 10 << endl;
				fehlercounter = 0;

			}







			
	}
	myfile.close();
}