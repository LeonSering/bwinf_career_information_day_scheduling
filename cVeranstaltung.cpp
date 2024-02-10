#include "cVeranstaltung.h"

cVeranstaltung::cVeranstaltung(int id, cAngebot * typ, int termin):
	itsId (id),
	itsTyp (typ),
	itsTermin (termin)
{
	itsAnzTeilnehmer = 0;
	itsTeilnehmer = new cTeilnehmer*[itsAnzTeilnehmer]; // Denklariert eine neues Array von Zeigern auf cTeilnehmer-Objekte und laesst itsTeilnehmer darauf zeigen
}

cVeranstaltung::~cVeranstaltung()
{
}

void cVeranstaltung::TeilnehmerHinzufuegen(cTeilnehmer * teilnehmer) {
	itsAnzTeilnehmer++;
	cTeilnehmer ** tempTeilnehmer = new cTeilnehmer*[itsAnzTeilnehmer];
	
	for (int i = 0; i < itsAnzTeilnehmer -1; i++)
		tempTeilnehmer[i] = itsTeilnehmer[i];	
	delete [] itsTeilnehmer;
	
	tempTeilnehmer[itsAnzTeilnehmer -1] = teilnehmer;
	itsTeilnehmer = tempTeilnehmer;
}

cTeilnehmer * cVeranstaltung::getTeilnehmer(int i) {  // gibt einen Zeiger auf den i-ten Teilnehmer zurueck
	if (i < itsAnzTeilnehmer)
		return itsTeilnehmer[i];
	else
		return 0;
}


void cVeranstaltung::Ausgeben() {
	cout << "Veranstaltung " << itsId << ": Typ: " << itsTyp->getName().toStdString() << " (" << itsTyp->getId() << ") | " << itsAnzTeilnehmer << " Teilnehmer: ";
	for (int i = 0; i< itsAnzTeilnehmer; i++)
		cout << itsTeilnehmer[i]->getName().toStdString() << " (" << itsTeilnehmer[i]->getId() << ") | ";
	cout << endl; 
}
