#pragma once
#include <iostream>
#include <string>
#include "Datum.h"
#include "Dodavatel.h"

using std::string;

class Paleta
{
private:
	int aRegion;
	int aHmotnost;
	bool aPrvejTriedy;
	string aDatumDorucenia;
	bool aZrealizovana;
	bool aPrevzata;
	bool aJeNaSklade;
	string aDatumVratenia;
	string aDatumPrichodu;
	bool aNalozena;
	string aDatumNeprevzatia;
	Dodavatel *aDodavatel; 
public:
	Paleta();
	Paleta(int paRegion, int paHmotnost, bool paPrvejTriedy, string paDatum, Dodavatel *dod);
	~Paleta();
	int getRegion();
	int getHmotnost();
	bool jePrvejTriedy();
	bool jeZrealizovana();
	bool jePrevzata();
	bool jeNalozena();
	bool jeAktualneNaSklade();
	bool jeNaSklade();
	string getDatumDorucenia();
	string getDatumVratenia();
	string getDatumPrichodu();
	string getDatumNeprevzatia();
	Dodavatel* getDodavatel();
	void setRegion(int paRegion);
	void setHmotnost(int paHmotnost);
	void setPrvejTriedy(bool paPrvejTriedy);
	void setDatumDorucenia(string paDatumDorucenia);
	void setZrealizovana(bool paZrealizovana);
	void setPrevzata(bool paPrevzata);
	void setDatumVratenia(string paDatumVratenia);
	void setDatumPrichodu(string paDatumPrichodu);
	void setDodavatel(Dodavatel *paDodavatel);
	void setNalozena(bool nalozena);
	void setDatumNeprevzatia(string datum);
	void setJeNaSklade(bool je);

};

