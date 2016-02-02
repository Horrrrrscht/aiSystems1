#ifndef SYNAPSE_H
#define SYNAPSE_H


class Synapse
{
public:
	Synapse();
	~Synapse();

	void setStrength(double newStrength) { m_strength = newStrength; }
	void setDeltaStrength(double newDeltaStrength) { m_deltaStrength = newDeltaStrength; }

	double getStrength() { return m_strength; }
	double getDeltaStrength() { return m_deltaStrength; }


private:


	double m_strength;
	double m_deltaStrength;

};

#endif // !SYNAPSE_H
#pragma once
