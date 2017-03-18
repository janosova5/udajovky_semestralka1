#include "Firma.h"
#include <iostream>



Firma::Firma()
{
	aEvidenciaVozidiel = new ArrayList<Vozidlo*>(5); 
	//aMozuRozvazat = new PriorityQueue_Heap<Vozidlo*>(); 
	aVyradeneVozidla = new LinkedList<Vozidlo*>(); //zatial to dam ako linkedlist kym nezozeniem funkcne explicit queue
	aSklad = new ArrayList<Zasielka*>(5);
	aDodavatelia = new ArrayList<Dodavatel*>(5); 
	aKamiony = new LinkedList<Kamion*>(); 
	aNezrealizovane = new ArrayList<Paleta*>(5);
}


Firma::~Firma() // ????? 
{
	//TODO aafasfas
	aEvidenciaVozidiel->clear();
	delete aEvidenciaVozidiel;
	//aMozuRozvazat->clear();
	//delete aMozuRozvazat;
	aVyradeneVozidla->clear();
	delete aVyradeneVozidla;
	aSklad->clear();
	delete aSklad;
	aDodavatelia->clear();
	delete aDodavatelia;
	aKamiony->clear();
	delete aKamiony;
	aNezrealizovane->clear();
	delete aNezrealizovane;
}

bool Firma::pridajNoveVozidlo(Vozidlo* vozidlo) //tuto budem pridavat aj do evidencie vozidiel kvoli metode 10
{
	Datum *datum = new Datum();
	int i = 0;
	bool pom = false;
	for (Vozidlo* V : *aEvidenciaVozidiel) {
		if (V->getSPZ() == vozidlo->getSPZ()) {
			pom = true;
			break;
		}
	}
	if (pom == false) {
		if (aEvidenciaVozidiel->size() == 0) {
			//aMozuRozvazat->push(0, vozidlo);
			aEvidenciaVozidiel->add(vozidlo);
		}
		else { //compare porovna lexikograficky 2 retazce
			while ((i < aEvidenciaVozidiel->size()) && (datum->budePrvySkor(vozidlo->getDatum(), aEvidenciaVozidiel->operator[](i)->getDatum())))
			{
				i++;
			}
			aEvidenciaVozidiel->insert(vozidlo, i);
			//aMozuRozvazat->push(0, vozidlo);
			//cout << i; 
		}
		return true;
	}
	else {
		cout << "Dodavatel s tymto nazvom uz existuje";
		return false;
	}
	delete datum;
}

bool Firma::pridajNovehoDodavatela(Dodavatel* dodavatel)
{
	int i = 0;
	bool pom = false;
	for (Dodavatel* D : *aDodavatelia) {
		if (D->getObchodnyNazov() == dodavatel->getObchodnyNazov()) {
			pom = true;
			break;
		}
	}
	if (pom == false) {
		if (aDodavatelia->size() == 0) {
			aDodavatelia->add(dodavatel);
		}
		else { //compare porovna lexikograficky 2 retazce
			while (i < aDodavatelia->size() && dodavatel->getObchodnyNazov().compare(aDodavatelia->operator[](i)->getObchodnyNazov()) > 0)
			{
				i++;
			}
			aDodavatelia->insert(dodavatel,i); 
			//cout << i; 
		}
		return true;
	}
	else {
		cout << "Dodavatel s tymto nazvom uz existuje";
		return false;
	}
}

void Firma::vypisDodavatelov()
{
	//cout << " " << aDodavatelia->size();
	for (Dodavatel* D : *aDodavatelia) { 
		cout << D->toString() << endl;
	}
	//for (int i = 0; i < aDodavatelia->size(); i++)
	//{
		//cout << aDodavatelia->operator[](i)->toString();
	//}
}

void Firma::otestujPrioritnyFront(int o)
{
	//Vozidlo *pom = aMozuRozvazat->pop();
	//pom->zvysOpotrebovanie(o);
	//aMozuRozvazat->push(pom->getOpotrebovanie(), pom);
}
void Firma::otestujPrioritnyFront1()
{
	PriorityQueue_Heap<int> *skuska = new PriorityQueue_Heap<int>();
	skuska->push(2.5, 1);
	skuska->push(8.5, 1);
	skuska->push(1.9, 1);
	for (int i = 0; i < skuska->size(); i++) {
		cout << skuska->peek(i) <<endl;
	}
	delete skuska;
}

void Firma::vypis() //IBA NA OTESTOVANIE PRIOR.FRONTU!
{
	//int pocet = aMozuRozvazat->size();
	//for (int i = 0; i < pocet; i++) //tu si treba davat pozor pri vypisovani lebo ked popnem tak zaroven sa velkost frontu znizi o 1 a nevypise
		//vsetky, budem ich popovat a zaroven pridavat do arraylistu, ktory zoradim podla datumu a tak ich vypisem
	//{
		//cout << aMozuRozvazat->peek(i)->getOpotrebovanie() << endl;
	//}
	
}

