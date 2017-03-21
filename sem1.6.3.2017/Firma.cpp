#include "Firma.h"
#include <iostream>
#include <random>
#include <chrono>


Firma::Firma()
{
	aEvidenciaVozidiel = new ArrayList<Vozidlo*>(5);
	aRozvazajuceVozidla = new PriorityQueue_Heap<Vozidlo*>();
	aVyradeneVozidla = new LinkedList<Vozidlo*>(); //zatial to dam ako linkedlist kym nezozeniem funkcne explicit queue
	aSklad = new ArrayList<Zasielka*>(5);
	aDodavatelia = new ArrayList<Dodavatel*>(5);
	aKamiony = new LinkedList<Kamion*>();
	aNezrealizovane = new ArrayList<Paleta*>(5);
}


Firma::~Firma() // ????? 
{
	//TODO aafasfas
	//aEvidenciaVozidiel->clear();
	//delete aEvidenciaVozidiel;
	for (Vozidlo* v : *aEvidenciaVozidiel) { //tymto sa deletnu vsetky vozidla, ktore sa nachadzaju realne v pamati
		v->~Vozidlo();
		delete v;
	}
	aRozvazajuceVozidla->clear();
	delete aRozvazajuceVozidla; //tymto sa deletne ten new arraylist
	//takisto aj dalej
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

bool Firma::pridajNoveVozidlo(Vozidlo* vozidlo) //pridaj nove vozidlo do evidencie vozidiel
//zaroven sa prida aj do vozidiel, ktore mozu rozvazat
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
			aRozvazajuceVozidla->push(0,vozidlo);
			//aMozuRozvazat->push(0, vozidlo);
			aEvidenciaVozidiel->add(vozidlo);
		}
		else { //compare porovna lexikograficky 2 retazce
			while ((i < aEvidenciaVozidiel->size()) && (datum->budePrvySkor(vozidlo->getDatum(), aEvidenciaVozidiel->operator[](i)->getDatum())))
			{
				i++;
			}
			aEvidenciaVozidiel->insert(vozidlo, i);
			aRozvazajuceVozidla->push(0,vozidlo);
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
			aDodavatelia->insert(dodavatel, i);
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
		cout << skuska->peek(i) << endl;
	}
	delete skuska;
}

/**
void Firma::skontrolujOpotrebovanie()
{
	for (Vozidlo* v : *aRozvazajuceVozidla) {
		if (v->getOpotrebovanie() > 90) {
			aVyradeneVozidla->add(v);
			aRozvazajuceVozidla->tryRemove(v);
		}
	}
}
*/

void Firma::vypisPaletyZVozidiel() //iba na kontrolu
{
	//ArrayList <Vozidlo*> *vozidla = new ArrayList<Vozidlo*>();
	//int pocet = aRozvazajuceVozidla->size();
	//for (Vozidlo* v : *aEvidenciaVozidiel) {
		//if (v->getNalozene() == false) aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
	//}
	for (Vozidlo* v : *aEvidenciaVozidiel) {
		if (v->jeNaCeste()) {
			ArrayList <Paleta*> *pom = new ArrayList<Paleta*>();
			cout << v->getPalety()->size() << endl;
			int pocet = v->getPalety()->size();
			for (int i = 0; i < pocet; i++)
			{
				pom->add(v->getPalety()->pop());
				cout << pom->operator[](i)->getHmotnost() << endl;
			}
			for (int i = 0; i < pocet; i++)
			{
				v->getPalety()->push(pom->operator[](i));
			}
			delete pom;
		}
	}
	//delete vozidla;


}
/**
void Firma::sortPodlaOpotrebovanosti()
{
	for (int i = 0; i < aRozvazajuceVozidla->size() - 1; i++) {
		for (int j = 0; j < aRozvazajuceVozidla->size() - i - 1; j++) {
			if (aRozvazajuceVozidla->operator[](j + 1)->getOpotrebovanie() < aRozvazajuceVozidla->operator[](j)->getOpotrebovanie()) {
				Vozidlo* najmensie = aRozvazajuceVozidla->operator[](j+1);
				aRozvazajuceVozidla->operator[](j + 1) = aRozvazajuceVozidla->operator[](j);
				aRozvazajuceVozidla->operator[](j) = najmensie;
			}
		}
	}
}
*/

