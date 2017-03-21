#include "Dodavatel.h"

Dodavatel::Dodavatel(string paObchodNaz, string paAdresa)
{
	aObchodnyNazov = paObchodNaz;
	aAdresa = paAdresa;
	aMnozstvoNeprevzatychPaliet = 0;
}
Dodavatel::~Dodavatel()
{
}

string Dodavatel::getObchodnyNazov() const
{
	return aObchodnyNazov;
}

string Dodavatel::getAdresaSidla() const
{
	return aAdresa;
}

int Dodavatel::getMnozstvoNeprevzatych()
{
	return aMnozstvoNeprevzatychPaliet;
}

void Dodavatel::setObchodnyNazov(string paObchodnyNazov)
{
	aObchodnyNazov = paObchodnyNazov;
}

void Dodavatel::setMnozstvoNeprevzatych(int paPocet)
{
	aMnozstvoNeprevzatychPaliet += paPocet;
}

string Dodavatel::toString()
{
	return "Obchodny nazov: " + aObchodnyNazov + ", adresa: " + aAdresa;
}

void Dodavatel::setAdresaSidla(string paAdresa)
{
	aAdresa = paAdresa;
}