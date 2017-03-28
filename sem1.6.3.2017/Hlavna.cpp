#include "Firma.h"
#include "Datum.h"
#include "heap_monitor.h"

void vlozData(Firma *firma) {
	Vozidlo* vozidlo1 = new Vozidlo("abcd123", 20, 0, "05.05.2016");
	Vozidlo* vozidlo2 = new Vozidlo("efgh456", 27, 0, "25.05.2015");
	Vozidlo* vozidlo3 = new Vozidlo("ijkl789", 21, 0, "04.01.2016");
	Vozidlo* vozidlo4 = new Vozidlo("mnop100", 33, 0, "13.03.2017");
	Vozidlo* vozidlo5 = new Vozidlo("rstu123", 37, 0, "21.02.2017");
	//1
	firma->pridajNoveVozidlo(vozidlo1);
	firma->pridajNoveVozidlo(vozidlo2);
	firma->pridajNoveVozidlo(vozidlo3);
	firma->pridajNoveVozidlo(vozidlo4);
	firma->pridajNoveVozidlo(vozidlo5);
	//2
	Dodavatel *dod1 = new Dodavatel("Lidl", "Vysokoskolakov15-Zilina");
	Dodavatel *dod2 = new Dodavatel("Tesco", "Vlcince38-Namestovo");
	Dodavatel *dod3 = new Dodavatel("Billa", "Sandricka25-Nitra");
	Dodavatel *dod4 = new Dodavatel("Kaufland", "Majova823-Trencin");
	Dodavatel *dod5 = new Dodavatel("CBA", "Dolna19-Kosice");
	firma->pridajNovehoDodavatela(dod1);
	firma->pridajNovehoDodavatela(dod2);
	firma->pridajNovehoDodavatela(dod3);
	firma->pridajNovehoDodavatela(dod4);
	firma->pridajNovehoDodavatela(dod5);
	Paleta* paleta1 = new Paleta(1, 9, false, "99.99.9999", dod1);
	Paleta* paleta2 = new Paleta(2, 4, false, "99.99.9999", dod1);
	Paleta* paleta3 = new Paleta(1, 5, true, "22.04.2017", dod2);
	Paleta* paleta4 = new Paleta(1, 19, true, "22.04.2017", dod2);
	Paleta* paleta5 = new Paleta(2, 3, true, "20.04.2017", dod3); 
	Paleta* paleta6 = new Paleta(3, 25, true, "22.04.2017", dod3);
	Paleta* paleta7 = new Paleta(4, 12, false, "99.99.9999", dod4);
	Paleta* paleta8 = new Paleta(5, 15, true, "22.04.2017", dod4);
	Paleta* paleta9 = new Paleta(6, 30, true, "22.04.2017", dod4);
	Paleta* paleta10 = new Paleta(5, 38, false, "99.99.9999", dod4);
	Paleta* paleta11 = new Paleta(7, 26, true, "26.05.2017", dod5);
	Kamion* kamion = new Kamion("01.02.2017");
	Kamion* kamion1 = new Kamion("15.03.2017");
	Kamion* kamion2 = new Kamion("08.12.2016");
	Kamion* kamion3 = new Kamion("19.01.2017");
	Kamion* kamion4 = new Kamion("12.03.2017");
	kamion->getObsah()->add(paleta1);
	kamion->getObsah()->add(paleta2);	
	kamion1->getObsah()->add(paleta3);
	kamion1->getObsah()->add(paleta4);
	kamion2->getObsah()->add(paleta5);
	kamion2->getObsah()->add(paleta6);
	kamion3->getObsah()->add(paleta7);
	kamion3->getObsah()->add(paleta8);
	kamion3->getObsah()->add(paleta9);
	kamion3->getObsah()->add(paleta10);
	kamion4->getObsah()->add(paleta11);
	
	//5
	firma->ohlasKamion(kamion);
	firma->ohlasKamion(kamion1);
	firma->ohlasKamion(kamion2);
	firma->ohlasKamion(kamion3);
	firma->ohlasKamion(kamion4);
	//6
	/**
	firma->vylozeniePalietDoSkladu(kamion);
	firma->vylozeniePalietDoSkladu(kamion1);
	firma->vylozeniePalietDoSkladu(kamion2);
	firma->vylozeniePalietDoSkladu(kamion3);
	firma->vylozeniePalietDoSkladu(kamion4);
	//7
	firma->naplnenieVozidiel("22.04.2017");
	//8
	firma->vylozenieVozidla(vozidlo1, "24.04.2017");
	firma->vylozenieVozidla(vozidlo2, "23.04.2017");
	firma->vylozenieVozidla(vozidlo3, "24.04.2017");
	firma->vylozenieVozidla(vozidlo4, "26.04.2017");
	firma->vylozenieVozidla(vozidlo5, "26.04.2017");
	//9
	firma->navratVozidla(vozidlo1);
	firma->navratVozidla(vozidlo2);
	firma->navratVozidla(vozidlo3);
	firma->navratVozidla(vozidlo4);
	firma->navratVozidla(vozidlo5);
	//10
	firma->vyradenieVozidielZevidencie();
	//11
	firma->vypisSklad();
	//12
	firma->dodavatelSnajvacsimPoctomNeprevzatychPaliet("20.04.2017", "25.04.2017");
	//13
	firma->vypisNezrealizovanePalety("20.04.2017", "25.04.2017");
	*/
}
int menu() {
	Datum *d = new Datum();
	int cislo;
	cout << "...................................\nVitajte v menu:\n";
	cout << "Dnes je: " << d->getDnesnyDatum() << endl;
	cout << "Zajtra je: " << d->getZajtra() << endl;
	cout << " 1 - Pridanie noveho vozidla\n";
	cout << " 2 - Vypis vozidiel podla datumu zaradenia do evidencie\n";
	cout << " 3 - Pridanie noveho dodavatela\n";
	cout << " 4 - Vypisanie zoznamu dodavatelov v abecednom poradi podla nazvu \n";
	cout << " 5 - Ohlasenie kamiona s paletami\n";
	cout << " 6 - Vylozenie paliet z kamiona do centralneho skladu\n";
	cout << " 7 - Naplnenie vozidiel paletami zo skladu\n";
	cout << " 8 - Odovzdanie paliet daneho vozidla zakaznikom\n";
	cout << " 9 - Navrat vozidla do skladu\n";
	cout << "10 - Vyradenie opotrebovanych vozidiel z evidencie\n";
	cout << "11 - Vypisanie vsetkych paliet, ktore su aktualne v centralnom sklade\n";
	cout << "12 - Vyhladanie dodavatela, ktoremu bolo za dane casove obdobie vratene najvacsie mnozstvo neprevzatych paliet\n";
	cout << "13 - Vypisanie vsetkych paliet 1. triedy, ktore sa v danom casovom obdobi nepodarilo zrealizovat\n";
	cout << "-1 - Ukoncenie aplikacie\n";
	cin >> cislo;
	system("cls");
	delete d;
	return cislo;
}

