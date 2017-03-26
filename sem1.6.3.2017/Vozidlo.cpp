#include "Vozidlo.h"
#include "heap_monitor.h"

Vozidlo::Vozidlo()
{
}

Vozidlo::Vozidlo(string paSPZ, double paNosnost, string paDatum)
{
	aSPZ = paSPZ;
	aNosnost = paNosnost;
	aOpotrebovanie = 0;
	aRegion = 0;
	aDatumZaradenia = paDatum;
	aKolkoJeNalozene = 0.0;
	aJeNaCeste = false;
	aJeVyradene = false;
	aPalety = new ExplicitStack<Paleta*>();
}

Vozidlo::~Vozidlo()
{
	//aPalety->clear();
	//aPalety->~ExplicitStack();
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
	/**
	if (!(paleta->jeNalozena())) {
		if (aRegion == 0) this->setRegion(paleta->getRegion());
		if (paleta->getHmotnost() + aKolkoJeNalozene <= this->getNosnost() && this->aRegion == paleta->getRegion() && !(paleta->jeNalozena()))
		{
			aPalety->push(paleta);
			paleta->setNalozena(true);
			aKolkoJeNalozene += paleta->getHmotnost();
			return true;
		}
	}
	return false;
	*/

	if (paleta->jeAktualneNaSklade()) {
		if (paleta->getHmotnost() + aKolkoJeNalozene <= this->getNosnost()) {
			if (aRegion == 0) this->setRegion(paleta->getRegion());
			if (this->aRegion == paleta->getRegion()) {
				aPalety->push(paleta);
				aKolkoJeNalozene += paleta->getHmotnost();
				paleta->setNalozena(true);
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

void Vozidlo::mozemPridatPaletu(Paleta * paleta)
{
	//v sklade su vsetky palety, ktore nim zatial presli
	//tu musim vyseparovat tie, ktore sa daju nalozit
	//a to su tie, ktore niesu este nalozene a zaroven neboli este (ne)prevzate alebo (ne)zrealizovane
	if (paleta->jeAktualneNaSklade()) {
		if (paleta->getHmotnost() + aKolkoJeNalozene <= this->getNosnost()) {
				if (aRegion == 0) this->setRegion(paleta->getRegion());
				if (this->aRegion == paleta->getRegion()) {
					aKolkoJeNalozene += paleta->getHmotnost();
					paleta->setNalozena(true);
				}	
		} 
	}
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

void Vozidlo::setJeNaCeste(bool je)
{
	aJeNaCeste = je;
}

bool Vozidlo::jeNaCeste()
{
	return aJeNaCeste;
}

bool Vozidlo::jeVyradene()
{
	return aJeVyradene;
}

void Vozidlo::setJeVyradene(bool je)
{
	aJeVyradene = je;
}