void Firma::vypisVozidlaPodlaDatumu()
{
	for (Vozidlo* V : *aEvidenciaVozidiel) { 
		cout << "SPZ: " << V->getSPZ() << ", nosnost: " << V->getNosnost() << ", opotrebovanie: " << V->getOpotrebovanie();
	}
}

void Firma::ohlasKamion(Kamion* paKamion) //ten kamion sa musi predtym niekde vytvorit, cize sa musi naplnit jeho pole paletami
//a urcit datum, to bude asi niekde v main, moze sa to nacitat zo suboru alebo najskor skusim to tam natvrdo hodit nejake atributy
{
	aKamiony->add(paKamion); 
	for (Kamion* K : *aKamiony) {
		for(int i = 0; i < K->getObsah()->size(); i++) //kazdej palete sa nastavi datum prichodu, treba to kvoli metode 13
			K->getObsah()->operator[](i)->setDatumPrichodu(K->getDatumPrichodu());
	}
}

void Firma::vypisKamiony()
{
	for (Kamion* K : *aKamiony) {
		cout << K->getDatumPrichodu();
	}
}

void Firma::vylozeniePalietDoSkladu(Kamion* K) //funguje
{
	Datum* dnes = new Datum();
	//toto arraylist lebo tam aj hlavne pristupujem k prvkom
	ArrayList<int> *pom = new ArrayList<int>(); //v tomto poli su docasne ulozene zatial rozlisene regiony
	ArrayList<Zasielka*> *zasielky = new ArrayList<Zasielka*>(); //kvoli vyhladaniu na ktorom indexe sa dana zasielka v sklade nachadza,
	//aby sme jej potom mohli pridat palety, ktore patria pre jej region
	//toto bude linkedlist lebo tam len pridavam
	//int pocet;
	int velkost;
	int index;
	//tu nemozem pouzit foreach, lebo na konci jednej otocky vymazem dany kamion z kontajnera aKamiony, takze pri foreach by mi padol program
	//for (Kamion *K: *aKamiony) { //ohlasene kamiony
		//if (dnes->budePrvySkor(K->getDatumPrichodu(),dnes->getDnesnyDatum())) { //uz prisiel do skladu
			//pocet = K->getObsah()->size(); //kolko obsahuje dany kamion paliet
			//cout << pocet << endl;
	for (int i = 0; i < K->getObsah()->size(); i++) { //prejdem vsetky jeho palety
		velkost = pom->size(); //velkost pomocneho pola
		//cout << velkost << endl;
		//ak paleta splna podmienky, prida sa do skladu, ak ich nesplna, do skladu sa neprida
		if (K->getObsah()->operator[](i)->getHmotnost() <= vratMaxNosnost() && dnes->budePrvySkor(K->getObsah()->operator[](i)->getDatumDorucenia(),dnes->getDnesnyDatum())) {
			if (velkost == 0) {
				Zasielka* zasielka = new Zasielka(K->getObsah()->operator[](i)->getRegion());
				//do kontajnera paliet zasielky pridam zasielku, ktora splna dany region
				zasielka->getPalety()->add(K->getObsah()->operator[](i)); //danu paletu pridam do zasielky
				pom->add(K->getObsah()->operator[](i)->getRegion()); //pridam ju do pomocneho pola kvoli rozlisteniu regionu
				zasielky->add(zasielka);
				aSklad->add(zasielka); //zaroven ju pridam rovno do skladu
				//tu asi nemozem deletnut zasielku, lebo si ju zrusim
			}
			else { //ak sa uz v pomocnom poli nachadzaju zasielky, teda je rozliseny nejaky region
				for (int j = 0; j < velkost; j++) { //prejdi vsetky regiony
					//ak sa nasla paleta, ktora ma odlisny region
					//cout << "region pom: " << pom->operator[](j)->getRegion() << endl;
					//cout << "region palety: " << K->getObsah()->operator[](i)->getRegion() << endl;
					//ak taky region este nenasiel - teda nenachadza sa este v poli pre regiony 
					if ((K->getObsah()->operator[](i)->getRegion() != pom->operator[](j)) && pom->getIndexOf(K->getObsah()->operator[](i)->getRegion()) == -1) {
						Zasielka* zasielka1 = new Zasielka(K->getObsah()->operator[](i)->getRegion());
						zasielka1->getPalety()->add(K->getObsah()->operator[](i));
						pom->add(K->getObsah()->operator[](i)->getRegion()); //pridam ju do pomocneho pola, teda pribudne novy region
						zasielky->add(zasielka1);
						aSklad->add(zasielka1); //zaroven ju pridam rovno do skladu
						break;
					}
					else if (K->getObsah()->operator[](i)->getRegion() == pom->operator[](j) && pom->getIndexOf(K->getObsah()->operator[](i)->getRegion()) != -1) {
						//pom->operator[](j)->getPalety()->add(K->getObsah()->operator[](i)); //pridam len palety danej 
						//existujucej zasielke, ktora sa nachazda v pomocnom poli a aj v sklade
						index = aSklad->getIndexOf(zasielky->operator[](j));
						aSklad->operator[](index)->getPalety()->add(K->getObsah()->operator[](i));
						//aSklad->insert(pom->operator[](j)->getPalety()->add(K->getObsah()->operator[](i)),aSklad->getIndexOf(pom->operator[](j)));
					}

				}
			}
			//Zasielka* zasielka = new Zasielka(K->getObsah()->operator[](i)->getRegion()); //oznac region palety za region zasielky
			//zasielka->getPalety()->add(K->getObsah()->operator[](i)); //pridaj tuto paletu do pola paliet tejto zasielkz s danym reg.
			//aSklad->add(zasielka);
		}
	}
		//}
	//}
	delete dnes;
	delete pom;
	delete zasielky;
}

