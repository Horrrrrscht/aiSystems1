#include "Menu.h"
//bl
#include <iostream>
#include <iomanip>

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
	m_layout.push_back(10);
	m_layout.push_back(1);
	m_reps = 1;
	m_startLearning = 0;
	m_learningVals.push_back(1);
	m_learningVals.push_back(1);
}

Menu::~Menu()
{
}