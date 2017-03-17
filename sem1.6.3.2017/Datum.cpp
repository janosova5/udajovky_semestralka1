#include "Datum.h"
#include <iostream>

using std::cout;

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
	nowLocal = *localtime(&now);
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

bool Datum::jeDatumZajtra(string paDatum)
{
	if (paDatum.size() < 10)
	{
		std::cout << "ZLY FORMAT DATUMU !!! ma to byt: napr 01.12.2016";
		throw std::invalid_argument("Zly format datumu zadaj ho vo formate 08.12.2016");
	}

	string dni = paDatum.substr(0, 2);
	string mesiace = paDatum.substr(3, 2);
	string roky = paDatum.substr(6, 4);

	int odovzd_dni = atoi(dni.c_str());
	int odovzd_mesiace = atoi(mesiace.c_str());
	int odovzd_roky = atoi(roky.c_str());

	time_t now;
	tm nowLocal;

	now = time(NULL);
	nowLocal = *localtime(&now);
	// mesiace +1 roky + 1900 testik
	int dniTeras, mesiaceTeras, rokyTeras;
	dniTeras = (int)nowLocal.tm_mday;
	mesiaceTeras = (int)nowLocal.tm_mon;
	mesiaceTeras++; // zvecsene koli funkcnosti 
	rokyTeras = (int)nowLocal.tm_year;
	rokyTeras += 1900; // zvecsene koli funkcnosti

	int pomocnaMesiace = mesiaceTeras; // lebo potrebujem menit aj mesiac 
	switch (pomocnaMesiace)
	{
	case 1: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 2; break;
		}

	}

	case 2: {
		if (dniTeras <= 28) { dniTeras += 1; break; }

		if (dniTeras == 29)
		{
			dniTeras = 1; mesiaceTeras = 3; break;
		}

	}

	case 3: {
		if (dniTeras <= 30) { dniTeras += 1; break; }
		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 4; break;
		}

	}

	case 4: {
		if (dniTeras <= 29) { dniTeras += 1; break; }

		if (dniTeras == 30)
		{
			dniTeras = 1; mesiaceTeras = 5; break;
		}

	}

	case 5: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 6; break;
		}

	}

	case 6: {
		if (dniTeras <= 29) { dniTeras += 1; break; }

		if (dniTeras == 30)
		{
			dniTeras = 1; mesiaceTeras = 7; break;
		}

	}

	case 7: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 8; break;
		}

	}

	case 8: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 9; break;
		}

	}

	case 9: {
		if (dniTeras <= 29) { dniTeras += 1; break; }

		if (dniTeras == 30)
		{
			dniTeras = 1; mesiaceTeras = 10; break;
		}

	}

	case 10: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 11; break;
		}

	}

	case 11: {
		if (dniTeras <= 29) { dniTeras += 1; break; }

		if (dniTeras == 30)
		{
			dniTeras = 1; mesiaceTeras = 12; break;
		}

	}

	case 12: {
		if (dniTeras <= 30) { dniTeras += 1; break; }

		if (dniTeras == 31)
		{
			dniTeras = 1; mesiaceTeras = 1; rokyTeras++; break;
		}

	}
	}

	if (odovzd_roky == rokyTeras &&
		odovzd_mesiace == mesiaceTeras &&
		odovzd_dni == dniTeras)
	{
		return true;
	}
	else {
		return false;
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
