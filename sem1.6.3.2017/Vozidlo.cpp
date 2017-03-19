#include "Vozidlo.h"


Vozidlo::Vozidlo(string paSPZ, double paNosnost, string paDatum)
{
	aSPZ = paSPZ;
	aNosnost = paNosnost;
	aOpotrebovanie = 0;
	aRegion = 0;
	aDatumZaradenia = paDatum;
	aKolkoJeNalozene = 0.0;
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

ExplicitStack<Paleta*>* Vozidlo::getPalety()
{
	return aPalety;
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

bool Vozidlo::pridajPaletu(Paleta * paleta)
{
	if (aRegion == 0 || !(paleta->jeNalozena())) this->setRegion(paleta->getRegion());
	if (paleta->getHmotnost() + aKolkoJeNalozene <= this->getNosnost() && this->aRegion == paleta->getRegion() && !(paleta->jeNalozena()))
	{
		aPalety->push(paleta);
		paleta->setNalozena(true);
		aKolkoJeNalozene += paleta->getHmotnost();
		return true;
	}
	return false;
}

bool Vozidlo::mozemPridatPaletu(Paleta * paleta)
{
	if (aRegion == 0 || !(paleta->jeNalozena())) this->setRegion(paleta->getRegion());
	if (paleta->getHmotnost() + aKolkoJeNalozene <= this->getNosnost() && this->aRegion == paleta->getRegion() && !(paleta->jeNalozena()))
	{
		aKolkoJeNalozene += paleta->getHmotnost();
		return true;
	}
	return false;
}

void Vozidlo::vynulujKolkoJeNalozene()
{
	aKolkoJeNalozene = 0;
}

void Vozidlo::resetRegion()
{
	aRegion = 0;
}

double Vozidlo::getNalozene()
{
	return aKolkoJeNalozene;
}

void Vozidlo::setNalozene(double hmotnost)
{
	aKolkoJeNalozene += hmotnost;
}


