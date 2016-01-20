#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <string>
#include "Edge.h"

using namespace std;

class Synapse 
{
public:
	Synapse() {};
	~Synapse() {};

	void setStrength(double newStrength) { m_strength = newStrength; }
	void setDeltaStrength(double newDeltaStrength) { m_deltaStrength = newDeltaStrength; }

	double &getStrength() { return m_strength; }
	double &getDeltaStrength() { return m_deltaStrength; }

private:

	double m_strength;
	double m_deltaStrength;

};

#endif
#pragma once