int main() {
	initHeapMonitor();
	Firma *firma = new Firma();
	Datum *datum = new Datum();
	//vlozData(firma);
	int cislo = 0;
	system("cls");
	int volba = 0;
	cout << "Pred zacatim programu chcete nacitat aktualnu evidenciu zo suboru alebo zacat s novymi datami? " << endl;
	cout << "Aktualna evidencia zo suboru - 1" << endl;
	cout << "Nove data - 2" << endl;
	cin >> volba;
	if (volba == 1) {
		firma->nacitajDodavatelovZoSuboru();
		firma->nacitajVozidlaZoSuboru();
		firma->nacitajSkladZoSuboru();
		firma->nacitajNevylozeneKamionyZoSuboru();
	}
	else vlozData(firma);
	system("cls");
	while (cislo != -1)
	{
		cislo = menu();
		switch (cislo)
		{
		case 1: {
			string spz, datum;
			int nosnost;
			cin.ignore();
			cout << "Zadajte SPZ vozidla: \n";
			getline(cin, spz);
			cout << "Zadajte datum pridania do evidencie v tvare dd.mm.yyyy: \n";
			getline(cin, datum);
			cout << "\nZadajte nosnost vozidla: \n";
			cin >> nosnost;
			system("cls"); // vycisti konzolu !!!
			firma->pridajNoveVozidlo(new Vozidlo(spz,nosnost,0, datum));
		}; break;
		case 2: {
			firma->vypisVozidlaPodlaDatumu();
		}; break;
		case 3: {
			string obchodnyNazov, adresaSidla;
			cin.ignore();
			cout << "Zadajte obchodny nazov dodavatela: \n";
			getline(cin, obchodnyNazov);
			cout << "\nZadajte adresu sidla v tvare ulica-cislo-mesto: \n";
			getline(cin, adresaSidla);
			system("cls"); // vycisti konzolu !!!
			firma->pridajNovehoDodavatela(new Dodavatel(obchodnyNazov, adresaSidla));
		}; break;
		case 4: {
			firma->vypisDodavatelov();
		}; break;
		case 5: {
			string datumPrichodu, datumDorucenia, nazovDod,adresa;
			int region, hmotnost, pocet;
			cin.ignore();
			cout << "Zadajte datum prichodu kamionu v tvare dd.mm.yyyy (predpokladame, ze je mensi rovny ako dnesny datum): \n";
			getline(cin, datumPrichodu);
			cout << "Zadajte obchodny nazov dodavatela, od ktoreho kamion pochadza: \n";
			getline(cin, nazovDod);
			Dodavatel* dod = firma->vyhladajDodavatelaPodlaNazvu(nazovDod);
			if (dod == nullptr) {
				cout << "Tento dodavatel sa v nasej databaze este nenachadza, pridame ho tam. \n";
				cout << "Zadajte adresu sidla dodavatela v tvare ulica-cislo-mesto: \n";
				getline(cin, adresa);
				dod = new Dodavatel(nazovDod, adresa);
				firma->pridajNovehoDodavatela(dod);
				system("cls");
			}
			Kamion *kamion = new Kamion(datumPrichodu);
			cout << "Zadajte pocet paliet: \n";
			cin >> pocet;
			system("cls");
			for (int i = 1; i <= pocet; i++) {
				system("cls");
				cin.ignore();
				cout << "Paleta c. " << i << ": " << endl;
				cout << "Ak je paleta 1.triedy, zadajte jej datum dorucenia v tvare dd.mm.yyyy, inak zadajte 99.99.9999\n";
				getline(cin, datumDorucenia);
				bool prvejTriedy = false;
				if (datumDorucenia != "99.99.9999") prvejTriedy = true;
				cout << "Zadajte region, do ktoreho ma byt paleta dorucena (berte do uvahy, ze regiony su cislovane od 1 po 8): " << endl;
				cin >> region;
				cout << "Zadajte hmotnost palety ako cele cislo: "<< endl;
				cin >> hmotnost;
				kamion->getObsah()->add(new Paleta(region, hmotnost, prvejTriedy, datumDorucenia, dod));
			}
			firma->ohlasKamion(kamion);
			system("cls");
			//cout << "Kamion bol zaevidovany, pokracujte, prosim, bodom c.6, aby sme jeho palety mohli vylozit do skladu" << endl;
		}; break;
		case 6: {
			int cislo;
			cout << "Ohlasene kamiony: " << endl;
			if (firma->vypisKamiony() > 0) {
				cout << "" << endl;
				cout << "Napiste cislo kamionu, ktoreho palety chcete vylozit do skladu: " << endl;
				cin >> cislo;
				system("cls");
				Kamion *kamion = firma->getKamiony()->operator[](cislo - 1);
				firma->vylozeniePalietDoSkladu(kamion);
			}
			else menu();
		}; break;
		case 7: {
			string datum;
			cin.ignore();
			cout << "Zadajte datum, kedy sa budu vozidla nakladat v tvare dd.mm.yyyy: " << endl;
			getline(cin, datum);
			firma->naplnenieVozidiel(datum); 
		}; break;
		case 8: {
			int cislo;
			string datum;
			cin.ignore();
			cout << "Nalozene vozidla: " << endl;
			if (firma->vypisNalozeneVozidla() > 0) {
				cout << "" << endl;
				cout << "Napiste cislo vozidla, ktoreho palety chcete odovzdat zakaznikovi: " << endl;
				cin >> cislo;
				cin.ignore();
				cout << "Zadajte datum, kedy sa sa vybrane vozidlo vylozi v tvare dd.mm.yyyy: " << endl;
				getline(cin, datum);
				system("cls");
				firma->vylozenieVozidla(firma->getVozidla()->operator[](cislo - 1), datum);
			}
			else menu();
		}; break;
		case 9: {
			int cislo;
			cin.ignore();
			cout << "Vylozene vozidla: " << endl;
			if (firma->vypisVylozeneVozidla() > 0) {
				cout << "" << endl;
				cout << "Napiste cislo vozidla, ktore chcete vratit do skladu: " << endl;
				cin >> cislo;
				system("cls");
				firma->navratVozidla(firma->getVozidla()->operator[](cislo - 1));
			}
			else menu();
		}; break;
		case 10: {
			firma->vyradenieVozidielZevidencie();
		}; break;
		case 11: {
			firma->vypisSklad();
		}; break;
		case 12: {
			string datum1, datum2;
			cin.ignore();
			cout << "Zadajte datum OD v tvare dd.mm.yyyy: " << endl;
			getline(cin, datum1);
			cout << "Zadajte datum DO v tvare dd.mm.yyyy: " << endl;
			getline(cin, datum2);
			firma->dodavatelSnajvacsimPoctomNeprevzatychPaliet(datum1, datum2);
		}; break;
		case 13: {
			string datum1, datum2;
			cin.ignore();
			cout << "Zadajte datum OD v tvare dd.mm.yyyy: " << endl;
			getline(cin, datum1);
			cout << "Zadajte datum DO v tvare dd.mm.yyyy: " << endl;
			getline(cin, datum2);
			firma->vypisNezrealizovanePalety(datum1, datum2);
		}; break;
		case -1: {
			int volba;
			cout << "Chcete ulozit evidenciu do suboru? \n";
			cout << "1 - ano\n";
			cout << "2 - nie\n";
			cin >> volba;
			if (volba == 1)
			{
				cout << "Ukladanie ";
				firma->ulozEvidenciuDoSuboru();
				cislo = -1;
			}
			else if (volba == 2) {
				cout << "Neulozilo sa\n";
				cislo = -1;
			}
		}; break;
		default: cout << "Zadali ste zlu moznost, koniec programu" << endl;
			cislo = -1;
			break;
		}
	}

	cout << "Koniec" << endl;
	delete datum;
	delete firma;
	return 0;
}