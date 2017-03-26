#include "Kamion.h"
#include "heap_monitor.h"


Kamion::Kamion(string paDatum)
{
	aObsah = new ArrayList<Paleta*>();
	aDatumPrichodu = paDatum;
}


Kamion::~Kamion() //????
{
	//aObsah->clear();
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
