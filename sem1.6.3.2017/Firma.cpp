#include "Firma.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "heap_monitor.h"

using std::ofstream;
using std::ifstream;

Firma::Firma()
{
	aEvidenciaVozidiel = new ArrayList<Vozidlo*>(5); //tu su uplne vsetky vozidla a sluzi na vypis
	aRozvazajuceVozidla = new PriorityQueue_Heap<Vozidlo*>(); //pf podla opotrebovanosti
	aVyradeneVozidla = new ExplicitQueue<Vozidlo*>(); 
	aSklad = new PriorityQueue_Heap<Paleta*>(); //tu su vsetky palety, ktore sa podarilo pridat do skladu, pf podla regionu
	aDodavatelia = new ArrayList<Dodavatel*>(10); //tu su vsetci dodavatelia, vypisujem ich 
	aKamiony = new ArrayList<Kamion*>(10); //tu su vsetky kamiony, sluzi na vypis
	aNezrealizovane = new ArrayList<Paleta*>(10); //prehliadam ich a vypisujem
	aNeprevzate = new ArrayList<Paleta*>(10); //dalej ich prehliadam
	aNezaevidovaliSaDoSkladu = new LinkedList<Paleta*>(); //tu su palety, ktore sa nepodarilo pridat do skladu, tie mozem aj deletnut
	//a toto mi nebude treba
	aEvidenciaPaliet = new ArrayList<Paleta*>(20); //kvoli vypisu a mazaniu, budu tu uplne vsetky palety, ktore kedy presli systemom
}


Firma::~Firma() // ????? 
{

	delete aNezaevidovaliSaDoSkladu;
	for (Paleta *p : *aEvidenciaPaliet) {
		if (p != nullptr) {
			delete p; 
		}
	}

	for (Kamion *k : *aKamiony) {
		if (k != nullptr) {
			delete k;
		}
	}
	delete aEvidenciaPaliet;
	for (Dodavatel *d : *aDodavatelia) {
		if (d != nullptr) {
			delete d;
		}
	}
	delete aDodavatelia;
	for (Vozidlo* v : *aEvidenciaVozidiel) { 
		if (v != nullptr) {
			delete v;
		}
	}
	delete aEvidenciaVozidiel;
	delete aKamiony;
	delete aNeprevzate;
	delete aNezrealizovane;
	delete aVyradeneVozidla;
	delete aRozvazajuceVozidla;
	delete aSklad;
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
			aEvidenciaVozidiel->add(vozidlo);
			cout << "Vozidlo sa uspesne pridalo" << endl;
		}
		else { 
			int velkost = aEvidenciaVozidiel->size();
			while ((i < velkost) && (datum->budePrvySkor(vozidlo->getDatum(), aEvidenciaVozidiel->operator[](i)->getDatum())))
			{
				i++;
			}
			aEvidenciaVozidiel->insert(vozidlo, i);
			aRozvazajuceVozidla->push(0,vozidlo);
			cout << "Vozidlo sa uspesne pridalo" << endl;
		}
		delete datum;
		return true;
	}
	else {
		cout << "Vozidlo s touto SPZ uz existuje" << endl;
		delete vozidlo;
		delete datum;
		return false;
	}

}

bool Firma::pridajNovehoDodavatela(Dodavatel *dod)
{
	int i = 0;
	bool pom = false;
	for (Dodavatel* D : *aDodavatelia) {
		if (D->getObchodnyNazov() == dod->getObchodnyNazov()) {
			pom = true;
			break;
		}
	}
	if (pom == false) {
		if (aDodavatelia->size() == 0) {
			aDodavatelia->add(dod);
			cout << "Dodavatel sa uspesne pridal" << endl;
		}
		else { //compare porovna lexikograficky 2 retazce
			int velkost = aDodavatelia->size();
			while (i < velkost && dod->getObchodnyNazov().compare(aDodavatelia->operator[](i)->getObchodnyNazov()) > 0)
			{
				i++;
			}
			aDodavatelia->insert(dod, i);
			cout << "Dodavatel sa uspesne pridal" << endl;
		}
		return true;
	}
	else {
		cout << "Dodavatel s tymto nazvom uz existuje" << endl;
		delete dod;
		return false;
	}
}

