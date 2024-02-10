#ifndef CANGEBOT_H_
#define CANGEBOT_H_

#include <iostream>
using namespace std;

#include <QString>

class cAngebot
{
public:
	cAngebot(int id = 0, int min = 0, int max = 0, QString name = "Angebot");
	~cAngebot();
	
	void Ausgeben();  // fuer die Konsole
	
	QString getName() {return itsName; }
	int getId() {return itsId; }
	
	int getMin() {return itsMin; }
	int getMax() {return itsMax; }
	
private:
	int itsId; // werden durchnummeriert
	QString itsName;

	int itsMin;
	int itsMax;
};

#endif /*CANGEBOT_H_*/
