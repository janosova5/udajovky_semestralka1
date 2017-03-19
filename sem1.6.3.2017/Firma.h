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
//using DS::ExplicitQueue;
//using DS::ImplicitQueue;

class Firma
{
private:
	ArrayList<Vozidlo*> *aEvidenciaVozidiel; //tu iba budu uchovane vsetky vozidla, ktore ma firma k dispo
	ArrayList<Vozidlo*> *aRozvazajuceVozidla; //sem budem davat vozidla, ked s nimi budem pracovat a vyberat ich podla opotrebovanosti
	LinkedList<Vozidlo*> *aVyradeneVozidla; //kedm i pojde explicit queue dam ten
	ArrayList<Zasielka*> *aSklad;
	ArrayList<Dodavatel*> *aDodavatelia; //toto bude arraylist
	LinkedList<Kamion*> *aKamiony; //mozno to nejde lebo nemam deklarovane v kontruktore new array list pre kamiony, skusim to este tak
	//uz to ide, problem bol asi to, ze som naplnala kamion v metode, kde som si sice vratila kamion ale vratila som ho ako smernik
	//a lokalnu premennu nemozem vracat ako smernik lebo mi zanikne
	ArrayList<Paleta*> *aNezrealizovane;

public:
	Firma();
	~Firma();
	bool pridajNoveVozidlo(Vozidlo* vozidlo); 
	bool pridajNovehoDodavatela(Dodavatel* dodavatel);
	void vypisDodavatelov();
	void otestujPrioritnyFront(int o);
	void vypis();
	void vypisVozidlaPodlaDatumu();
	//Kamion* naplnKamion1(string paDatum); //toto potom budem robit niekde inde, teraz len testujem metodu 5
	//Kamion& naplnKamion2(string paDatum);
	void ohlasKamion(Kamion* paKamion); //5
	void vypisKamiony(); //na otestovanie metody 5
	void vylozeniePalietDoSkladu(Kamion* paKamion); //6
	void vypisSklad(); //otestovanie 6
	double vratMaxNosnost();
	void naplnenieVozidiel();
	void otestujPrioritnyFront1();
	void skontrolujOpotrebovanie();
	void vypisPaletyZVozidiel();
};

