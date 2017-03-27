#include "Kamion.h"
#include "heap_monitor.h"


Kamion::Kamion(string paDatum)
{
	aObsah = new ArrayList<Paleta*>(10);
	aDatumPrichodu = paDatum;
	aJeVylozeny = false;
}


Kamion::~Kamion() //????
{
	//aObsah->clear();
	//for (Paleta *p : *aObsah) {
		//if (p != nullptr) {
			//delete p;
		//}
	//}
	delete aObsah;
}

string Kamion::getDatumPrichodu()
{
	return aDatumPrichodu;
}

ArrayList<Paleta*>* Kamion::getObsah()
{
	return aObsah;
}

void Kamion::setDatumPrichodu(string paDatum)
{
	aDatumPrichodu = paDatum;
}

bool Kamion::jeVylozeny()
{
	return aJeVylozeny;
}

void Kamion::setJeVylozeny(bool je)
{
	aJeVylozeny = je;
}
