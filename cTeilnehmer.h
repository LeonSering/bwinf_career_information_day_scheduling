#ifndef CTEILNEHMER_H_
#define CTEILNEHMER_H_

#include <iostream>
using namespace std;

#include <QString>

#include "cAngebot.h"

class cTeilnehmer
{
public:
	cTeilnehmer();
	cTeilnehmer(int id, int anzWuensche, cAngebot * wuensche, QString name = QString::fromUtf8("Schüler"));
	~cTeilnehmer();
	
	cAngebot * getWuensche();
	
	void Ausgeben();  // fuer die Konsole
	
	int getId() { return itsId; }
	QString getName() { return itsName; }
	

	
private:
	int itsId; // Teilnehmer werden auch durchnummeriert
	QString itsName;

	int itsAnzWuensche;
	cAngebot * itsWuensche;
	
};

#endif /*CTEILNEHMER_H_*/
