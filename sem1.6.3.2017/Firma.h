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
	ArrayList<Zasielka*> *aSklad;
	ArrayList<Dodavatel*> *aDodavatelia; 
	LinkedList<Kamion*> *aKamiony; 
	ArrayList<Paleta*> *aNezrealizovane;
	ArrayList<Paleta*> *aNeprevzate;
	LinkedList<Paleta*> *aNezaevidovaliSaDoSkladu; //lebo tam len pridavam

public:
	Firma();
	~Firma();
	bool pridajNoveVozidlo(Vozidlo* vozidlo); 
	bool pridajNovehoDodavatela(Dodavatel* dodavatel);
	void vypisDodavatelov();
	void otestujPrioritnyFront(int o);
	void vypisVozidlaPodlaDatumu();
	void ohlasKamion(Kamion* paKamion); //5
	void vypisKamiony(); //na otestovanie metody 5
	void vylozeniePalietDoSkladu(Kamion* paKamion); //6
	void vypisSklad(); //otestovanie 6
	double vratMaxNosnost();
	void naplnenieVozidiel(string paDatum); //7
	void otestujPrioritnyFront1();
	//void skontrolujOpotrebovanie();
	void vypisPaletyZVozidiel();
	//void sortPodlaOpotrebovanosti();
	void sortPodlaHmotnosti(ArrayList<Paleta*> *prvejTriedy);
	void sortPodlaDatumu(ArrayList<Paleta*> *ostatne);
	void nemozuSaNalozitVsetky(string paDatum, ArrayList<Vozidlo*> *vozidla);
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

};

