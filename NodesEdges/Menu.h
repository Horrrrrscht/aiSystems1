#ifndef MENU_H
#define MENU_H
//bla
#include <vector>

using namespace std;

class Menu
{
public:
	Menu();
	vector<unsigned>getLayout() { return m_layout; }
	void setLayout();
	unsigned getReps() { return m_reps; }
	void setReps();
	void chart(const char* Funktion, int Eingabe);
	void ui();
	vector<double> getLearningVals() { return m_learningVals; }
	void setLearningVals();
	vector<double>getOwnInput() { return m_ownInput; }
	void setOwnInput();
	int go() { return m_startLearning; }


	//bla


	~Menu();

private:
	vector<unsigned> m_layout;
	unsigned m_reps;
	vector<double> m_learningVals;
	vector<double>m_ownInput;
	int m_startLearning;


};









#endif // !MENU_H
#pragma once