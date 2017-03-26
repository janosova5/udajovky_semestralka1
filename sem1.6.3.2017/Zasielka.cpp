#include "Zasielka.h"
#include "heap_monitor.h"


Zasielka::Zasielka(int paRegion)
{
	aRegion = paRegion;
	aPalety = new ArrayList<Paleta*>();
}


Zasielka::~Zasielka() //????
{
	for (Paleta *p : *aPalety) {
		delete p;
	}
	//aPalety->clear();
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
