#include "Firma.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using std::ofstream;
using std::ifstream;

Firma::Firma()
{
	aEvidenciaVozidiel = new ArrayList<Vozidlo*>(5);
	aRozvazajuceVozidla = new PriorityQueue_Heap<Vozidlo*>();
	aVyradeneVozidla = new ExplicitQueue<Vozidlo*>(); 
	aSklad = new ArrayList<Zasielka*>(5);
	aDodavatelia = new ArrayList<Dodavatel*>(5);
	aKamiony = new LinkedList<Kamion*>();
	aNezrealizovane = new ArrayList<Paleta*>(5);
	aNeprevzate = new ArrayList<Paleta*>(5);
	aNezaevidovaliSaDoSkladu = new LinkedList<Paleta*>();
}


Firma::~Firma() // ????? 
{
	for (Vozidlo* v : *aEvidenciaVozidiel) { //tymto sa deletnu vsetky vozidla, ktore sa nachadzaju realne v pamati
		if (v != nullptr) {
			delete v;
		}
	}
	delete aEvidenciaVozidiel;
	//atd 
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
		cout << "Vozidlo s touto SPZ uz existuje";
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
		if (D != nullptr) cout << D->toString() << endl;
	}
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
		if (v->jeNaCeste() && v!= nullptr) {
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
			if (p != nullptr && p->jeAktualneNaSklade()) {
				if (p->jePrvejTriedy() && p->getDatumDorucenia() == datum) prvejTriedy->add(p);
				else ostatne->add(p);
			}
		}
	}
	if (prvejTriedy->size() > 0) {
		this->sortPodlaHmotnosti(prvejTriedy); //tu zotriedi palety podla hmotnosti
		for (Vozidlo* v : *pom) {
			if (v != nullptr) {
				for (Paleta* p : *prvejTriedy) {
					if (v->pridajPaletu(p)) v->setJeNaCeste(true);
				}
			}
		}
		//oznacia sa ako nezrealizovane 
		for (Paleta* p : *prvejTriedy) {
			if (!(p->jeNalozena())) {
				p->setZrealizovana(false);
				aNezrealizovane->add(p);
				p->setDatumVratenia(datum);
				cout << "Nezrealizovana: " << p->getHmotnost() << endl;
			}
		}
	}
	//prejdem vsetky auta a ak nejake maju volne kapacity, nalozim zvysne palety
	if (ostatne->size() > 0) { //ak vobec mam nejake ostatne palety
		this->sortPodlaDatumu(ostatne);
		for (Vozidlo* v : *pom) {
			if (v != nullptr) {
				for (Paleta* p : *ostatne) {
					if (v->pridajPaletu(p)) v->setJeNaCeste(true);
				}
			}
		}
	}
	for (Vozidlo* v : *pom) { //ak nejake vozidlo zostalo prazdne, hod ho spat do prioritneho frontu vozidiel, kt mozu rozvazat
		if (v != nullptr && v->jeNaCeste() == false) aRozvazajuceVozidla->push(v->getOpotrebovanie(), v);
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

void Firma::vylozenieVozidla(Vozidlo * vozidlo, string datum) 
{
	if (vozidlo->jeNaCeste()) {
		int pocet = vozidlo->getPalety()->size();
		for (int i = 0; i < pocet; i++) {
			if (this->randBetween0and1() < 0.75) {
				Paleta *paleta = vozidlo->getPalety()->pop();
				paleta->setPrevzata(false);
				aNeprevzate->add(paleta);
				paleta->setDatumNeprevzatia(datum);
				paleta->setNalozena(false);
				//paleta->getDodavatel()->setMnozstvoNeprevzatych(1);
			}
			else {
				Paleta *paleta = vozidlo->getPalety()->pop();
				paleta->setPrevzata(true);
				paleta->setNalozena(false);
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
	v->zvysOpotrebovanie(v->getRegion()+90);
	v->setRegion(0); //resetovanie regionu
	v->setJeNaCeste(false); //uz nieje na ceste
	if (v->getOpotrebovanie() > 90) aVyradeneVozidla->push(v); //ak viac ako 90, zaradi sa do frontu opotrebovanych
	else aRozvazajuceVozidla->push(v->getOpotrebovanie(), v); //ak menej, zaradi sa do pr.frontu rozvazajucich vozidiel podla opotrebovanosti
	cout << aVyradeneVozidla->peek()->getSPZ() << endl; //vypise sa
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
						cout << v->getSPZ() << endl; //vozidlo sa odstrani uplne, uz nema v pamati existovat ?
						//delete v;
						//v = nullptr; //ked urobim toto a tu, tak k vozidlu sa uz nedostanem
						//cout << v->getSPZ() << endl;
						v->setJeVyradene(true); // ??????
						break;
					}
				}
			}
		}
	}
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
				cout << "Datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
		}
		delete datum;
	}
	else {
		cout << "Nezrealizovane palety v obdobi od " << datumOd << " do " << datumDo << ":" << endl;
		cout << "NENASLI SA" << endl;
	}
}

