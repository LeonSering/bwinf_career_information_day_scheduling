#ifndef CVERANSTALTUNG_H_
#define CVERANSTALTUNG_H_

#include "cAngebot.h"
#include "cTeilnehmer.h"

class cVeranstaltung
{
public:
	cVeranstaltung(int id = 0, cAngebot * typ = 0, int termin = 0);
	~cVeranstaltung();
	
	void TeilnehmerHinzufuegen(cTeilnehmer * teilnehmer);
	
	int getId() { return itsId; }
	int getTermin() { return itsTermin; }
	cAngebot * getTyp() { return itsTyp; }
	
	
	int getAnzTeilnehmer() {return itsAnzTeilnehmer; }
	cTeilnehmer * getTeilnehmer(int i);
	void Ausgeben();  // fuer die Konsole
	
private:
	int itsId; // auch Veranstaltungen werden seperat durchnummeriert
	cAngebot * itsTyp;  // Das Angebot, von der Sorte die Veranstaltung ist
	
	int itsTermin; // 0: unbelegt; 1 - 4: Termin 1 bis 4
	
	int itsAnzTeilnehmer;
	cTeilnehmer ** itsTeilnehmer; // Die Teilnehmer, die bei dieser Veranstaltung teilnehmen.
		// Ein Zeiger auf ein Array von Zeigern!!!
};

#endif /*CVERANSTALTUNG_H_*/