void Firma::vypisSklad()
{
	cout << aSklad->size();
	cout << endl;
	for (Zasielka *Z : *aSklad) {
		cout << Z->getRegion();
		cout << endl;
		for (int i = 0; i < Z->getPalety()->size(); i++) {
			cout << Z->getPalety()->operator[](i)->getRegion() << ", " << Z->getPalety()->operator[](i)->getHmotnost();
			cout << endl;
		}
	}
}

double Firma::vratMaxNosnost()
{
	double max = 0.0;
	for (Vozidlo* V : *aEvidenciaVozidiel) {
		if (V->getNosnost() > max) max = V->getNosnost();
	}
	return max;
}


void Firma::naplnenieVozidiel()
{
	//etst
	/**int j = 0;
	for (int i = 0; i < aMozuRozvazat->size(); i++) { //prejdi prior.front, cize na zaciatku bude vozidlo s najmensim opotrebenim
		while (j < aSklad->size()) { //prejdi sklad
			aMozuRozvazat->peek(i)->setRegion(aSklad->operator[](j)->getRegion());
			j++;
		
		}
	
	
	
	}
	//v metode, kde sa bude vozidlo vracat a znova pridavat do prior.frontu treba zavolat resetRegion a to nastavi region na 0
	//ak mam zasielok viac ako vozidiel, je jasne, ze niektore zasielky neroznesiem, lebo jedno vozidlo ide len do jedneho regionu
	//kedze jedna zasielka predstavuje jeden region
	//ak ich mam teda viac, tak si ulozim do nejakej premennej kolku otocku idem a ak je to pocetZasielok 

	//aby do kazdeho regionu islo nejake auto, ak je aut dostatok
	//ak aut dostatok nie je, zasielky sa prerozdelia, tak ako "nasleduju za sebou"
	//ak mi na konci zostanu volne kapacity v autach alebo volne auta, tak sa to prerozdeli podla regionov
	//tymto sposobom aj zabranim tomu, aby jedno vozidlo malo viac regionov
	for (Zasielka *Z : *aSklad) { //prejdi sklad, kazda zasielka prezentuje iny region
		for (int i = 0 ; i < aMozuRozvazat->size(); i++) { //prejdi prioritny front 
			//ak sa tam zmestia vsetky palety a nema este nastaveny region
			if (Z->spocitajHmotnosti() <= aMozuRozvazat->peek(i)->getNosnost() && aMozuRozvazat->peek(i)->getRegion() == 0) {
				aMozuRozvazat->peek(i)->setRegion(Z->getRegion()); //autu poviem, ze ides do regionu tejto zasielky

			}
			else if (Z->spocitajHmotnosti() > aMozuRozvazat->peek(i)->getNosnost() && aMozuRozvazat->peek(i)->getRegion() == 0) {
				
			
			}
		}
	}
	//nastavenie regionu
	//v pripade, ze sa pre dane vozidlo najde zasielka, ktora sa do neho zmesti cela, oznacim ho, ze pojde do daneho regionu rozniest
	//danu zasielku
	//ak pre nejake vozidlo nenajdem takuto zasielku, priradim mu hocijaku
	for (int i = 0; i < aMozuRozvazat->size(); i++) { //prejdi prior.front, cize na zaciatku bude vozidlo s najmensim opotrebenim
		for (Zasielka *Z : *aSklad) {
			if (Z->spocitajHmotnosti() <= aMozuRozvazat->peek(i)->getNosnost()) {
				aMozuRozvazat->peek(i)->setRegion(Z->getRegion());
			}
		}
	}
	*/

}
