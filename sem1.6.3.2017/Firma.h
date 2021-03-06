#pragma once
#include "ArrayList.h"
#include "ExplicitQueue.h"
#include "PriorityQueue_Heap.h"
#include "Vozidlo.h"
#include "Paleta.h"
#include "Datum.h"
#include "Kamion.h"
#include "Zasielka.h"
#include "LinkedList.h"
#include "ImplicitQueue.h"
#include <iostream>
#include "heap_monitor.h"
using namespace std;

using DS::ArrayList;
using DS::LinkedList;
using DS::PriorityQueue_Heap;
using DS::ExplicitQueue;

class Firma
{
private:
	ArrayList<Vozidlo*> *aEvidenciaVozidiel; //tu iba budu uchovane vsetky vozidla, ktore ma firma k dispo
	PriorityQueue_Heap<Vozidlo*> *aRozvazajuceVozidla; //sem budem davat vozidla, ked s nimi budem pracovat a vyberat ich podla opotrebovanosti
	ExplicitQueue<Vozidlo*> *aVyradeneVozidla; 
	PriorityQueue_Heap<Paleta*> *aSklad; //toto pouzivam ked s paletami pracujem
	ArrayList<Dodavatel*> *aDodavatelia; 
	ArrayList<Kamion*> *aKamiony; //vypisujem ich
	ArrayList<Paleta*> *aNezrealizovane;
	ArrayList<Paleta*> *aNeprevzate;
	LinkedList<Paleta*> *aNezaevidovaliSaDoSkladu; //lebo tam len pridavam
	ArrayList<Paleta*> *aEvidenciaPaliet; //tu evidujem vsetky palety kvoli vypisu

public:
	Firma();
	~Firma();
	bool pridajNoveVozidlo(Vozidlo* vozidlo); 
	bool pridajNovehoDodavatela(Dodavatel *dod);
	void vypisDodavatelov();
	void vypisVozidlaPodlaDatumu();
	void ohlasKamion(Kamion* paKamion); //5
	int vypisKamiony(); //na otestovanie metody 5
	int vypisVylozeneVozidla();
	ArrayList<Kamion*>* getKamiony();
	ArrayList<Vozidlo*>* getVozidla();
	int vypisNalozeneVozidla();
	void vylozeniePalietDoSkladu(Kamion* paKamion); //6
	void vypisSklad(); //otestovanie 6
	double vratMaxNosnost();
	void naplnenieVozidiel(string paDatum); //7
	void vypisPaletyZVozidielPoVylozeni();
	void vylozenieVozidla(Vozidlo *vozidlo, string datum); //funkcionalita 8 
	double randBetween0and1();
	void navratVozidla(Vozidlo *vozidlo); //funkcionalita 9
	void vyradenieVozidielZevidencie();
	void vymazanieDodavatela(Dodavatel* dod);
	void vypisNezrealizovanePalety(string datumOd, string datumDo); //funkcionalita 13 - funguje
	void dodavatelSnajvacsimPoctomNeprevzatychPaliet(string datumOd, string datumDo);
	void ulozDodavatelovDoSuboru();
	void nacitajDodavatelovZoSuboru();
	bool uzObsahujeTohtoDodavatela(string nazov); 
	void ulozEvidenciuVozidielDoSuboru();
	void nacitajVozidlaZoSuboru();
	bool uzObsahujeTotoVozidlo(string spz);
	void ulozSkladDoSuboru();
	void ulozNevylozeneKamionyDoSuboru();
	void ulozNalozeneVozidlaDoSuboru();
	void ulozVylozeneVozidlaDoSuboru();
	void ulozEvidenciuDoSuboru();
	void nacitajSkladZoSuboru();
	void nacitajNevylozeneKamionyZoSuboru();
	void vypisEvidenciuPaliet();
	int zmenDatumNaInt(string paDatum);
	Dodavatel* vyhladajDodavatelaPodlaNazvu(string nazov);
};

