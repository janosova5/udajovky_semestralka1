#pragma once

#include <iostream>
#include <string>

using std::string;

class Dodavatel
{
private:
	string aObchodnyNazov;
	string aAdresa;
	int aMnozstvoNeprevzatychPaliet;
public:
	Dodavatel() {};
	Dodavatel(string paObchodNaz, string paAdresa);
	~Dodavatel();
	string getObchodnyNazov()  const;
	string getAdresaSidla() const;
	int getMnozstvoNeprevzatych();
	friend bool operator ==(Dodavatel a, Dodavatel b);
	void setAdresaSidla(string paAdresa);
	void setObchodnyNazov(string paObchodnyNazov);
	void setMnozstvoNeprevzatych(int paPocet);
	string toString();
};

inline bool operator ==(Dodavatel a, Dodavatel b)
{
	return false;
}