void Firma::sortPodlaHmotnosti(ArrayList<Paleta*>* prvejTriedy)
{
	for (int i = 0; i < prvejTriedy->size() - 1; i++) {
		for (int j = 0; j < prvejTriedy->size() - i - 1; j++) {
			if (prvejTriedy->operator[](j + 1)->getHmotnost() < prvejTriedy->operator[](j)->getHmotnost()) {
				Paleta* najmensie = prvejTriedy->operator[](j + 1);
				prvejTriedy->operator[](j + 1) = prvejTriedy->operator[](j);
				prvejTriedy->operator[](j) = najmensie;
			}
		}
	}
}

void Firma::sortPodlaDatumu(ArrayList<Paleta*>* ostatne)
{
	Datum * datum = new Datum();
	for (int i = 0; i < ostatne->size() - 1; i++) {
		for (int j = 0; j < ostatne->size() - i - 1; j++) {
			if (datum->budePrvySkor((*ostatne)[j + 1]->getDatumPrichodu(), (*ostatne)[j]->getDatumPrichodu())) {

				Paleta * najmensia = (*ostatne)[j + 1];
				(*ostatne)[j + 1] = (*ostatne)[j];
				(*ostatne)[j] = najmensia;

			}
		}
	}
	delete datum;

}

void Firma::nemozuSaNalozitVsetky(string datum, ArrayList<Vozidlo*> *pom)
{
	cout << "nemozu sa nalozit" << endl;
	ArrayList<Paleta*> *prvejTriedy = new ArrayList<Paleta*>(5);
	ArrayList<Paleta*> *ostatne = new ArrayList<Paleta*>(5);
	//roztriedenie
	for (Zasielka* z : *aSklad) {
		for (Paleta* p : *z->getPalety()) {
			if (p->jePrvejTriedy() && p->getDatumDorucenia() == datum) prvejTriedy->add(p);
			else ostatne->add(p);
		}
	}
	if (prvejTriedy->size() > 0) {
		this->sortPodlaHmotnosti(prvejTriedy); //tu zotriedi palety podla hmotnosti
		for (Vozidlo* v : *pom) {
			for (Paleta* p : *prvejTriedy) {
				v->pridajPaletu(p);
				v->setJeNaCeste(true);
			}
		}
		//oznacia sa ako nezrealizovane 
		for (Paleta* p : *prvejTriedy) {
			if (!(p->jeNalozena())) {
				p->setZrealizovana(false);
				p->setDatumVratenia(datum);
				cout << "Nezrealizovana: " << p->getHmotnost() << endl;
			}
		}
	}
	//prejdem vsetky auta a ak nejake maju volne kapacity, nalozim zvysne palety
	if (ostatne->size() > 0) { //ak vobec mam nejake ostatne palety
		this->sortPodlaDatumu(ostatne);
		for (Vozidlo* v : *pom) {
			for (Paleta* p : *ostatne) {
				v->pridajPaletu(p);
				v->setJeNaCeste(true);
			}
		}
	}
	for (Vozidlo* v : *pom) { //ak nejake vozidlo zostalo prazdne, hod ho spat do prioritneho frontu vozidiel, kt mozu rozvazat
		if (v->jeNaCeste() == false) aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
	}
	//vymazem zo skladu nalozene a nezrealizovane palety
	//TU TO PADA KVOLI VYMAZAVANIU 
	//TOTO ESTE VYRIESIT
	/**
	for (Zasielka* z : *aSklad) {
	int pocet = z->getPalety()->size();
	for (int i = 0; i <= pocet; i++) {
	if (z->getPalety()->operator[](i)->jeNalozena() || !(z->getPalety()->operator[](i)->jeZrealizovana())) z->getPalety()->removeAt(i++);
	}
	}
	
	for (Zasielka* z : *aSklad) {
		for (Paleta* p : *z->getPalety()) {
			if (p->jeNalozena() || !(p->jeZrealizovana())) z->getPalety()->tryRemove(p);
		}
	}
	*/
	delete pom;
	delete prvejTriedy;
	delete ostatne;
}

