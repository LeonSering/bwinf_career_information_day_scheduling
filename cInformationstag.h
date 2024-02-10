#ifndef CINFORMATIONSTAG_H_
#define CINFORMATIONSTAG_H_

#include <glpk.h> // glpk wird hier eingebunden
#include <QString>

// eigene
#include "cAngebot.h"
#include "cVeranstaltung.h"
#include "cTeilnehmer.h"

class cInformationstag
{
public:
	cInformationstag(int anzTermine = 4, int anzWuensche = 6, int * prioritaeten = 0);
	~cInformationstag();
	
 	 // Hinzufuege-Methoden geben jeweils die ID zurueck! Beim Fehler -1!!
	int AngebotHinzufuegen(int min, int max, QString name = "Angebot");
	int TeilnehmerHinzufuegen(int * wuensche, QString name = QString::fromUtf8("Schüler"));
	
	// Loeschenmethoden
	void AllesLoeschen();
	void TeilnehmerLoeschen();
	void VeranstaltungenLoeschen();
	
	
	void Ausgeben(); // fuer die Konsole
	
	void PlanErstellen(bool optimal = false); // Schnittstelle fuer cThread, leitet die Aufgabe an den richtigen Algorithmus weiter standardmaessig wird der schnelle Algorithmus verwendet
	
	
	void setAnzTermine(int anzTermine);
	void setAnzWuensche(int anzWuensche);
	void setPrioritaeten(int * prioritaeten = 0);  // bei 0 werden die Prioritaeten standardmaeßig eingestellt
			// Achtung: Prioritaeten muessen in einem Array gespeichert sein, der die Laenge von itsAnzWuensche hat
	
	int getAnzTermine() {return itsAnzTermine; }
	int getAnzWuensche() {return itsAnzWuensche; }
	int * getPrioritaeten() {return itsPrioritaeten; }
	
	cAngebot * getAngebote() {return itsAngebote; }
	int getAnzAngeobte() {return itsAnzAngebote; }
	
	cVeranstaltung * getVeranstaltungen() {return itsVeranstaltungen; }
	int getAnzVeranstaltungen() {return itsAnzVeranstaltungen; }
	
	cTeilnehmer * getTeilnehmer() {return itsTeilnehmer; }
	int getAnzTeilnehmer() {return itsAnzTeilnehmer; }
	
private:

	int VeranstaltungHinzufuegen(cAngebot * typ, int termin);
	void TeilnehmerZuweisen(int teilnehmer, int angebot, int termin);     // Weist einen Teilnehmer einer Veranstaltung zu, wenn diese schon existiert, sonsten wird diese erstellt


	void PlanErstellenSchnell();
	void PlanErstellenOptimal();

	int itsAnzTermine;
	int itsAnzWuensche;
	int * itsPrioritaeten;  // Prioritaet[0] ist fuer den obersten Wunsch
	

	cAngebot * itsAngebote;
	int itsAnzAngebote;
	
	cVeranstaltung * itsVeranstaltungen;
	int itsAnzVeranstaltungen;
	
	cTeilnehmer * itsTeilnehmer;
	int itsAnzTeilnehmer;
	
	
	// ein paar Arrays zum speichern, welche Sachen schon mit dem PlanErstellen() zugeordnet wurden
	bool * TeilWue;  // speichert in einem Array welche Wueschne von welchen Teilnehmern schon erfuellt wurden
	bool * TeilTer;  // speichert in einem Array welche Termine schon von welchen Teilnehmer belegt wurden
	bool * AngTer;	 // speichert in einem Array welche Termine schon von welchen Angeboten belegt wurden
	
	void GespeichertesLoeschen();  // setzt alle oberen Arrays wieder auf die gewuenschte laenge und auf false
};

#endif /*CINFORMATIONSTAG_H_*/
