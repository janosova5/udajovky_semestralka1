#pragma once
#include <ctime>
#include <string>

using std::time_t;
using std::string;
using std::to_string;

class Datum

{

public:
	Datum();
	~Datum();
	string getDnesnyDatum();
	bool budePrvySkor(string paPrvyDat, string paDruhyDat);
	bool jeDatumZajtra(string paDatum);
	bool jeDatumVIntervale(string paSkusanyDatum, string paDatumOd, string paDatumDo);

};
