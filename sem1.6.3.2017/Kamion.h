#pragma once
#include "Paleta.h"
#include <string>
#include "ArrayList.h"
#include "heap_monitor.h"
using namespace std;

using DS::ArrayList;
class Kamion
{
private:
	string aDatumPrichodu;
	ArrayList<Paleta*> *aObsah;

public:
	Kamion(string paDatum);
	~Kamion();
	string getDatumPrichodu();
	ArrayList<Paleta*>* getObsah();
	void setDatumPrichodu(string paDatum);
};

