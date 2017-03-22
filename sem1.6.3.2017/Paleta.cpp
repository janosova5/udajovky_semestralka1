#include "Paleta.h"
#include "Datum.h"



Paleta::Paleta()
{
}

Paleta::Paleta(int paRegion, double paHmotnost, bool paPrvejTriedy, string paDatum, Dodavatel *dod)
{
	aRegion = paRegion;
	aHmotnost = paHmotnost;
	aPrvejTriedy = paPrvejTriedy;
	//aDatumDorucenia = "";
	aZrealizovana = true;
	aPrevzata = false;
	aDatumVratenia = "";
	aDatumPrichodu = "";
	aDatumNeprevzatia = "";
	aDodavatel = dod;
	aNalozena = false;
	if (aPrvejTriedy) {
		aDatumDorucenia = paDatum;
	}
	else aDatumDorucenia = "00.00.0000"; //lubovolny datum dorucenia
}


Paleta::~Paleta() //nemoze rusit dodavatela, na toho mam smerniky v arrayliste dodavatelov
{

}

int Paleta::getRegion()
{
	return aRegion;
}

double Paleta::getHmotnost()
{
	return aHmotnost;
}

bool Paleta::jePrvejTriedy()
{
	return aPrvejTriedy;
}

bool Paleta::jeZrealizovana()
{
	return aZrealizovana;
}

bool Paleta::jePrevzata()
{
	return aPrevzata;
}

bool Paleta::jeNalozena()
{
	return aNalozena;
}

bool Paleta::jeAktualneNaSklade()
{
	if (!(this->jeNalozena()) && this->jePrevzata() == false && this->getDatumNeprevzatia() == "" && this->jeZrealizovana() && this->getDatumVratenia() == "") return true;
	else return false;
}

string Paleta::getDatumDorucenia()
{
	return aDatumDorucenia;
}

string Paleta::getDatumVratenia()
{
	return aDatumVratenia;
}

string Paleta::getDatumPrichodu()
{
	return aDatumPrichodu;
}

string Paleta::getDatumNeprevzatia()
{
	return aDatumNeprevzatia;
}

Dodavatel* Paleta::getDodavatel()
{
	return aDodavatel;
}

void Paleta::setRegion(int paRegion)
{
	aRegion = paRegion;
}

void Paleta::setHmotnost(double paHmotnost)
{
	aHmotnost = paHmotnost;
}

void Paleta::setPrvejTriedy(bool paPrvejTriedy)
{
	aPrvejTriedy = paPrvejTriedy;
}

void Paleta::setDatumDorucenia(string paDatumDorucenia)
{

	if (aPrvejTriedy) {
		Datum *dnes = new Datum();
		aDatumDorucenia = dnes->getDnesnyDatum();
		delete dnes;
	}
	else aDatumDorucenia = paDatumDorucenia;

}

void Paleta::setZrealizovana(bool paZrealizovana)
{
	aZrealizovana = paZrealizovana;
}

void Paleta::setPrevzata(bool paPrevzata)
{
	aPrevzata = paPrevzata;
}

void Paleta::setDatumVratenia(string paDatumVratenia)
{
	aDatumVratenia = paDatumVratenia;
}

void Paleta::setDatumPrichodu(string paDatumPrichodu)
{
	aDatumPrichodu = paDatumPrichodu;
}

void Paleta::setDodavatel(Dodavatel * paDodavatel)
{
	aDodavatel = paDodavatel;
}

void Paleta::setNalozena(bool nalozena)
{
	aNalozena = nalozena;
}

void Paleta::setDatumNeprevzatia(string datum)
{
	aDatumNeprevzatia = datum;
}
