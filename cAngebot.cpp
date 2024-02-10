#include "cAngebot.h"

cAngebot::cAngebot(int id, int min, int max, QString name):
		itsId(id),
		itsMin(min),
		itsMax(max) {
	if (name == "Angebot")
		itsName = "Angebot " + QString::number(id);
	else
		itsName = name;
}

cAngebot::~cAngebot()
{
}

void cAngebot::Ausgeben() {
	cout << "Angebot " << itsId << ": \"" << itsName.toStdString() << "\" | min: " << itsMin << " | max: " << itsMax << endl;
}
