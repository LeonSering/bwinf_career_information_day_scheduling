#include "cTeilnehmer.h"

cTeilnehmer::cTeilnehmer() {
	itsId = -2;  // objekt besitzt noch keinen inhalt
	itsAnzWuensche = 0;
	itsName = "leeres Objekt";
	itsWuensche = new cAngebot[0];
}

cTeilnehmer::cTeilnehmer(int id, int anzWuensche, cAngebot * wuensche, QString name) {
	if (name == QString::fromUtf8("Schüler"))
		itsName = QString::fromUtf8("Schüler ") + QString::number(id);
	else
		itsName = name;
	itsId = id;
	itsAnzWuensche = anzWuensche;
	
	itsWuensche = new cAngebot[itsAnzWuensche];
	
	for (int i = 0; i < itsAnzWuensche; i++)
		itsWuensche[i] = wuensche[i];
}

cTeilnehmer::~cTeilnehmer() {
}

cAngebot * cTeilnehmer::getWuensche() {		
	return itsWuensche;
}

void cTeilnehmer::Ausgeben() {
	cout << "Teilnehmer " << itsId << ": \"" << itsName.toStdString() << "\" Wünsche: ";
	for (int i = 0; i< itsAnzWuensche; i++)
		cout << itsWuensche[i].getName().toStdString() << " (" << itsWuensche[i].getId() << ") | ";
	cout << endl; 
}
