#ifndef MENU_H
#define MENU_H
//bla
#include <vector>
#include "NeuralNet.h"
#include "FileReader.h"
#include "Neuron.h"

using namespace std;


class NeuralNet;

//das menu ist f�r die Organisation des neuralNets zust�ndig und erm�glicht dem Nutzer die Interaktion mit dem netz

class Menu
{
public:
	Menu();
	vector<unsigned>getLayout() { return m_layout; }
	void setLayout();
	unsigned getReps() { return m_reps; }
	void setReps();
	void chart(const char* Funktion, double Eingabe);
	void chart2(const char* Funktion, unsigned Eingabe, unsigned Eingabe2);
	void ui();
	vector<double> getLearningVals() { return m_learningVals; }
	void setLearningVals();
	vector<double>getOwnInput() { return m_ownInput; }
	void setOwnInput();
	int exit() { return m_exit; }
	void startLearning();
	void makeNeuralNet();
	void printNet();



	~Menu();

private:
	vector<NeuralNet> Nets;
	vector<unsigned> m_layout, m_oldlayout;
	unsigned m_reps;
	vector<double> m_learningVals;
	vector<double>m_ownInput;
	int m_startLearning;
	int m_exit=0;
	int m_precision;

};









#endif // !MENU_H
#pragma once
