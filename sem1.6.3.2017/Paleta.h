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
	double aHmotnost;
	bool aPrvejTriedy;
	string aDatumDorucenia;
	bool aZrealizovana;
	bool aPrevzata;
	string aDatumVratenia;
	string aDatumPrichodu;
	bool aNalozena;
	Dodavatel *aDodavatel; //este toto dokoncit konstruktor a destruktor 
public:
	Paleta();
	Paleta(int paRegion, double paHmotnost, bool paPrvejTriedy, string paDatum, Dodavatel *paDodavatel);
	~Paleta();
	int getRegion();
	double getHmotnost();
	bool jePrvejTriedy();
	bool jeZrealizovana();
	bool jePrevzata();
	bool jeNalozena();
	string getDatumDorucenia();
	string getDatumVratenia();
	string getDatumPrichodu();
	Dodavatel* getDodavatel();
	void setRegion(int paRegion);
	void setHmotnost(double paHmotnost);
	void setPrvejTriedy(bool paPrvejTriedy);
	void setDatumDorucenia(string paDatumDorucenia);
	void setZrealizovana(bool paZrealizovana);
	void setPrevzata(bool paPrevzata);
	void setDatumVratenia(string paDatumVratenia);
	void setDatumPrichodu(string paDatumPrichodu);
	void setDodavatel(Dodavatel *paDodavatel);
	void setNalozena(bool nalozena);

};