void Firma::vypisDodavatelov()
{
	for (Dodavatel* D : *aDodavatelia) {
		if (D != nullptr) cout << D->toString() << endl;
	}
}

void Firma::vypisPaletyZVozidielPoVylozeni() //iba na kontrolu
{
	for (Vozidlo* v : *aEvidenciaVozidiel) {
		if (v->jeNaCeste() && v!= nullptr) {
			ArrayList <Paleta*> *pom = new ArrayList<Paleta*>();
			cout << "Pocet paliet: " << v->getPalety()->size() << endl;
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
}


void Firma::vylozenieVozidla(Vozidlo * vozidlo, string datum) 
{
	if (vozidlo->jeNaCeste()) {
		int pocet = vozidlo->getPalety()->size(); //ak vo vozidle bude len 1 paleta tento cyklus netreba
		for (int i = 0; i < pocet; i++) {
			double cislo = this->randBetween0and1();
			if (cislo < 0.75) { //0.05
				Paleta *p = vozidlo->getPalety()->pop();
				p->setPrevzata(false);
				aNeprevzate->add(p);
				p->setDatumNeprevzatia(datum);
				p->setNalozena(false);
				vozidlo->setJeVylozene(true);
				cout << "Paleta: " << endl;
				if (p->jePrvejTriedy()) {
					cout << "Datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				}
				else cout << "Datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				cout << "Nebola prevzata zakaznikom " << endl;
			}
			else { 
				//tu ked bude odovzdana, tak ju mozem rovno deletnut
				Paleta *p = vozidlo->getPalety()->pop();
				p->setPrevzata(true);
				p->setNalozena(false);
				vozidlo->setJeVylozene(true);
				cout << "Paleta: " << endl;
				if (p->jePrvejTriedy()) {
					cout << "Datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				}
				else cout << "Datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				cout << "Bola uspesne prevzata zakaznikom " << endl;
			}
		}
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

void Firma::navratVozidla(Vozidlo *v)
{
	v->zvysOpotrebovanie(v->getRegion());
	v->setRegion(0); //resetovanie regionu
	v->setJeNaCeste(false); //uz nieje na ceste
	if (v->getOpotrebovanie() > 90) {
		aVyradeneVozidla->push(v); //ak viac ako 90, zaradi sa do frontu opotrebovanych
		cout << "Vozidlo bolo zaradene medzi opotrebovane vozidla" << endl;
	}
	else {
		aRozvazajuceVozidla->push(v->getOpotrebovanie(), v); //ak menej, zaradi sa do pr.frontu rozvazajucich vozidiel podla opotrebovanosti
		cout << "Vozidlo bolo zaradene medzi vozidla, ktore mozu rozvazat" << endl;
	}
}

void Firma::vyradenieVozidielZevidencie() // ?????
{
	int pocet = aVyradeneVozidla->size();
	if (pocet > 0) {
		for (int i = 0; i < pocet; i++) {
			Vozidlo *pom = aVyradeneVozidla->pop();
			for (Vozidlo * v : *aEvidenciaVozidiel) {
				if (v != nullptr) {
					if (pom == v) {
						cout << "Z evidencie sa vyradilo vozidlo: " << endl;
						cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie() << endl;
						v->setJeVyradene(true); // ??????
						break;
					}
				}
			}
		}
	}
	else cout << "Front vozidiel na vyradenie je prazdny" << endl;
}

void Firma::vymazanieDodavatela(Dodavatel * dod)
{
	for (Dodavatel* d : *aDodavatelia) {
		if (d == dod) d = nullptr;
	}
}

void Firma::vypisNezrealizovanePalety(string datumOd, string datumDo)
{
	if (aNezrealizovane->size() > 0) {
		cout << "Nezrealizovane palety v obdobi od " << datumOd << " do " << datumDo << ":" << endl;
		Datum *datum = new Datum();
		for (Paleta *p : *aNezrealizovane) {
			if (datum->jeDatumVIntervale(p->getDatumVratenia(), datumOd, datumDo))
				if (p->jePrvejTriedy()) {
					cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				}
				else cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
		}
		delete datum;
	}
	else {
		cout << "Nezrealizovane palety v obdobi od " << datumOd << " do " << datumDo << ":" << endl;
		cout << "NENASLI SA" << endl;
	}
}

void Firma::dodavatelSnajvacsimPoctomNeprevzatychPaliet(string datumOd, string datumDo)
//toto urobit inak, dodavatelovi nastavt datumNeprevzatia ?
{	
	if (aNeprevzate->size() > 0) {
		Datum *datum = new Datum();
		for (Paleta *p : *aNeprevzate) {
			if (datum->jeDatumVIntervale(p->getDatumNeprevzatia(), datumOd, datumDo)) p->getDodavatel()->setMnozstvoNeprevzatych(1);
		}
		int max = 0;
		Dodavatel *dod = nullptr;
		for (Dodavatel *d : *aDodavatelia) {
			if (d->getMnozstvoNeprevzatych() > max) {
				max = d->getMnozstvoNeprevzatych();
				dod = d;
			}
		}
		if (dod != nullptr) {
			cout << "Dodavatel s najvacsim poctom neprevzatych paliet v danom obdobi od " << datumOd << " do " << datumDo << ":" << endl;
			cout << dod->toString() << endl;
		}
		delete datum;
	}
	else {
		cout << "Dodavatel s najvacsim poctom neprevzatych paliet v danom obdobi od " << datumOd << " do " << datumDo << ":" << endl;
		cout << "NENASIEL SA" << endl;
	}
}

void Firma::vypisVozidlaPodlaDatumu() //vypise vsetky vozidla okrem vyradenych
{
	if (aEvidenciaVozidiel->size() > 0) {
		cout << "Evidencia vozidiel zoradena podla datumu zaradenia vozidla od najnovsich po najstarsie: " << endl;
		for (Vozidlo* v : *aEvidenciaVozidiel) {
			if (v != nullptr && v->jeVyradene() == false) {
				cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie() << endl;
			}
		}
	}
}

void Firma::ohlasKamion(Kamion* paKamion) //ohlasit kamion asi znamena nastavit datum prichodu kazdej palete
{
	aKamiony->add(paKamion); 
	for (Paleta* p : *paKamion->getObsah()) {
		//kazdej palete sa nastavi datum prichodu, treba to kvoli metode 13
		p->setDatumPrichodu(paKamion->getDatumPrichodu());
		aEvidenciaPaliet->add(p); //kazdu paletu pridaj do evidenciu paliet kvoli mazaniu pamate
	}
}

int Firma::vypisKamiony()
{
	int i = 0;
	int j = 0;
	for (Kamion* K : *aKamiony) {
		i++;
		if (K->jeVylozeny() == false) {
			j++;
			if (i > 1) cout << "" << endl;
			cout << "Kamion c. " << i << " ,datum prichodu: " << K->getDatumPrichodu() << ", pocet paliet: " << K->getObsah()->size() << endl;
			for (Paleta *p : *K->getObsah()) {
				if (p->jePrvejTriedy()) {
					cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
				}
				else cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;

			}
		}
	}
	return j;
}

int Firma::vypisVylozeneVozidla()
{
	int i = 0;
	int j = 0;
	for (Vozidlo *v : *aEvidenciaVozidiel) {
		i++;
		if (v->jeNaCeste() && v->jeVylozene()) {
			j++;
			cout << "Vozidlo c. " << i << ":" << endl;
			cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie() << endl;
		}
	}
	return j;
}

ArrayList<Kamion*>* Firma::getKamiony()
{
	return aKamiony;
}

ArrayList<Vozidlo*>* Firma::getVozidla()
{
	return aEvidenciaVozidiel;
}

int Firma::vypisNalozeneVozidla()
{
	int i = 0;
	int j = 0;
	for (Vozidlo *v : *aEvidenciaVozidiel) {
		i++;
		if (v->jeNaCeste() && v->jeVylozene() == false) {
			j++;
			cout << "Vozidlo c. " << i << ":" << endl;
			cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie() << endl;
		}
	}
	return j;
}

void Firma::vylozeniePalietDoSkladu(Kamion* K) 
{
	if (K->getObsah()->size() > 0) {
		K->setJeVylozeny(true);
		Datum* dnes = new Datum();
		int i = 0;
		for (Paleta* p : *K->getObsah()) {
			i++;
			if (p->getHmotnost() <= vratMaxNosnost()) {
				if ((this->zmenDatumNaInt(p->getDatumDorucenia()) > this->zmenDatumNaInt(dnes->getDnesnyDatum()) || !(p->jePrvejTriedy()))) {
					aSklad->push(p->getRegion(), p);
					p->setJeNaSklade(true);
					//aEvidenciaPaliet->add(p);
					cout << "Paleta c. " << i << " bola uspesne pridana do skladu" << endl;
				}
			}
			//tu ju deletnem
			else {
				cout << "Paleta c. " << i << " nesplna podmienky zaradenia do skladu" << endl;
				aNezaevidovaliSaDoSkladu->add(p);
			}//aby som si tu uchovala smerniky na ne, ked ich budem na konci mazat z pamate
		}
		delete dnes;
	}

	/**
	if (K->getObsah()->size() > 0) {
		Datum* dnes = new Datum();
		for (Paleta* p : *K->getObsah()) {
			bool zaradena = false;
			if (p->getHmotnost() <= vratMaxNosnost() && !(dnes->budePrvySkor(p->getDatumDorucenia(), dnes->getDnesnyDatum())) || !(p->jePrvejTriedy())) {
				if (aSklad->size() > 0) {
					for (Zasielka* z : *aSklad) {
						if (p->getRegion() == z->getRegion()) {
							//zarad paletu do danej zasielky
							z->getPalety()->add(p);
							//oznac paletu ako zaradenu
							zaradena = true;
							break;
						}
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
			else aNezaevidovaliSaDoSkladu->add(p); //aby som si tu uchovala smerniky na ne, ked ich budem na konci mazat z pamate
		}
		delete dnes;
	}
	*/
}

void Firma::vypisSklad() 
{
	cout << "Palety, ktore sa aktualne nachadzaju v sklade: " << endl;
	for (Paleta *p : *aEvidenciaPaliet) {
		if (p->jeAktualneNaSklade() && p != nullptr) {
			cout << "Region: " << p->getRegion() << ": " << endl;
			if (p->jePrvejTriedy()) {
				cout << "Datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
			}
			else cout << "Datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;		
		}
	}
}

double Firma::vratMaxNosnost()
{
	double max = 0.0;
	if (aEvidenciaVozidiel->size() > 0) {
		for (Vozidlo* V : *aEvidenciaVozidiel) {
			if (V != nullptr && V->jeVyradene() == false) {
				if (V->getNosnost() > max) max = V->getNosnost();
			}
		}
	}
	return max;
}


void Firma::naplnenieVozidiel(string datum) //takymto sposobom moze byt v kazdom vozidle len 1 paleta
{
	if (aSklad->isEmpty() == false) {
		//roztriedenie
		PriorityQueue_Heap<Paleta*> *prvejTriedy = new PriorityQueue_Heap<Paleta*>;
		PriorityQueue_Heap<Paleta*> *ostatne = new PriorityQueue_Heap<Paleta*>;
		while (aSklad->isEmpty() == false) {
			Paleta *paleta = aSklad->pop();
			if (paleta->jePrvejTriedy() && paleta->getDatumDorucenia() == datum) prvejTriedy->push(paleta->getHmotnost(), paleta);
			else ostatne->push(this->zmenDatumNaInt(paleta->getDatumPrichodu()), paleta);
		}
		//nakladanie
		//PriorityQueue_Heap<Vozidlo*> *prazdne = new PriorityQueue_Heap<Vozidlo*>;
		//toto je n ako n paliet, lebo prejdem vsetky palety a kazdu zaradim bud do auta, do nezrealizovanych alebo spat do skladu 
		while (prvejTriedy->isEmpty() == false) { //toto je najviac p*n , p je pocet paliet a n je pocet vozidiel
			//pretoze pre kazde vozidlo prejdem najviac p paliet kym nejaku z nich nalozim
			if (aRozvazajuceVozidla->isEmpty()) break;
			Vozidlo* v = aRozvazajuceVozidla->peek(); //takymto sposobom moze byt vo vozidle iba 1 paleta, ale optimalizovat nalozenie nieje nasa uloha 
			Paleta *p = prvejTriedy->peek();
			if (v != nullptr && p != nullptr) {
				if (p->getHmotnost() <= v->getNosnost()) { //kedze v nom bude len jedna paleta
					if (v->getRegion() == 0) v->setRegion(p->getRegion());
					if (v->getRegion() == p->getRegion()) {
						p->setNalozena(true);
						p->setJeNaSklade(false);
						cout << "Nalozena paleta: " << endl;
						if (p->jePrvejTriedy()) {
							cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
						}
						else cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
						v->getPalety()->push(prvejTriedy->pop()); //paletu pridaj do stacku auta
						//vozidlu nastavim ze je na ceste a popnem ho z rozvazajucich
						v->setJeNaCeste(true);
						v->setJeVylozene(false);
						aRozvazajuceVozidla->pop();
					}
				}
				else {
					//prazdne->push(v->getOpotrebovanie(), aRozvazajuceVozidla->pop());
					Paleta *p = prvejTriedy->pop();
					p->setZrealizovana(false);
					p->setDatumVratenia(datum);
					p->setJeNaSklade(false);
					aNezrealizovane->add(p); //ak sa nedala nalozit
				}
			}
		}
		while (prvejTriedy->isEmpty() == false) {
			Paleta *p = prvejTriedy->pop();
			p->setZrealizovana(false);
			p->setDatumVratenia(datum);
			aNezrealizovane->add(p); //ak sa nedala nalozit
		}
		//ak som presla vsetky palety a zostali mi volne vozidla, naloz ostatne
		while (ostatne->isEmpty() == false && aRozvazajuceVozidla->isEmpty() == false) { //prejde vsetky ostatne palety a zaradi bud do vozidla alebo spat do skladu
			Vozidlo* v = aRozvazajuceVozidla->peek();
			Paleta *p = ostatne->peek();
			if (v != nullptr && p != nullptr) {
				if (p->getHmotnost() <= v->getNosnost()) { //kedze v nom bude len jedna paleta
					if (v->getRegion() == 0) v->setRegion(p->getRegion());
					if (v->getRegion() == p->getRegion()) {
						p->setNalozena(true);
						p->setJeNaSklade(false);
						cout << "Nalozena paleta: " << endl;
						cout << "Region: " << p->getRegion() << ", datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
						v->getPalety()->push(ostatne->pop());
						v->setJeNaCeste(true);
						v->setJeVylozene(false);
						aRozvazajuceVozidla->pop();
					}
				}
				else {
					//inak ju vrat spat do skladu podla regionu
					Paleta *p = ostatne->pop();
					p->setJeNaSklade(true);
					aSklad->push(p->getRegion(), p);
				}
			}
		}
		//ak nejake neboli nalozene, vrat do skladu
		while (ostatne->isEmpty() == false) {
			Paleta *p = ostatne->pop();
			p->setJeNaSklade(true);
			aSklad->push(p->getRegion(), p);
		}
		delete prvejTriedy;
		delete ostatne;
	}
	else cout << "Sklad je prazdny" << endl;
	/**
	//pokracuj iba ak su k dispo nejake rozvazajuce vozidla
	int pocet = aRozvazajuceVozidla->size();
	if (pocet > 0) {
		//ak zasielok t.j regionov je viac ako vozidiel, hned je jasne, ze sa nemozu nalozit vsetky palety
		bool mozuSaNalozit = true;
		//this->sortPodlaOpotrebovanosti(); //tu zoradi vozidla podla opotrebovanosti
		//ak sa nemozu nalozit z dovodu, ze je viac regionov ako vozidiel
		if (aSklad->size() > aRozvazajuceVozidla->size()) mozuSaNalozit = false;
		//inak skontroluj ci sa podla zadanych pravidiel daju nalozit vsetky palety
		//najskor sa vytvori pomocny arraylist, do ktoreho sa pridaju vozidla z prioritneho frontu
		ArrayList <Vozidlo*> *pom = new ArrayList<Vozidlo*>();
		for (int i = 0; i < pocet; i++) {
			pom->add(aRozvazajuceVozidla->pop()); //tu budu zotriedene podla opotrebovanosti
		}
		//ArrayList<Vozidlo*> *druhyPom = dynamic_cast<ArrayList<Vozidlo*>*>(pom->clone()); //tu si urobim jeho kopiu a tu poslem do 
		//metody nemozuSaNalozit()
		if (mozuSaNalozit) {
			for (Vozidlo* v : *pom) {
				if (v != nullptr) { //pre istotu
					cout << "SPZ: " << v->getSPZ() << ", nosnost: " << v->getNosnost() << ", opotrebovanie: " << v->getOpotrebovanie();
					for (Zasielka* z : *aSklad) {
						for (Paleta* p : *z->getPalety()) {
							v->mozemPridatPaletu(p);
						}
					}
				}
			}
			//VYRESETOVANIE - kvoli metode mozemPridatPaletu()
			for (Vozidlo* v : *pom)
			{
				if (v != nullptr) { //pre istotu
					v->vynulujKolkoJeNalozene();
					v->resetRegion();
				}
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
							if (v->pridajPaletu(p)) v->setJeNaCeste(true);
						}
					}
				}
				/**
				//NA VYMAZAVANI TO PADA!!!!!!!!!!!!!!
				for (Zasielka* z : *aSklad) {
					for (Paleta* p : *z->getPalety()) {
						if (p->jeNalozena()) z->getPalety()->tryRemove(p);
					}
				}
				for (Vozidlo* v : *pom) { //ak nejake vozidlo zostalo prazdne, hod ho spat do prioritneho frontu vozidiel, kt mozu rozvazat
					if (v != nullptr && v->jeNaCeste() == false) aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
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
	*/
}
void Firma::ulozDodavatelovDoSuboru()
{
	std::ofstream myfile;
	myfile.open("dodavatelia.txt");
	for (Dodavatel* d: *aDodavatelia)
	{
		myfile << (d->getObchodnyNazov()) << endl;
		myfile << (d->getAdresaSidla()) << endl;
	}
	myfile << "#";
	myfile.close();
}

void Firma::nacitajDodavatelovZoSuboru()
{
	std::ifstream citac;
	citac.open("dodavatelia.txt");
	if (citac.fail())
	{
		cout << "Zlyhalo otvorenie suboru dodavatelia\n";
	}
	while (!citac.eof())
	{
		string obchodnyNazov, adresaDodavatela;
		getline(citac, obchodnyNazov);
		if (obchodnyNazov == "#") break;
		getline(citac, adresaDodavatela);
		if (obchodnyNazov != "" && adresaDodavatela != "")
		{
			aDodavatelia->add(new Dodavatel(obchodnyNazov,adresaDodavatela)); 
		}
	}
	citac.close();

}

bool Firma::uzObsahujeTohtoDodavatela(string nazov)
{
	for (Dodavatel *d : *aDodavatelia) {
		if (d->getObchodnyNazov() == nazov) return true;
	}
	return false;
}



void Firma::ulozEvidenciuVozidielDoSuboru()
{
	std::ofstream myfile;
	myfile.open("vozidla.txt");
	for (Vozidlo* v : *aEvidenciaVozidiel)
	{
		myfile << (v->getSPZ()) << endl;
		myfile << (v->getNosnost()) << endl;
		myfile << (v->getOpotrebovanie()) << endl;
		myfile << (v->getDatum()) << endl;
	}
	myfile << "#";
	myfile.close();

}

void Firma::nacitajVozidlaZoSuboru()
{
	std::ifstream citac;
	citac.open("vozidla.txt");
	if (citac.fail())
	{
		cout << "Zlyhalo otvorenie suboru vozidla\n";
	}
	while (!citac.eof())
	{
		string spz, nosnost, opotrebovanie, datum;
		getline(citac, spz);
		if (spz == "#") break;
		getline(citac, nosnost);
		getline(citac, opotrebovanie);
		getline(citac, datum);
		int o = atoi(opotrebovanie.c_str());
		int n = atoi(nosnost.c_str());
		if (spz != "")
		{
			Vozidlo *v = new Vozidlo(spz, n, o, datum);
			aEvidenciaVozidiel->add(v); 
			aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
		}
	}
	citac.close();
}

bool Firma::uzObsahujeTotoVozidlo(string spz)
{
	for (Vozidlo *v : *aEvidenciaVozidiel) {
		if (v->getSPZ() == spz) return true;
	}
	return false;
}

void Firma::ulozSkladDoSuboru()
{
	std::ofstream myfile;
	myfile.open("sklad.txt");
	for (Paleta* p : *aEvidenciaPaliet)
	{
		if (p->jeAktualneNaSklade()) {
			myfile << "paleta" << endl;
			myfile << (p->getDatumPrichodu()) << endl;
			myfile << (p->getRegion()) << endl;
			myfile << (p->getHmotnost()) << endl;
			myfile << (p->jePrvejTriedy()) << endl;
			myfile << (p->getDatumDorucenia()) << endl;
			myfile << (p->getDodavatel()->getObchodnyNazov()) << endl;
		}
	}
	myfile << "#";
	myfile.close();
}

void Firma::ulozNevylozeneKamionyDoSuboru()
{
	std::ofstream myfile;
	myfile.open("nevylozeneKamiony.txt");
	int i = 0;
	for (Kamion* K : *aKamiony) {
		if (K->jeVylozeny() == false) {
			if (i > 0) myfile << "kamion" << endl;
			myfile << (K->getDatumPrichodu()) << endl;
			i++;
			for (Paleta *p : *K->getObsah()) {
				myfile << "paleta" << endl;
				myfile << (p->getRegion()) << endl;
				myfile << (p->getHmotnost()) << endl;
				myfile << (p->jePrvejTriedy()) << endl;
				myfile << (p->getDatumDorucenia()) << endl;
				myfile << (p->getDodavatel()->getObchodnyNazov()) << endl;
			}
		}
	}
	myfile << "#";
	myfile.close();
}

void Firma::ulozNalozeneVozidlaDoSuboru()
{
	std::ofstream myfile;
	myfile.open("nalozeneVozidla.txt");
	for (Vozidlo* v : *aEvidenciaVozidiel)
	{
		if (v->jeNaCeste() && v->jeVylozene() == false) {
			myfile << (v->getSPZ()) << endl;
			myfile << (v->getNosnost()) << endl;
			myfile << (v->getOpotrebovanie()) << endl;
			myfile << (v->getDatum()) << endl;
		}
	}
	myfile << "#";
	myfile.close();
}

void Firma::ulozVylozeneVozidlaDoSuboru()
{
	std::ofstream myfile;
	myfile.open("vylozeneVozidla.txt");
	for (Vozidlo* v : *aEvidenciaVozidiel)
	{
		if (v->jeNaCeste() && v->jeVylozene()) {
			myfile << (v->getSPZ()) << endl;
			myfile << (v->getNosnost()) << endl;
			myfile << (v->getOpotrebovanie()) << endl;
			myfile << (v->getDatum()) << endl;
		}
	}
	myfile << "#";
	myfile.close();
}

void Firma::ulozEvidenciuDoSuboru()
{
	this->ulozDodavatelovDoSuboru();
	this->ulozEvidenciuVozidielDoSuboru();
	this->ulozSkladDoSuboru();
	this->ulozNevylozeneKamionyDoSuboru();
	//this->ulozNalozeneVozidlaDoSuboru();
	//this->ulozVylozeneVozidlaDoSuboru();
}

void Firma::nacitajSkladZoSuboru()
{
	std::ifstream citac;
	citac.open("sklad.txt");
	if (citac.fail())
	{
		cout << "Zlyhalo otvorenie suboru sklad\n";
	}
	while (!citac.eof())
	{
		string paleta, region, hmotnost, trieda, datum, nazovDod, prichod;
		getline(citac, paleta);
		if (paleta == "paleta") {
			getline(citac, prichod);
			getline(citac, region);
			getline(citac, hmotnost);
			getline(citac, trieda);
			getline(citac, datum);
			getline(citac, nazovDod);
		}
		else if (paleta == "#") break;
		bool prvejTriedy;
		if (trieda == "1") prvejTriedy = true;
		else prvejTriedy = false;
		Dodavatel *d = this->vyhladajDodavatelaPodlaNazvu(nazovDod);
		Paleta * p = new Paleta(atoi(region.c_str()), atoi(hmotnost.c_str()), prvejTriedy, datum, d);
		p->setDatumPrichodu(prichod);
		aEvidenciaPaliet->add(p);
		aSklad->push(p->getHmotnost(), p);
		p->setJeNaSklade(true);
	}
	citac.close();
}

void Firma::nacitajNevylozeneKamionyZoSuboru()
{
	std::ifstream citac;
	citac.open("nevylozeneKamiony.txt");
	if (citac.fail())
	{
		cout << "Zlyhalo otvorenie suboru sklad\n";
	}
	Kamion *k = nullptr;
	while (!citac.eof())
	{
		string paleta, datumKamionu, region, hmotnost, trieda, datum, nazovDod;
		string test = "";
		if (test == "#") break;
		getline(citac, datumKamionu);
		if (datumKamionu == "#") break;
		k = new Kamion(datumKamionu);
		getline(citac, paleta);
		while (test != "kamion") {
			if (paleta == "paleta" || test == "paleta") {
				if (test == "#") break;
				getline(citac, region);
				getline(citac, hmotnost);
				getline(citac, trieda);
				getline(citac, datum);
				getline(citac, nazovDod);
				bool prvejTriedy;
				if (trieda == "1") prvejTriedy = true;
				else prvejTriedy = false;
				Dodavatel *d = this->vyhladajDodavatelaPodlaNazvu(nazovDod);
				Paleta * p = new Paleta(atoi(region.c_str()), atoi(hmotnost.c_str()), prvejTriedy, datum, d);
				p->setDatumPrichodu(datumKamionu);
				k->getObsah()->add(p);
				aEvidenciaPaliet->add(p);
				getline(citac, test);
			}
		}
		aKamiony->add(k);
	}
	citac.close();
}

void Firma::vypisEvidenciuPaliet()
{
	for (Paleta* p : *aEvidenciaPaliet) {
		cout << "Paleta s hmotnostou: " << p->getHmotnost() << endl;
	}
}

int Firma::zmenDatumNaInt(string paDatum)
{
	string dni = paDatum.substr(0, 2);
	string mesiace = paDatum.substr(3, 2);
	string roky = paDatum.substr(6, 4);

	int cdni = atoi(dni.c_str());
	int cmesiace = atoi(mesiace.c_str());
	int croky = atoi(roky.c_str());

	int cislo = croky * 10000 + cmesiace * 100 + cdni;
	//cout << cislo << endl;
	return cislo;

}

Dodavatel * Firma::vyhladajDodavatelaPodlaNazvu(string nazov)
{
	for (Dodavatel *dod : *aDodavatelia) {
		if (dod->getObchodnyNazov() == nazov) return dod;
	}
	return nullptr;
}
