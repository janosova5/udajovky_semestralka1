#include "Firma.h"
#include "Datum.h"


int main() {
	Firma *firma = new Firma();
	/**string paSPZ;
	cout << "Zadajte SPZ vozidla" << endl;
	cin >> paSPZ;
	double paNosnost;
	cout << "Zadajte nosnost vozidla" << endl;
	cin >> paNosnost;
	string paDatum;
	cout << "Zadajte datum zaradenia vozidla vo formate: dd.mm.yyyy" << endl;
	cin >> paDatum;
	*/
	Datum *datum = new Datum();
	cout << datum->getDnesnyDatum() << endl;
	cout << datum->budePrvySkor("15.03.2017", datum->getDnesnyDatum()) << endl;
	Vozidlo* vozidlo1 = new Vozidlo("abcd123", 20.6, "05.05.2015");
	Vozidlo* vozidlo2 = new Vozidlo("efgh123", 27.6, "25.05.2016");
	Vozidlo* vozidlo3 = new Vozidlo("ijkl123", 21.6, "04.01.2017");
	firma->pridajNoveVozidlo(vozidlo1);
	firma->pridajNoveVozidlo(vozidlo2);
	firma->pridajNoveVozidlo(vozidlo3);
	cout << "max nosnost: " << firma->vratMaxNosnost() << endl;
	//firma->pridajNoveVozidlo();
	//firma->pridajNoveVozidlo();
	//firma->otestujPrioritnyFront(10);
	//firma->otestujPrioritnyFront(15);
	//firma->vypis();
	firma->vypisVozidlaPodlaDatumu();
	//firma->pridajNovehoDodavatela();
	//firma->pridajNovehoDodavatela();
	//firma->pridajNovehoDodavatela();
	//firma->vypisDodavatelov();
	//firma->ohlasKamion(firma->naplnKamion1("01.01.2017"));
	//firma->ohlasKamion(firma->naplnKamion2("01.02.2017"));
	Dodavatel *dod1 = new Dodavatel("Lidl", "Vysokoskolakov-Zilina"); //tento dodavatel pojde z pola dodavatelov,cize toho nedeletujem
	Paleta* paleta1 = new Paleta(1, 2.5, false, "", dod1);
	Paleta* paleta2 = new Paleta(2, 1.8, false, "", dod1);
	Kamion* kamion = new Kamion("01.01.2017");
	kamion->getObsah()->add(paleta1);
	kamion->getObsah()->add(paleta2);
	Paleta* paleta3 = new Paleta(1, 5.2, true, "20.03.2017", dod1);
	cout << paleta3->getDatumDorucenia() << endl;
	Paleta* paleta4 = new Paleta(1, 12.9, false, "", dod1);
	Paleta* paleta5 = new Paleta(2, 10.1, true, "21.03.2017", dod1); //poriesit metodu budePrvySkor, aby nedavalo paletu ktora ma dnesny den
	Paleta* paleta6 = new Paleta(3, 20.1, true, "22.03.2017", dod1);
	Paleta* paleta7 = new Paleta(2, 0.4, true, "22.03.2017", dod1);
	Kamion* kamion1 = new Kamion("01.02.2017");
	kamion1->getObsah()->add(paleta3);
	kamion1->getObsah()->add(paleta4);
	kamion1->getObsah()->add(paleta5);
	kamion1->getObsah()->add(paleta6);
	kamion1->getObsah()->add(paleta7);
	//firma->ohlasKamion(firma->naplnKamion1("01.02.2017"));
	firma->ohlasKamion(kamion);
	firma->ohlasKamion(kamion1);
	firma->vypisKamiony();
	firma->vylozeniePalietDoSkladu(kamion);
	firma->vylozeniePalietDoSkladu(kamion1);
	//firma->vypisKamiony();
	firma->vypisSklad();
	cout << "Naplnenie vozidiel" << endl;
	firma->naplnenieVozidiel("22.03.2017"); //do tejto metody asi pojde parameter datum, ze ktory den sa ide rozvazat
	firma->vypisPaletyZVozidiel();
	firma->vylozenieVozidla(vozidlo2);
	firma->vylozenieVozidla(vozidlo3);
	cout << "palety vo vozidlach - kontrola: " << endl;
	firma->vypisPaletyZVozidiel();
	//firma->vypisSklad();
	//firma->otestujPrioritnyFront1();
	//firma->vypisKamiony();
	//firma->~Firma(); toto tu nemozem dat, lebo to pada, ale ako mam potom vymazat pamat ? 
	double cislo = firma->randBetween0and1();
	cout << "Cislo: "  << cislo << endl;
	return 0;
}