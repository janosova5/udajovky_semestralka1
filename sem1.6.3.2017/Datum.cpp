#include "Datum.h"
#include <iostream>
#include "Array.h"

using std::cout;
using std::array;

Datum::Datum()
{
}




Datum::~Datum()
{
}

string Datum::getDnesnyDatum()
{
	time_t now;
	tm nowLocal;

	now = time(NULL);
	nowLocal = *localtime(&now); //warning
	// mesiace +1 roky + 1900 
	int dni, mesiace, roky;
	dni = (int)nowLocal.tm_mday;
	mesiace = (int)nowLocal.tm_mon;
	mesiace++;
	roky = (int)nowLocal.tm_year;
	roky += 1900;

	string dniStr, mesiaceStr;

	if (dni < 10)
	{
		dniStr = "0" + to_string(dni);
	}
	else {
		dniStr = to_string(dni);
	}

	if (mesiace < 10)
	{
		mesiaceStr = "0" + to_string(mesiace);
	}
	else {
		mesiaceStr = to_string(mesiace);
	}


	string s_dnesnyDatum = dniStr + "." + mesiaceStr + "." + to_string(roky);
	return s_dnesnyDatum;

}


bool Datum::budePrvySkor(string paPrvyDat, string paDruhyDat)
{

	if (paPrvyDat.size() < 10 || paDruhyDat.size() < 10)
	{
		std::cout << "ZLY FORMAT DATUMU !!! ma to byt: napr 01.12.2016";
		throw std::invalid_argument("Zly format datumu zadaj ho vo formate 08.12.2016");
	}

	string dni1 = paPrvyDat.substr(0, 2);
	string mesiace1 = paPrvyDat.substr(3, 2);
	string roky1 = paPrvyDat.substr(6, 4);

	int dni_1 = atoi(dni1.c_str());
	int mesiace_1 = atoi(mesiace1.c_str());
	int roky_1 = atoi(roky1.c_str());

	string dni2 = paDruhyDat.substr(0, 2);
	string mesiace2 = paDruhyDat.substr(3, 2);
	string roky2 = paDruhyDat.substr(6, 4);

	int dni_2 = atoi(dni2.c_str());
	int mesiace_2 = atoi(mesiace2.c_str());
	int roky_2 = atoi(roky2.c_str());


	if (roky_1 < roky_2)
	{
		return true;
	}
	else {
		if (roky_1 > roky_2)
		{
			return false;
		}

		if (mesiace_1 < mesiace_2)
		{
			return true;
		}
		else {
			if (mesiace_1 > mesiace_2)
			{
				return false;
			}

			if (dni_1 < dni_2)
			{
				return true;
			}
			else {
				return false;
			}
		}




	}
}


bool Datum::jeDatumVIntervale(string paSkusanyDatum, string paDatumOd, string paDatumDo)
{

	if (paDatumDo.size() < 10 || paDatumOd.size() < 10 || paSkusanyDatum.size() < 10)
	{
		std::cout << "ZLY FORMAT DATUMU !!! ma to byt: napr 01.12.2016";
		throw std::invalid_argument("Zly format datumu zadaj ho vo formate 08.12.2016");
	}


	// premienam skusany na dni od roku 2000  "12.10.2016"
	string dniSkusaneho = paSkusanyDatum.substr(0, 2);
	string mesiaceSkusaneho = paSkusanyDatum.substr(3, 2);
	string rokySkusajuceho = paSkusanyDatum.substr(8, 2); // je tu len 16 

	int pocetDniSkusaneho = (atoi(rokySkusajuceho.c_str()) * 365);
	pocetDniSkusaneho += (atoi(mesiaceSkusaneho.c_str()) * 30);
	pocetDniSkusaneho += atoi(dniSkusaneho.c_str());

	// premienam datumOD na dni od roku 2000  "12.10.2016"
	string dniOd = paDatumOd.substr(0, 2);
	string mesiaceOd = paDatumOd.substr(3, 2);
	string rokyOd = paDatumOd.substr(8, 2); // je tu len 16 

	int pocetDniOd = (atoi(rokyOd.c_str()) * 365);
	pocetDniOd += (atoi(mesiaceOd.c_str()) * 30);
	pocetDniOd += atoi(dniOd.c_str());

	// premienam DatumDO na dni od roku 2000  "12.10.2016"
	string dniDo = paDatumDo.substr(0, 2);
	string mesiaceDo = paDatumDo.substr(3, 2);
	string rokyDo = paDatumDo.substr(8, 2); // je tu len 16 

	int pocetDniDo = (atoi(rokyDo.c_str()) * 365);
	pocetDniDo += (atoi(mesiaceDo.c_str()) * 30);
	pocetDniDo += atoi(dniDo.c_str());

	if (pocetDniOd <= pocetDniSkusaneho && pocetDniSkusaneho <= pocetDniDo)
	{
		return true;
	}

	return false;


}

string Datum::getZajtra()
{
	ArrayList<int> *pole = new ArrayList<int>(12);
	pole->add(31);
	pole->add(28);
	pole->add(31);
	pole->add(30);
	pole->add(31);
	pole->add(30);
	pole->add(30);
	pole->add(31);
	pole->add(30);
	pole->add(31);
	pole->add(30);
	pole->add(31);
	string dnes = this->getDnesnyDatum();
	string dni = dnes.substr(0, 2);
	string mesiace = dnes.substr(3, 2);
	string roky = dnes.substr(6, 4);

	int dnes_dni = atoi(dni.c_str());
	int dnes_mesiace = atoi(mesiace.c_str());
	int dnes_roky = atoi(roky.c_str());

	int zajtra_dni = 0;
	int zajtra_mes = 0;
	int zajtra_rok = 0;
	if (dnes_dni + 1 > pole->operator[](dnes_mesiace - 1)) {
		zajtra_dni = 1;
		if (dnes_mesiace < 12) {
			zajtra_mes = dnes_mesiace + 1;
			zajtra_rok = dnes_roky;
		}
		else {
			zajtra_mes = 1;
			zajtra_rok = dnes_roky + 1;
		}
	}
	else {
		zajtra_dni = dnes_dni + 1;
		zajtra_mes = dnes_mesiace;
		zajtra_rok = dnes_roky;
	}
	string dniStr = "";
	if(zajtra_dni < 10) dniStr = "0" + to_string(zajtra_dni);
	else dniStr = to_string(zajtra_dni);
	string mesStr = "";
	if(zajtra_mes < 10)  mesStr = "0" + to_string(zajtra_mes);
	else mesStr = to_string(zajtra_mes);
	string rokStr = to_string(zajtra_rok);
	string zajtra = dniStr + "." + mesStr + "." + rokStr;
	delete pole;
	return zajtra;
}
