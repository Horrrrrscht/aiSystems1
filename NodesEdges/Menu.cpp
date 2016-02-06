#include "Menu.h"
//bl
#include <iostream>
#include <iomanip>
#include <conio.h>



ofstream myfile;

using namespace std;

void Menu::chart(const char* Funktion ,  double Eingabe)											//Festelgung des Layouts des Menüs
{
	cout << "| " << std::setw(35) << Funktion << " | "
		<< std::setw(9) << Eingabe << " | " << ::endl;

}
void Menu::chart2(const char* Funktion, unsigned Eingabe, unsigned Eingabe2)						//Festelgung des Layouts des Menüs
{
	cout << "| " << std::setw(32) << Funktion <<" "<< setw(2) << Eingabe<< " | "
		<< std::setw(9) << Eingabe2 << " | " << ::endl;
}
void Menu::ui()																						//Menü mit Abfrage
{
	int a;
	system("cls");
	Menu::chart("Set layout", 1);
	Menu::chart("Set lerning-values", 2);
	Menu::chart("Set number of repititions", 3);
	Menu::chart("Set own input", 4);
	Menu::chart("Create NeuralNet", 5);
	Menu::chart("Sart learning", 6);
	Menu::chart("Print Net", 7);
	Menu::chart("exit", 8);
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
	case 7: printNet();
		break;
	case 8: m_exit = 1;
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


void Menu::setOwnInput()														//Der Vektor m_owninputs wird mit auf der Konsole eingegeben Double-Werten gefüllt
{
	

		double x;
		if (m_ownInput.size() > 0) {
			m_ownInput.clear();
		}
		cout << "Sepal Length in cm" << endl;
		cin >> x;
		m_ownInput.push_back(x);
		cout << "Sepal Width in cm" << endl;
		cin >> x;
		m_ownInput.push_back(x);
		cout << "Petal Length in cm" << endl;
		cin >> x;
		m_ownInput.push_back(x);
		cout << "Petal Width in cm" << endl;
		cin >> x;
		m_ownInput.push_back(x);


		//for (unsigned n = 0; n < m_layout[0]; n++)								//je nachdem wie groß die Input-Layer ist, werden Inputs abgefragt
		//{
		//	cout << "Input " << n + 1 << endl;
		//	cin >> x;
		//	m_ownInput.push_back(x);


		//}

		Nets[0].feedForward(m_ownInput);										//der Vector mit den Eingabewerten wird an die feedforward funktion des Neuralen Netzwerkes übergeben
		vector<double> ergebnis;
		Nets[0].getResults(ergebnis);
		system("cls");
		
		for (unsigned x = 0; x < ergebnis.size(); x++) {
			if ((int)round(ergebnis[x]) == 1) {
				//cout << "Dies ist mit " << m_precision << "% Wahrscheinlichkeit das Ergebnis Ihrer Eingabe: " << endl;
				cout << "Dies ist mit " << m_precision << "% Wahrscheinlichkeit die folgende Blume: " << endl;
				//cout << x+1 << endl;												//Das vom neuralen Netz bestimmte Ergebnis wird in einen Wert umgewandelt und ausgegeben
				
				
				switch (x + 1) {
				case 1: cout << "Iris Setosa" << endl;
					break;
				case 2: cout << "Iris Versicolour" << endl;
					break;
				case 3: cout << "Iris Virginica" << endl;
					break;				
				}

			}
		}
		cout << "Press any key to continue..." << endl;
		while (!kbhit());
	
		
}

void Menu::setReps()															//Die Anzahl der Schritte, die das neuronale Netz zum lernen durchführen soll, wird festgelegt
{
	cout << "How many repetitions shall the net do to learn the dataset?" << endl;
	cin >> m_reps;
}

void Menu::setLearningVals()													//Festlegung der Stärke der Änderung der Verbindugsstärke bei einem falschen Endergebnis und des Faktors mit dem die alte Verbindungsstärke in die Berechnung der neuen einfließen soll
{
	double x;
	if (m_learningVals.size() > 0) {
		m_learningVals.clear();
	}
	cout << "Learning Rate:" << endl;
	cin >> x;
	m_learningVals.push_back(x);
	cout << "Old-Con-Str Faktor:" << endl;
	cin >> x;
	m_learningVals.push_back(x);
}

Menu::Menu()																	//Festlegung der dafault-werte, die ein Neuronales Netz hat, bevor man es anpasst
{
	m_layout.push_back(4);
	m_layout.push_back(15);
	m_layout.push_back(3);
	m_reps = 10000;
	m_learningVals.push_back(0.5);
	m_learningVals.push_back(0.0005);
	m_precision = 0;
	cout << "DEFAULT-";
	Nets.push_back(NeuralNet(m_layout, m_learningVals));
}

Menu::~Menu()
{
}


void Menu::startLearning()
{

			myfile.open("example.txt");
			vector<vector<double>> sampleData = FileReader::readData("SampleData2.csv");			//Einlesen des Datensatzes! Jede Zeile im Datensatz ist ein Vector im Vector SampleData

			int stepcounter = 0, fehlercounter = 0;
			for (unsigned j = 0; j < m_reps; ++j) {


				vector<double> inputWerte;		
			
				unsigned x = rand() % sampleData.size();											//Generierunge eine zufälligen Wertes zwischen 0 und der Größe des Datensatzes um einen zufälligen Satz Input-daten auszuwählen

				for (unsigned int n = 0; n < (m_layout.front()); ++n)									//die größe der Input-Layer bestimmt die Anzahl der Werte aus dem ausgewählten Satz, die an die Input-Neuronen übergeben werden
				{
					inputWerte.push_back(sampleData[x][n]);											//die Daten, die an die Input-neuronen übergeben werden sollen, werden zunächst in einen Vector geschrieben
				}

				vector<double> zielWerte;
				for (unsigned y = 0; y < m_layout.back(); y++)										//der Wert, der an der letzten Stelle des ausgewählten input-datensatzes steht, bestimmt, an welches der output-Neuronen eine 1 übergeben wird, die danderen bekommen den Wert 0 zugewiesen
					if (y+1 == ((sampleData[x].back()))) {
						zielWerte.push_back(1);
					}
					else zielWerte.push_back(0);
					++stepcounter;

					Nets[0].feedForward(inputWerte);												//die Inputwerte werden mit der feedforward-Funktion an das neuronale Netz übergeben 

					Nets[0].backProp(zielWerte);													//die Zielwerte werden der Backpropagation-funktion übergeben, die überprüft, ob das erwünschte ergebnis erzielt wurde und das neuronale Netz dahingehend anpasst, dass beim nächsten Versuch eher die erwünschten Werte erreicht werden

					vector<double> ergebnis;
					Nets[0].getResults(ergebnis);													//Das Ergebnis der Berechnung des neuronalen Netzwerkes werden mittels der getResult-Funktion abgerufen und in einem Vector gespeichert, der eine Anschließende Verwendung der Werte ermöglicht

					//Die erzielten Werte werden nun auf 1 oder 0 gerundet und wenn dies nicht das gewünschte Ergebnis erzielt, werden die Werte in der example.txt gespeichert um nach dem Lernen sehen zu können, bei welchen Werten die AI schwierigkeiten hat
					if (zielWerte[0] != (int)round(ergebnis[0]) || zielWerte[1] != (int)round(ergebnis[1]) || zielWerte[2] != (int)round(ergebnis[2])) {
						myfile << "Step " << stepcounter << "Input : " << inputWerte[0] << " " << inputWerte[1] << " " << inputWerte[2] << " " << inputWerte[3] << "Ziel : " << zielWerte[0] << " " << zielWerte[1] << " " << zielWerte[2] << " " << "Ergebnis : " << (int)round(ergebnis[0]) << " " << (int)round(ergebnis[1]) << " " << (int)round(ergebnis[2]) << endl;

						fehlercounter++;
					}
				
					if (stepcounter % 1000 == 0) {
						system("cls");
						cout << "Learning successfull!" << endl;
						cout << "Step: "<< stepcounter << endl;
						cout <<"Genauigkeit: "<< 100-(fehlercounter / 10) <<"%"<< endl;
						m_precision = 100 - (fehlercounter / 10);
						fehlercounter = 0;

					}








			}
			cout << "Press any key to continue..." << endl;
			while (!kbhit());
			myfile.close();
		
}

void Menu::makeNeuralNet()
{
	Nets.clear();
	cout << "Altes Netz geloescht!" << endl;
	Nets.push_back(NeuralNet(m_layout, m_learningVals));
}

void Menu::printNet()
{
	system("cls");
	cout << "Neural Net:" << endl;
	for (unsigned x = 0; x < Nets[0].returnLayout().size(); ++x) {
		Menu::chart2("Anzahl der Neuronen in Layer", x+1, Nets[0].returnLayout()[x]);
	}
	Menu::chart("Learning Rate", m_learningVals[0]);
	Menu::chart("Old-con-Str Faktor", m_learningVals[1]);
	Menu::chart("Umfang des naechsten Lernprozessess", m_reps);
	Menu::chart("Genauigkeit in % ", m_precision);
	cout << "Press any key to continue..." << endl;
	while(!kbhit());
}
