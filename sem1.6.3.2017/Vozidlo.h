#pragma once
#include "ExplicitStack.h"
#include "Paleta.h"
#include <iostream>
#include <string>

using std::string;
using DS::ExplicitStack;

class Vozidlo //malo by mat este kontajner paliet, aby som ich tam mohla nalozit, ot by mohol byt aj stack
{
private:
	string aSPZ;
	double aNosnost;
	int aOpotrebovanie;
	int aRegion;
	string aDatumZaradenia;
	double aKolkoJeNalozene;
	ExplicitStack<Paleta*> *aPalety;

public:
	Vozidlo() {};
	Vozidlo(string paSPZ, double paNosnost, string paDatum);
	~Vozidlo();
	string getSPZ()  const;
	double getNosnost() const;
	int getOpotrebovanie() const;
	int getRegion() const;
	string getDatum() const;
	ExplicitStack<Paleta*>* getPalety();
	friend bool operator ==(Vozidlo a, Vozidlo b);
	void setSPZ(string paSPZ);
	void setNosnost(double paNosnost);
	void zvysOpotrebovanie(int paRegion);
	void setRegion(int paRegion);
	bool pridajPaletu(Paleta *paleta);
	bool mozemPridatPaletu(Paleta *paleta);
	void vynulujKolkoJeNalozene();
	void resetRegion();
	double getNalozene();
	void setNalozene(double hmotnost);
};

inline bool operator ==(Vozidlo a, Vozidlo b)
{
	return false;
}
