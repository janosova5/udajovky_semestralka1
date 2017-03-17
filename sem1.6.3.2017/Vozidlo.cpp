#include "Vozidlo.h"


Vozidlo::Vozidlo(string paSPZ, double paNosnost, string paDatum)
{
	aSPZ = paSPZ;
	aNosnost = paNosnost;
	aOpotrebovanie = 0;
	aRegion = 0;
	aDatumZaradenia = paDatum;
	aPalety = new ExplicitStack<Paleta*>();
}

Vozidlo::~Vozidlo()
{
	aPalety->clear();
	delete aPalety;
}

string Vozidlo::getSPZ() const
{
	return aSPZ;
}

double Vozidlo::getNosnost() const
{
	return aNosnost;
}

int Vozidlo::getOpotrebovanie() const
{
	return aOpotrebovanie;
}

int Vozidlo::getRegion() const
{
	return aRegion;
}

string Vozidlo::getDatum() const
{
	return aDatumZaradenia;
}

void Vozidlo::setSPZ(string paSPZ)
{
	aSPZ = paSPZ;
}

void Vozidlo::setNosnost(double paNosnost)
{
	aNosnost = paNosnost;
}

void Vozidlo::zvysOpotrebovanie(int paRegion)
{
	aOpotrebovanie += paRegion;
}

void Vozidlo::setRegion(int paRegion)
{
	aRegion = paRegion;
}


