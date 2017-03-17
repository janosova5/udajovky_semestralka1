#include "Zasielka.h"



Zasielka::Zasielka(int paRegion)
{
	aRegion = paRegion;
	aPalety = new ArrayList<Paleta*>();
}


Zasielka::~Zasielka() //????
{
	aPalety->clear();
	delete aPalety;
}

int Zasielka::getRegion()
{
	return aRegion;
}

ArrayList<Paleta*>* Zasielka::getPalety()
{
	return aPalety;
}

void Zasielka::setRegion(int paRegion)
{
	aRegion = paRegion;
}

double Zasielka::spocitajHmotnosti()
{	
	double hm = 0.0;
	for (Paleta *P: *aPalety) {
		hm += P->getHmotnost();
	}
	return hm;
}