void Firma::vylozenieVozidla(Vozidlo * vozidlo)
{
	int pocet = vozidlo->getPalety()->size();
	for (int i = 0; i < pocet; i++) {
		if (this->randBetween0and1() < 0.05) {
			Paleta *paleta = vozidlo->getPalety()->pop();
			paleta->setPrevzata(false);
			paleta->getDodavatel()->setMnozstvoNeprevzatych(1);
		}
		else vozidlo->getPalety()->pop();
	}
}

double Firma::randBetween0and1()
{
	std::mt19937_64 rng;
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	// initialize a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> unif(0, 1);
	// ready to generate random numbers
	const int nSimulations = 10;
	double currentRandomNumber = unif(rng);
	return currentRandomNumber;
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
		for (int i = 0; i < K->getObsah()->size(); i++) //kazdej palete sa nastavi datum prichodu, treba to kvoli metode 13
			K->getObsah()->operator[](i)->setDatumPrichodu(K->getDatumPrichodu());
	}
}

void Firma::vypisKamiony()
{
	for (Kamion* K : *aKamiony) {
		cout << K->getDatumPrichodu();
	}
}

void Firma::vylozeniePalietDoSkladu(Kamion* K) //PREROBIT, ABY KAZDY NOVY KAMION SA ZARADIL DO ZASIELOK, ABY SA NEVYTVARALI 
//NOVE ZASIELKY AK TAM UZ SU S TAKYM REGIONOM
{
	/**
	if (aSklad->size() == 0) {
		Datum* dnes = new Datum();
		//toto arraylist lebo tam aj hlavne pristupujem k prvkom
		ArrayList<int> *pom = new ArrayList<int>(); //v tomto poli su docasne ulozene zatial rozlisene regiony
		ArrayList<Zasielka*> *zasielky = new ArrayList<Zasielka*>(); //kvoli vyhladaniu na ktorom indexe sa dana zasielka v sklade nachadza,
		//aby sme jej potom mohli pridat palety, ktore patria pre jej region
		//toto bude linkedlist lebo tam len pridavam
		//int pocet;
			//AK V SKLADE NIC NIEJE, UROB TUTO VETVU
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
			if (K->getObsah()->operator[](i)->getHmotnost() <= vratMaxNosnost() && !(dnes->budePrvySkor(K->getObsah()->operator[](i)->getDatumDorucenia(), dnes->getDnesnyDatum())) || !(K->getObsah()->operator[](i)->jePrvejTriedy())) {
				if (velkost == 0) {
					Zasielka* zasielka = new Zasielka(K->getObsah()->operator[](i)->getRegion());
					//do kontajnera paliet zasielky pridam zasielku, ktora splna dany region
					zasielka->getPalety()->add(K->getObsah()->operator[](i)); //danu paletu pridam do zasielky
					pom->add(K->getObsah()->operator[](i)->getRegion()); //pridam ju do pomocneho pola kvoli rozliseniu regionu
					zasielky->add(zasielka);
					aSklad->add(zasielka); //zaroven ju pridam rovno do skladu
					//tu nemozem deletnut zasielku, lebo si ju zrusim
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
	else {
		*/
		//AK V UZ SU V SKLADE NEJAKE ZASIELKY, UROB TUTO VETVU: 
		Datum* dnes = new Datum();
		for (Paleta* p : *K->getObsah()) {
			bool zaradena = false;
			if (p->getHmotnost() <= vratMaxNosnost() && !(dnes->budePrvySkor(p->getDatumDorucenia(), dnes->getDnesnyDatum())) || !(p->jePrvejTriedy())) {
				for (Zasielka* z : *aSklad) {
					if (p->getRegion() == z->getRegion()) {
						//zarad paletu do danej zasielky
						z->getPalety()->add(p);
						//oznac paletu ako zaradenu
						zaradena = true;
						break;
					}
				}
				//if paleta nieje zaradena
				if (zaradena == false) {
					//vytvor novu zasielku
					Zasielka* zasielka = new Zasielka(p->getRegion());
					//zarad ju tam
					zasielka->getPalety()->add(p);
					aSklad->add(zasielka);
				}
			}
		}
		delete dnes;
	}
//}

