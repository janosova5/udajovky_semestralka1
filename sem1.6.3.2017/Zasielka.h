#pragma once
#include "ArrayList.h"
#include "Paleta.h"
using namespace std;

using DS::ArrayList;

class Zasielka
{
private: 
	int aRegion;
	ArrayList<Paleta*> *aPalety;
public:
	Zasielka(int paRegion);
	~Zasielka();
	int getRegion();
	ArrayList<Paleta*>* getPalety();
	void setRegion(int paRegion);
	double spocitajHmotnosti();
};