void Firma::dodavatelSnajvacsimPoctomNeprevzatychPaliet(string datumOd, string datumDo)
{	
	if (aNeprevzate->size() > 0) {
		Datum *datum = new Datum();
		for (Paleta *p : *aNeprevzate) {
			if (datum->jeDatumVIntervale(p->getDatumNeprevzatia(), datumOd, datumDo)) p->getDodavatel()->setMnozstvoNeprevzatych(1);
		}
		int max = 0;
		Dodavatel *dod;
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
	if (aEvidenciaVozidiel->size()) {
		cout << "Evidencia vozidiel zoradena podla datumu zaradenia vozidla: " << endl;
		for (Vozidlo* V : *aEvidenciaVozidiel) {
			if (V != nullptr && V->jeVyradene() == false) {
				cout << "SPZ: " << V->getSPZ() << ", nosnost: " << V->getNosnost() << ", opotrebovanie: " << V->getOpotrebovanie() << endl;
			}
		}
	}
}

void Firma::ohlasKamion(Kamion* paKamion) 
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

void Firma::vylozeniePalietDoSkladu(Kamion* K) 
{
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
}

void Firma::vypisSklad() //este toto
{
	if (aSklad->size() > 0) {
		cout << "Palety, ktore sa aktualne nachadzaju v sklade: " << endl;
		//cout << aSklad->size();
		//cout << endl;
		for (Zasielka *z : *aSklad) {
			//cout << "Palety pre region: " << z->getRegion() << endl;
			for (Paleta *p : *z->getPalety()) {
				if (p->jeAktualneNaSklade()) {
					cout << "Region: " << z->getRegion() << ": " << endl;
					if (p->jePrvejTriedy()) {
						cout << "Datum prichodu: " << p->getDatumPrichodu() << ", datum dorucenia: " << p->getDatumDorucenia() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;
					}
					else cout << "Datum prichodu: " << p->getDatumPrichodu() << ", hmotnost: " << p->getHmotnost() << ", dodavatel: " << p->getDodavatel()->toString() << endl;		
				}
			}
		}
	}
}

double Firma::vratMaxNosnost()
{
	double max = 0.0;
	if (aEvidenciaVozidiel->size() > 0) {
		for (Vozidlo* V : *aEvidenciaVozidiel) {
			if (V != nullptr) {
				if (V->getNosnost() > max) max = V->getNosnost();
			}
		}
	}
	return max;
}


void Firma::naplnenieVozidiel(string datum) 
{
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
				*/
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

	myfile.close();
}

void Firma::nacitajDodavatelovZoSuboru()
{
	std::ifstream citac;
	//aDodavatelia = new ArrayList<Dodavatel*>();
	citac.open("dodavatelia.txt");
	if (citac.fail())
	{
		cout << "Zlyhalo otvorenie suboru dodavatelia\n";
	}
	while (!citac.eof())
	{
		string obchodnyNazov, adresaDodavatela;
		getline(citac, obchodnyNazov);
		getline(citac, adresaDodavatela);
		if (obchodnyNazov != "" && adresaDodavatela != "")
		{
			if(!(this->uzObsahujeTohtoDodavatela(obchodnyNazov))) aDodavatelia->add(new Dodavatel(obchodnyNazov,adresaDodavatela)); //ak sa este nenachadza v evidencii dodavatelov
		}
	}
	for (int i = 0; i < aDodavatelia->size(); i++)
	cout << (*aDodavatelia)[i]->getObchodnyNazov() << "\n";

}

bool Firma::uzObsahujeTohtoDodavatela(string nazov)
{
	for (Dodavatel *d : *aDodavatelia) {
		if (d->getObchodnyNazov() == nazov) return true;
	}
	return false;
}
