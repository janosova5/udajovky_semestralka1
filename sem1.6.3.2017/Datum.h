#pragma once
#include <ctime>
#include <string>
#include "ArrayList.h"

using std::time_t;
using std::string;
using std::to_string;
using DS::ArrayList;

class Datum

{

public:
	Datum();
	~Datum();
	string getDnesnyDatum();
	bool budePrvySkor(string paPrvyDat, string paDruhyDat);
	bool jeDatumVIntervale(string paSkusanyDatum, string paDatumOd, string paDatumDo);
	string getZajtra();

};