void Firma::vypisSklad()
{
	cout << aSklad->size();
	cout << endl;
	for (Zasielka *Z : *aSklad) {
		cout << Z->getRegion();
		cout << endl;
		int pocet = Z->getPalety()->size();
		for (int i = 0; i < pocet; i++) {
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


void Firma::naplnenieVozidiel(string datum) //ESTE DAT VOZIDLU ATRIBUT CI JE NA CESTE,
//TYM UROBIM VLASTNE TO ABY SOM NEMUSELA VYMAZAT CELE VOZIDLO Z ROZVAZAJUCIH VOZIDIEL
{
	//ak zasielok t.j regionov je viac ako vozidiel, hned je jasne, ze sa nemozu nalozit vsetky palety
	bool mozuSaNalozit = true;
	//this->sortPodlaOpotrebovanosti(); //tu zoradi vozidla podla opotrebovanosti
	//ak sa nemozu nalozit z dovodu, ze je viac regionov ako vozidiel
	if (aSklad->size() > aRozvazajuceVozidla->size()) mozuSaNalozit = false;
	//inak skontroluj ci sa podla zadanych pravidiel daju nalozit vsetky palety
	//najskor sa vytvori pomocny arraylist, do ktoreho sa pridaju vozidla z prioritneho frontu
	ArrayList <Vozidlo*> *pom = new ArrayList<Vozidlo*>();
	int pocet = aRozvazajuceVozidla->size();
	for (int i = 0; i < pocet; i++) {
		pom->add(aRozvazajuceVozidla->pop()); //tu budu zotriedene podla opotrebovanosti
	}
	//ArrayList<Vozidlo*> *druhyPom = dynamic_cast<ArrayList<Vozidlo*>*>(pom->clone()); //tu si urobim jeho kopiu a tu poslem do 
	//metody nemozuSaNalozit()
	if (mozuSaNalozit) {
		for (Vozidlo* v : *pom) {
			cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie();
			for (Zasielka* z : *aSklad) {
				for (Paleta* p : *z->getPalety()) {
					v->mozemPridatPaletu(p);
				}
			}
		}
		//VYRESETOVANIE - kvoli metode mozemPridatPaletu()
		for (Vozidlo* v : *pom)
		{
			v->vynulujKolkoJeNalozene();
			v->resetRegion();
		}
		//ZISTENIE, CI SA DALI PRIDAT VSETKY PALETY
		int pocetNalozenych = 0;
		int pocetPaliet = 0;
		for (Zasielka* z : *aSklad) {
			for (Paleta* p : *z->getPalety()) {
				pocetPaliet++;
				if (p->jeNalozena()) pocetNalozenych++;
				p->setNalozena(false);
			}
		}
		//ak sa stane, ze co i len jedna paleta nebola nalozena, hned false
		if (pocetNalozenych < pocetPaliet) mozuSaNalozit = false;

		//ak sa mozu nalozit, naloz ich
		if (mozuSaNalozit) {
			cout << "mozu sa nalozit" << endl;
			for (Vozidlo* v : *pom) {
				for (Zasielka* z : *aSklad) {
					for (Paleta* p : *z->getPalety()) {
						v->pridajPaletu(p);
					}
				}
				v->setJeNaCeste(true);
			}
			/**
			//NA VYMAZAVANI TO PADA!!!!!!!!!!!!!!
			for (Zasielka* z : *aSklad) {
				for (Paleta* p : *z->getPalety()) {
					if (p->jeNalozena()) z->getPalety()->tryRemove(p);
				}
			}
			*/
			for (Vozidlo* v : *pom) { //ak nejake vozidlo zostalo prazdne, hod ho spat do prioritneho frontu vozidiel, kt mozu rozvazat
				if (v->jeNaCeste() == false) aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
			}
			delete pom; //tu sa vymaze pomocne pole, lebo uz ho nepotrebujem, lebo nejdem do vetvy nemozu sa nalozit 
		}
		//ak sa nemozu nalozit, pretoze sa nedaju nalozit rovno podla zadanych pravidiel, t.j vozidla su zoradene podla opotrebovanosti,
		//kazde ide iba do jedneho regionu a palety nesmu prekrocit nosnost vozidla
		else this->nemozuSaNalozitVsetky(datum, pom);
	}
	//ak sa nemozu nalozit z dovodu, ze je viac regionov ako vozidiel
	else this->nemozuSaNalozitVsetky(datum, pom);
}

