#include "Neuron.h"
#include <iostream>
#include "Synapse.h"

using namespace std;





//Wenn ein Neuron erstellt wird, wird ihm gesagt, wieviele nachfolgende Neuronen es gibt und es erzeugt für jede verbindung zu diesen einen zufälligen Wert für die Verbindugsstärke und übergibt diese jeweils an die Klasse Synapse. zusätzlich wird als vorherige Verbindungsstärke der Synapse die aktuelle Verbindungsstärke gespeichert
Neuron::Neuron(unsigned numOutputs, unsigned myId)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputStrengths.push_back(Synapse());
		m_outputStrengths.back().setStrength(randomStrength());
		m_outputStrengths.back().setDeltaStrength(m_outputStrengths.back().getStrength());
	}

	m_id = myId;
}

//Die Summer der dem Neuron aus der vorangegangenen Layer übergebenen und jeweils mit der jeweiligen Verbindugsstärke multiplizierten Werte werden an die Funktions-Funktion des Neurons übergeben und das errechnete Ergebnis wird in m_ergebnis des jeweiligen Neurons gespeichert
void Neuron::feedForward( Layer &prevLayer) {

	double summe = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		summe = (prevLayer[n].getOutputWert() *
			prevLayer[n].m_outputStrengths[m_id].getStrength()) + summe;
	}

	m_ergebnis = Neuron::funktion(summe);
}
//Mithilfe dieser Funktion generiert das Neuron einen Wert zwischen 0 und 1
double Neuron::funktion(double x) {

	return (tanh(x)/2)+0.5 ;
}
//Diese Funktion wird benötigt um festzustellen wie stark die Verbindungsstärke geändert werden muss. man könnte hier Die Ableitung der Funktion benutzen, aber da diese bei der verwendeten Funktion eine größere Berechnung zur Folge hätte, wird hier auf dem Intervall -0.5pi bis 0.5 pi die Cosinusfunktion benutzt, da sie den Anstieg der Funktion annähernd sehr gut beschreibt
double Neuron::funktionsAbleitung(double x) {

	if (-1.5707963<x<1.5707963) return cos(x) ;
	return 0;
}

void Neuron::calcOutputGradients(double zielWert) {
	double delta;
	//if (-0, 2 > zielWert - m_ergebnis>0, 2) {														//Toleranzbereich von +- 0,2, damit bei kleinen Abweichungen die Steigungen nicht mehr angepasst werden
	//	 delta = zielWert - m_ergebnis;
	//}
	//else  delta = 0;

	delta = zielWert - m_ergebnis;

	m_steigung = delta * Neuron::funktionsAbleitung(m_ergebnis);
}

void Neuron::calcHiddenGradients( Layer &nextLayer) {

	double summe = steigungsSumme(nextLayer);
	m_steigung = summe * Neuron::funktionsAbleitung(m_ergebnis);
}

double Neuron::steigungsSumme( Layer &nextLayer)  {

	double summe = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {

		summe = ( m_outputStrengths[n].getStrength() * nextLayer[n].m_steigung) + summe;
	}

	return summe;
}
//die neue Stärke der synapse wird mithilfe der Lern-werte errechnet und die alte Stärke wird gepeichert
void Neuron::updateInputStrengths(Layer &prevLayer) {

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		Neuron &neuron = prevLayer[n];
		double oldDeltaStrength = neuron.m_outputStrengths[m_id].getDeltaStrength();

		double newDeltaStrength = ((m_learningVals[0]) * neuron.getOutputWert()* m_steigung) +  ((m_learningVals[1]) *oldDeltaStrength);


		neuron.m_outputStrengths[m_id].setDeltaStrength(newDeltaStrength);
		neuron.m_outputStrengths[m_id].setStrength ( newDeltaStrength + neuron.m_outputStrengths[m_id].getStrength());

	}
}

void Neuron::printStrengths() {
	for (unsigned n = 0; n < m_outputStrengths.size(); n++) {
		cout << m_outputStrengths[n].getStrength() << endl;
	}
}


Neuron::~Neuron()
{
}
