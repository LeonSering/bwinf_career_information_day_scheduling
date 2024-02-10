#include "cInformationstag.h"

cInformationstag::cInformationstag(int anzTermine, int anzWuensche, int * prioritaeten) {
	if (anzTermine > anzWuensche)
		cout << "ERROR! Es darf nicht mehr Termine als Wuensche geben)" << endl;
	
	itsAnzTermine = anzTermine;
	itsAnzWuensche = anzWuensche;
	
	itsPrioritaeten = new int[itsAnzWuensche];
	
	if (prioritaeten == 0)
		for (int i = 0; i < itsAnzWuensche; i++)
			itsPrioritaeten[i] = 10 + itsAnzWuensche -i;  // Proritaeten auf Standardwerte
	else
		for (int i = 0; i < itsAnzWuensche; i++)
			itsPrioritaeten[i] = prioritaeten[i];
	
	itsAngebote = new cAngebot[0];
	itsVeranstaltungen = new cVeranstaltung[0];
	itsTeilnehmer = new cTeilnehmer[0];

	
	itsAnzAngebote = 0;
	itsAnzVeranstaltungen = 0;
	itsAnzTeilnehmer = 0;
	
	// hier werden die Arrays zum merken fuer den schnellen Algorithmus erstellt und mit false gefuellt
	TeilWue = new bool[itsAnzTeilnehmer*itsAnzWuensche];
	TeilTer = new bool[itsAnzTeilnehmer*itsAnzTermine];
	AngTer = new bool[itsAnzAngebote*itsAnzTermine];
	
	for (int i = 0 ; i < itsAnzTeilnehmer; i++) {
		for (int j = 0; j < itsAnzWuensche; j++)
			TeilWue[i*itsAnzWuensche + j] = false;
		for (int j = 0; j < itsAnzTermine; j++)
			TeilTer[i*itsAnzTermine + j] = false;
	}
	for (int i = 0; i < itsAnzAngebote; i++)
		for (int j = 0; j < itsAnzTermine; j++)
			AngTer[i*itsAnzTermine + j] = false;
}

cInformationstag::~cInformationstag() {
	
	// Alle Arrays wieder freigeben
	delete [] itsPrioritaeten;
	delete [] itsAngebote;
	delete [] itsVeranstaltungen;
	delete [] itsTeilnehmer;
	
	delete [] TeilWue;
	delete [] TeilTer;
	delete [] AngTer;
}

void cInformationstag::GespeichertesLoeschen() {
	// hier werden die Merk-Arrays erneut erstellt und mit false beschrieben
	delete [] TeilWue;
	delete [] TeilTer;
	delete [] AngTer;
	
	
	TeilWue = new bool[itsAnzTeilnehmer*itsAnzWuensche];
	TeilTer = new bool[itsAnzTeilnehmer*itsAnzTermine];
	AngTer = new bool[itsAnzAngebote*itsAnzTermine];
	
	for (int i = 0 ; i < itsAnzTeilnehmer; i++) {
		for (int j = 0; j < itsAnzWuensche; j++)
			TeilWue[i*itsAnzWuensche + j] = false;
		for (int j = 0; j < itsAnzTermine; j++)
			TeilTer[i*itsAnzTermine + j] = false;
	}
	for (int i = 0; i < itsAnzAngebote; i++)
		for (int j = 0; j < itsAnzTermine; j++)
			AngTer[i*itsAnzTermine + j] = false;
}

int cInformationstag::AngebotHinzufuegen(int min, int max, QString name) {
	if (min >= max) // min muss immer echt kleiner als max sein
		return -1; // Dann fehler zurueckgeben
	
	itsAnzAngebote++;
	cAngebot * tempAngebote = new cAngebot[itsAnzAngebote];
	for (int i = 0; i < itsAnzAngebote -1; i++)
		tempAngebote[i] = itsAngebote[i];
	delete [] itsAngebote;
	tempAngebote[itsAnzAngebote -1] = cAngebot(itsAnzAngebote-1, min, max, name);
	itsAngebote = tempAngebote;
	
	GespeichertesLoeschen();
	
	return itsAnzAngebote-1; // id wird zuueckgegeben
	

}

int cInformationstag::TeilnehmerHinzufuegen(int * wuensche, QString name) {
	
	if (itsAnzAngebote < itsAnzWuensche) // Wenn es gar nicht genuegend Angebote gibt
		return -1; // Fehler zurueckgeben
	
	cAngebot * tempWuensche = new cAngebot[itsAnzWuensche];
	for (int i = 0; i < itsAnzWuensche; i++)
		if (wuensche[i] <= itsAnzAngebote)
			tempWuensche[i] = itsAngebote[wuensche[i]];
		else
			return -1; // sollte ein Wunsch nicht guteltig sein, wird -1 zurueckgegeben.
				
	itsAnzTeilnehmer++;
	cTeilnehmer * tempTeilnehmer = new cTeilnehmer[itsAnzTeilnehmer -1];
	for (int i = 0; i < itsAnzTeilnehmer - 1; i++)
		tempTeilnehmer[i] = itsTeilnehmer[i];   // alte Teilnehmer kopieren
	
	delete [] itsTeilnehmer;

	
	itsTeilnehmer = new cTeilnehmer[itsAnzTeilnehmer];
	for (int i = 0; i < itsAnzTeilnehmer - 1; i++)
		itsTeilnehmer[i] = tempTeilnehmer[i];   // alte Teilnehmer kopieren
	delete [] tempTeilnehmer;
	
	itsTeilnehmer[itsAnzTeilnehmer - 1] = cTeilnehmer(itsAnzTeilnehmer-1, itsAnzWuensche, tempWuensche, name); // neuen Teilnehmer hinzufuegen
	
	GespeichertesLoeschen();

	return itsAnzTeilnehmer -1; // id wird zurueckgegeben
}

int cInformationstag::VeranstaltungHinzufuegen(cAngebot * typ, int termin) {
	itsAnzVeranstaltungen++;
	cVeranstaltung * tempVeranstaltungen = new cVeranstaltung[itsAnzVeranstaltungen];
	for (int i = 0; i < itsAnzVeranstaltungen - 1; i++)
		tempVeranstaltungen[i] = itsVeranstaltungen[i];
	delete [] itsVeranstaltungen;
	tempVeranstaltungen[itsAnzVeranstaltungen - 1] = cVeranstaltung(itsAnzVeranstaltungen-1, typ, termin); // neue Veranstaltung wird erstellt
	itsVeranstaltungen = tempVeranstaltungen;
	return itsAnzVeranstaltungen -1; // id wird zurueckgegeben
}
	
void cInformationstag::TeilnehmerZuweisen(int teilnehmer, int angebot, int termin) {
	// nunaechst pruefen, ob die Veranstaltung schon existiert:
	bool VeranstaltungSchonDa = false;  // ob die Veranstaltung schon existiert
	bool TeilnehmerSchonDa = false;	// ob der Teilnehmer in der Veranstaltung schon existiert
	int id = 0;
		
	for (int i = 0; i < itsAnzVeranstaltungen; i++)
		if (itsVeranstaltungen[i].getTyp()->getId() == angebot && itsVeranstaltungen[i].getTermin() == termin) {
			VeranstaltungSchonDa = true;
			id = i;
		}
	
	int anzahlTeilnehmer;

			
	if (VeranstaltungSchonDa == false)  // wenn sie noch nicht existiert, soll sie hinzugefuegt werden
		id = VeranstaltungHinzufuegen(&itsAngebote[angebot], termin);
	else {  // wenn sie schon existiert hat, soll geguckt werden, ob der Teilnehmer dadrin schon vorhanden ist
		anzahlTeilnehmer = itsVeranstaltungen[id].getAnzTeilnehmer();
		for (int i = 0; i < anzahlTeilnehmer; i++)
			if (itsVeranstaltungen[id].getTeilnehmer(i)->getId() == teilnehmer)
				TeilnehmerSchonDa = true;
	}
			

	if (TeilnehmerSchonDa == false) // Wenn der Teilnehmer in der Veranstaltung noch nicht aufgefuert wird, soll er dort hinzugefuegt werden 	
		itsVeranstaltungen[id].TeilnehmerHinzufuegen(&itsTeilnehmer[teilnehmer]);
		
}	
	
	
void cInformationstag::AllesLoeschen() {
	
	// zunaechst die Angebote loeschen
	delete [] itsAngebote;
	itsAngebote = new cAngebot[0];
	itsAnzAngebote = 0;

	// danach auch alles andere
	TeilnehmerLoeschen();
	GespeichertesLoeschen();
}

void cInformationstag::TeilnehmerLoeschen() {
	// zunaechst die Teilnehmer loeschen
	delete [] itsTeilnehmer;
	itsTeilnehmer = new cTeilnehmer[0];
	itsAnzTeilnehmer = 0;
	
	// danach auf die Veranstaltungen loeschen
	VeranstaltungenLoeschen();
	GespeichertesLoeschen();
}

void cInformationstag::VeranstaltungenLoeschen() {
	delete [] itsVeranstaltungen;
	
	itsVeranstaltungen = new cVeranstaltung[0];
	
	itsAnzVeranstaltungen = 0;
	GespeichertesLoeschen();
}

void cInformationstag::Ausgeben() { // in die Konsole ausgeben
	for (int i = 0; i < itsAnzAngebote; i++)
		itsAngebote[i].Ausgeben();
	cout << "itsAnzTeilnehmer: " << itsAnzTeilnehmer << endl;
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		itsTeilnehmer[i].Ausgeben();
		
	cout << "itsAnzVeranstaltungen: " << itsAnzVeranstaltungen << endl;
	for (int i = 0; i < itsAnzVeranstaltungen; i++)
		itsVeranstaltungen[i].Ausgeben();
}

void cInformationstag::setAnzTermine(int anzTermine) {
	itsAnzTermine = anzTermine; 
	
	// wurde die Anzahl der Termine geaendert muessen leider die Teilnehmer und die Mark-Arrays geloescht werden
	TeilnehmerLoeschen();
	GespeichertesLoeschen();
}
void cInformationstag::setAnzWuensche(int anzWuensche) {
	itsAnzWuensche = anzWuensche; 
	TeilnehmerLoeschen();  // bei einer neuen Anzahl an Wuenschen, sind die alten Teilnehmer hinfaellig
	
	// neuen Prioritaeten-Array erstellen
	delete [] itsPrioritaeten;
	itsPrioritaeten = new int[itsAnzWuensche];
	
	setPrioritaeten(); // Prioritaeten neu beschreiben (mit Standardwerten)
	
	GespeichertesLoeschen();
	
}

void cInformationstag::setPrioritaeten(int * prioritaeten) {
	
	if (prioritaeten == 0)  // bei 0 sollen Standardwerte benutzt werden
		for (int i = 0; i < itsAnzWuensche; i++)
			itsPrioritaeten[i] = 10 + itsAnzWuensche -i;
	else  // Ansonsten wird der Parameter ausgelesen
		for (int i = 0; i < itsAnzWuensche; i++) 
			itsPrioritaeten[i] = prioritaeten[i];
			
	GespeichertesLoeschen();
}

void cInformationstag::PlanErstellen(bool optimal) {
	
	// Die alte Ausgabe loeschen
	VeranstaltungenLoeschen();	
	GespeichertesLoeschen();
	// Fehler vorbeugen
	if (itsAnzTeilnehmer <= 0) {
		cout << "Fehler bei der Anzahl der Teilnehmer!" << endl;
		return;
	}
	if (itsAnzAngebote <= 0) {
		cout << "Fehler bei der Anzahl der Angebote!" << endl;
		return;
	}
	if (itsAnzTermine <= 0) {
		cout << "Fehler bei der Anzahl der Termine!" << endl;
		return;
	}
	if (itsAnzWuensche <= 0) {
		cout << "Fehler bei der Anzahl der Wuensche!" << endl;
		return;
	}
	 
	if (optimal == true)
		PlanErstellenOptimal();
	else
		PlanErstellenSchnell();
	
}


void cInformationstag::PlanErstellenOptimal() {
	
	cout << "Optimal-Plan-Erstellen wird geladen!" << endl;

	// Angebote auslesen:
	
	double min[itsAnzAngebote];
	double max[itsAnzAngebote]; 
	
	for (int i = 0; i < itsAnzAngebote; i++) {
		min[i] = itsAngebote[i].getMin();
		max[i] = itsAngebote[i].getMax();
	}
	
	// Teilnehmer auslesen:
	cAngebot * wuensche;
	int priori[itsAnzTeilnehmer][itsAnzAngebote];
	
	// zunaechst mit 0en fuellen:
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0; j < itsAnzAngebote; j++)
			priori[i][j] = 0;

	
	for(int i = 0; i < itsAnzTeilnehmer; i++) { // Alle Teilnehmer der Reihe nach durchgehen
		wuensche = itsTeilnehmer[i].getWuensche();
		for(int j = 0; j < itsAnzAngebote; j++)  // Alle Angebote durchgehen
			for(int k = 0; k < itsAnzWuensche; k++)  // Alle Wuensche des Teilnehmer durchgehen

				if (wuensche[k].getId() == j)  // Wenn beim akt Schueler der akt Wunsch mit dem akt Angebot uebereinstimmt 
					priori[i][j] = itsPrioritaeten[k];  // dann soll in die Matrix die entsprechende Prioritaetszahl geschrieben werden
	}
	
	
	// Das Problem formulieren
	int AnzH1 = itsAnzAngebote * itsAnzTeilnehmer;
	int AnzH2 = itsAnzAngebote * itsAnzTermine;
	int AnzH3 = itsAnzTeilnehmer * itsAnzTermine;
	
	int AnzZeilen = AnzH1 + AnzH2 + AnzH3;
	
	
	
	glp_prob * meinProblem;
	meinProblem = glp_create_prob();
	glp_set_prob_name(meinProblem, "Informationstag");
	glp_set_obj_dir(meinProblem, GLP_MAX);

	QString name;  // dadrin wird der name der Zeile bzw. Spalte gespeichert.
	int nummer;  // hier wird die jeweilige Nummer der Zeile bzw. Spalte gespeichert. Dient beides nur der Uebersicht
	
	
	// Zeilen (Beschrenkungen/Hilfsvariablen Hs)
	glp_add_rows(meinProblem, AnzZeilen);


	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0; j < itsAnzAngebote; j++) {
			name = "H1_" + QString::number(i) + "_" + QString::number(j);
			nummer = i * itsAnzAngebote + j + 1;
			glp_set_row_name(meinProblem, nummer, name.toLatin1());
			glp_set_row_bnds(meinProblem,nummer, GLP_DB, 0, 1);
		}
			
	for (int j = 0; j < itsAnzAngebote; j++)
		for (int k = 0; k < itsAnzTermine; k++) {
			name = "H2_" + QString::number(j) + "_" + QString::number(k);
			nummer = AnzH1 + j * itsAnzTermine + k + 1;
			glp_set_row_name(meinProblem, nummer, name.toLatin1());
			glp_set_row_bnds(meinProblem, nummer, GLP_DB, min[j], max[j]);
		}
	
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int k = 0; k < itsAnzTermine; k++) {
			name = "H3_" + QString::number(i) + "_" + QString::number(k);
			nummer = AnzH1 + AnzH2 + i * itsAnzTermine + k + 1;
			glp_set_row_name(meinProblem, nummer, name.toLatin1());	
			glp_set_row_bnds(meinProblem, nummer, GLP_DB, 0, 1);
		}
		
	// Spalten (structural variables) Die, die vom Programm bestimmt werden muessen (binaere Varibalen
	// Bools: Sind die binaeren Variablen die das Programm festlegt Bool_1_2_3 == 1 bedeutet, das Schüler 1 Angebot 2 zu Termin 3 besucht
	
	int AnzHauptBools = itsAnzTeilnehmer * itsAnzWuensche * itsAnzTermine; // Da Schueler keine Veranstaltung die Besuchen, die sie nicht auf gewaelt haben, wird hier nicht AnzAngebote benutzt, sondern nur die Anzahl der Wuensche
	int AnzHilfsBools = itsAnzAngebote * itsAnzTermine;  // ein paar Hilfs-Strukturale-Varibalen mit denen eine leere Veranstaltung direkt als voll behandelt werden kann
	int AnzSpalten = AnzHauptBools + AnzHilfsBools;
	
	glp_add_cols(meinProblem, AnzSpalten);
	
	
	// nun werden alle Bools hinzugefuegt und mit dem entsprechenden Koeffizenten fuer die Zielfunktion verknuepft 
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0, jwunsch = 0; j < itsAnzAngebote; j++)
			if (priori[i][j] != 0)  // wenn der Schueler i das Angebot j gewaehlt hat
			{
				for (int k = 0; k < itsAnzTermine; k++) {
					name = "Bool_" + QString::number(i) + "_" + QString::number(j) + "_" + QString::number(k);
					nummer = i * itsAnzWuensche * itsAnzTermine + jwunsch * itsAnzTermine + k + 1;
					glp_set_col_name(meinProblem, nummer, name.toLatin1());
					glp_set_col_kind(meinProblem, nummer, GLP_BV); // mach die Variable binaer
					glp_set_obj_coef(meinProblem, nummer, priori[i][j]); // der Koeffizient fuer die Zielfunktion
				}
				jwunsch++;
			}
	
	// Hilfsbools
	for (int j = 0; j < itsAnzAngebote; j++)
		for (int k = 0; k < itsAnzTermine; k++) {
			name = "NichtStatt_" + QString::number(j) + "_" + QString::number(k);
			nummer = AnzHauptBools + j * itsAnzTermine + k + 1;
			glp_set_col_name(meinProblem, nummer, name.toLatin1());
			glp_set_col_kind(meinProblem, nummer, GLP_BV); // mach die Variable binaer
			glp_set_obj_coef(meinProblem, nummer, 0); // diese haben keinen Einfluss auf die Zielfunktion
		}
		
	
	
	
	// Als letztes muss die Matrix geladen werden, diese muss dafuer in ein Eindemensionales Feld gepresst werden:
	int AnzFelder = AnzZeilen * AnzSpalten;
	
	int *zeile = new int[AnzFelder + 1];
	int *spalte = new int[AnzFelder + 1];
	double *matrix = new double[AnzFelder + 1];
	
	zeile[0] = 0;
	spalte[0] = 0;
	matrix[0] = 0;

	int aktSpalte;
	int aktZeile;
	
	int index;
	// alle Spalten durchgehen
	for (int i1 = 0; i1 < itsAnzTeilnehmer; i1++)
		for (int j1 = 0, jwunsch = 0; j1 < itsAnzAngebote; j1++)
			if (priori[i1][j1] != 0) {  // wenn der Schueler i das Angebot j gewaehlt hat
				for (int k1 = 0; k1 < itsAnzTermine; k1++) {
					aktSpalte = i1 * itsAnzWuensche * itsAnzTermine + jwunsch * itsAnzTermine + k1;
					
					
					
					// nun alle Zeilen durchgehen
					for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
						for (int j2 = 0; j2 < itsAnzAngebote; j2++) {
							aktZeile = i2 * itsAnzAngebote + j2;
							
							index = aktSpalte * AnzZeilen + aktZeile + 1;
							zeile[index] = aktZeile + 1;
							spalte[index] = aktSpalte + 1;
							if (i1 == i2 && j1 == j2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
								matrix[index] = 1;
							else
								matrix[index] = 0;
						}
							
					for (int j2 = 0; j2 < itsAnzAngebote; j2++)
						for (int k2 = 0; k2 < itsAnzTermine; k2++) {
							aktZeile = AnzH1 + j2 * itsAnzTermine + k2;
							index = aktSpalte * AnzZeilen + aktZeile + 1;
							zeile[index] = aktZeile + 1;
							spalte[index] = aktSpalte + 1;
							if (j1 == j2 && k1 == k2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
								matrix[index] = 1;
							else
								matrix[index] = 0;
						}
					
					for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
						for (int k2 = 0; k2 < itsAnzTermine; k2++) {
							aktZeile = AnzH1 + AnzH2 + i2 * itsAnzTermine + k2;
							index = aktSpalte * AnzZeilen + aktZeile + 1;
							zeile[index] = aktZeile + 1;
							spalte[index] = aktSpalte + 1;
							if (i1 == i2 && k1 == k2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
								matrix[index] = 1;
							else
								matrix[index] = 0;
						}
				}
			jwunsch++;
			}
				
	// hilfsBool spalten			
	for (int j1 = 0; j1 < itsAnzAngebote; j1++)
		for (int k1 = 0; k1 < itsAnzTermine; k1++) {
			aktSpalte = AnzHauptBools + j1 * itsAnzTermine + k1;
			
			// nun alle Zeilen durchgehen
			for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
				for (int j2 = 0; j2 < itsAnzAngebote; j2++) {
					aktZeile = i2 * itsAnzAngebote + j2;
					
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					matrix[index] = 0;  // hier soll das Programm nichts veraendern duerfen, deshalb alles 0

				}
					
			for (int j2 = 0; j2 < itsAnzAngebote; j2++)
				for (int k2 = 0; k2 < itsAnzTermine; k2++) {
					aktZeile = AnzH1 + j2 * itsAnzTermine + k2;
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					if (j1 == j2 && k1 == k2)  // hier soll das Programm direkt die volle Anzahl an moeglichen Teilnehmern fuer die Veranstaltunge setzen koennen (immer dann, wenn die Veranstaltung nicht stattfindet)
						matrix[index] = max[j1];
					else
						matrix[index] = 0;
				}
			
			for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
				for (int k2 = 0; k2 < itsAnzTermine; k2++) {
					aktZeile = AnzH1 + AnzH2 + i2 * itsAnzTermine + k2;
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					matrix[index] = 0;  // das hat dabei keinen Einfluss auf andere Sachen
				}		
		}	
			
			
	glp_load_matrix(meinProblem, AnzFelder, zeile, spalte, matrix);
	
	
	
	// Problem loesen
	cout << endl << endl << "Problem wird geloest: " << endl;
	glp_simplex(meinProblem, NULL);		// Problem wird geliest	zuerst mit dem Simplex-Verfahren
	glp_intopt(meinProblem, NULL);		// danach richtig mit dem Branch-and-Cut-Verfahren
	
				
	// Ergebnis auslesen
	double prioritaetenMax = glp_mip_obj_val(meinProblem);


	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0, jwunsch = 0; j < itsAnzAngebote; j++)
			if (priori[i][j] != 0)  // wenn der Schueler i das Angebot j gewaehlt hat
			{
				for (int k = 0; k < itsAnzTermine; k++) {
					nummer = i * itsAnzWuensche * itsAnzTermine + jwunsch * itsAnzTermine + k + 1;
					if (glp_mip_col_val(meinProblem, nummer) != 0)
						TeilnehmerZuweisen(i,j,k);
				}
				jwunsch++;
			}

		


	cout << "Das Prioritaeten Maximum liegt bei: " << prioritaetenMax << "!" << endl;
	
	delete [] zeile;
	delete [] spalte;
	delete [] matrix;
}

void cInformationstag::PlanErstellenSchnell() {
	
	cout << "Schnelles-Plan-Erstellen wird geladen!" << endl;
	
	// Angebote auslesen:
	
	double min[itsAnzAngebote];
	double max[itsAnzAngebote];
	
	for (int j = 0; j < itsAnzAngebote; j++) {
		min[j] = itsAngebote[j].getMin();
		max[j] = itsAngebote[j].getMax();
	}
	
	// Teilnehmer auslesen:
	cAngebot * wuensche;
	int prioriAngebot[itsAnzTeilnehmer][itsAnzAngebote];
	
	// zunaechst mit 0en fuellen:
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0; j < itsAnzAngebote; j++)
			prioriAngebot[i][j] = 0;

	
	for(int i = 0; i < itsAnzTeilnehmer; i++) { // Alle Teilnehmer der Reihe nach durchgehen
		wuensche = itsTeilnehmer[i].getWuensche();
		for(int j = 0; j < itsAnzAngebote; j++)  // Alle Angebote durchgehen
			for(int k = 0; k < itsAnzWuensche; k++)  // Alle Wuensche des Teilnehmer durchgehen

				if (wuensche[k].getId() == j && TeilWue[i*itsAnzWuensche + k] == false)  // Wenn beim akt Schueler der akt Wunsch mit dem akt Angebot uebereinstimmt 
					prioriAngebot[i][j] = itsPrioritaeten[k];  // dann soll in die Matrix die entsprechende Prioritaetszahl geschrieben werden
	}
	
	
	// Das erste Problem formulieren
	
	// welche Veranstaltungen, koennten stattfinden? Dies soll gezaehlt werden
	int AnzVeranstaltungen = 0;
	int AnzBenuzterAngebote = 0;  // ist die Anzahl der Angebote, bei der mindestens eine Veranstaltung zustande kommen kann
	
	int anzVerProAngebot[itsAnzAngebote];  // hier drin wird gespeichert, wie oft ein Angebot evtl. stattfindet
	
	for (int j = 0; j < itsAnzAngebote; j++)  
		anzVerProAngebot[j] = 0;  // erstmal mit 0en fuellen
	
	int TeilnehmerInVeranstaltung;
	
	int prioriVeranstaltung[itsAnzTeilnehmer][itsAnzAngebote * itsAnzTermine];  // gibt an welche Veranstaltung welche Prioritaet beim Teilnehmer hat.
	
	for (int j = 0; j < itsAnzAngebote; j++) { // alle Angebote durchgehen
		TeilnehmerInVeranstaltung = 0;  // noch gibt es keine Teilnehmer die evtl in die Veranstaltung wollen
		for (int i = 0; i < itsAnzTeilnehmer; i++) // nun soll geprueft werden, welcher Teilnehmer das Angebot gewaehlt hat
			if (prioriAngebot[i][j] > 0) { 
				TeilnehmerInVeranstaltung++;
				if (TeilnehmerInVeranstaltung >= min[j]) {
					if (anzVerProAngebot[j] >= itsAnzTermine)
						break;
					else {
						TeilnehmerInVeranstaltung = 0;
						AnzVeranstaltungen++;
						anzVerProAngebot[j]++;
					}
				}
				

			}
		
		if (anzVerProAngebot[j] > 0)
			AnzBenuzterAngebote++;

		// nun muss noch prioriVeranstaltung gefuellt werden	
		for (int k = 0; k < anzVerProAngebot[j]; k++) {	
			for (int i = 0; i < itsAnzTeilnehmer; i++) {
				prioriVeranstaltung[i][AnzVeranstaltungen - 1 - k] = prioriAngebot[i][j];	
			}
		}		
	}
	

	
	
	
	int AnzH1 = AnzBenuzterAngebote * itsAnzTeilnehmer;
	int AnzH2 = AnzVeranstaltungen;
	int AnzH3 = itsAnzTeilnehmer;
	
	int AnzZeilen = AnzH1 + AnzH2 + AnzH3;
	
	if (AnzVeranstaltungen == 0) {
		cout << "Es kann kein Angebot besucht werden!" << endl;
		return;
	}
	
	
	glp_prob * meinProblem;
	meinProblem = glp_create_prob();
	glp_set_prob_name(meinProblem, "Informationstag");
	glp_set_obj_dir(meinProblem, GLP_MAX);

	QString name;  // dadrin wird der Name der Zeile bzw. Spalte gespeichert.
	int nummer = 0;  // hier wird die jeweilige Nummer der Zeile bzw. Spalte gespeichert. Dient beides nur der Uebersicht
	
	
	// Zeilen (Beschrenkungen)
	glp_add_rows(meinProblem, AnzZeilen);


	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0; j < AnzBenuzterAngebote; j++) {
			name = "H1_" + QString::number(i) + "_" + QString::number(j);
			nummer = i * AnzBenuzterAngebote + j + 1;
			glp_set_row_name(meinProblem, nummer, name.toLatin1());
			glp_set_row_bnds(meinProblem,nummer, GLP_DB, 0, 1);
		}
			
	for (int j = 0, aktVer = 0; j < itsAnzAngebote; j++)
		if(anzVerProAngebot[j] > 0) 
			for (int k = 0; k < anzVerProAngebot[j]; k++) {
	
				name = "checkVeranstaltung_" + QString::number(aktVer);
				nummer = AnzH1 + aktVer + 1;
				glp_set_row_name(meinProblem, nummer, name.toLatin1());
				glp_set_row_bnds(meinProblem, nummer, GLP_DB, min[j], max[j]);			
				aktVer++;
			}
	
	int erlaubteAnz;
	
	for (int i = 0; i < itsAnzTeilnehmer; i++) {
		erlaubteAnz = itsAnzTermine;
		for (int k = 0; k < itsAnzWuensche; k++)
			if (TeilWue[i * itsAnzWuensche + k] == true)  // Besucht der Teilnehmer schon 1 oder mehr Veranstaltungen, darf er nur noch in entsprechend weniger
				erlaubteAnz--;
		
		name = "H3_" + QString::number(i);
		nummer = AnzH1 + AnzH2 + i + 1;
		glp_set_row_name(meinProblem, nummer, name.toLatin1());
		glp_set_row_bnds(meinProblem, nummer, GLP_DB, 0, erlaubteAnz);   // Ein Schueler darf mindests so viele Veranstaltungen besuchen, wie es ihm noch erlaubt ist
	}
	
	// Spalten/binaere Varibalen (structural variables) Die, die vom Programm bestimmt werden muessen.
	// Bools: Sind die binaeren Variablen die das Programm festlegt Bool_1_2_3 == 1 bedeutet, das Schüler 1 Angebot 2 zu Termin 3 besucht
	
	
	int AnzHauptBools = itsAnzTeilnehmer * AnzVeranstaltungen; // Da Schueler keine Veranstaltung die Besuchen, die sie nicht auf gewaelt haben, wird hier nicht AnzAngebote benutzt, sondern nur die Anzahl der Wuensche	
	int AnzHilfsBools = AnzVeranstaltungen;  // ein paar Hilfs-Strukturale-Varibalen mit denen eine leere Veranstaltung direkt als voll behandelt werden kann
	
	int AnzSpalten = AnzHauptBools + AnzHilfsBools;
	
	glp_add_cols(meinProblem, AnzSpalten);
	
	
	// nun werden alle Bools hinzugefuegt und mit dem entsprechenden Koeffizienten fuer die Zielfunktion verknuepft 
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0; j < AnzVeranstaltungen; j++) {
			name = "Bool_" + QString::number(i) + "_" + QString::number(j);
			nummer = i * AnzVeranstaltungen + j + 1;
			glp_set_col_name(meinProblem, nummer, name.toLatin1());
			glp_set_col_kind(meinProblem, nummer, GLP_BV); // mach die Variable binaer
			glp_set_obj_coef(meinProblem, nummer, prioriVeranstaltung[i][j]); // der Koeffizient fuer die Zielfunktion

		}
	
	// Hilfsbools
	for (int j = 0; j < AnzVeranstaltungen; j++) {
		name = "NichtStatt_" + QString::number(j);
		nummer = AnzHauptBools + j + 1;
		glp_set_col_name(meinProblem, nummer, name.toLatin1());
		glp_set_col_kind(meinProblem, nummer, GLP_BV); // mach die Variable binaer
		glp_set_obj_coef(meinProblem, nummer, 0); // diese haben keinen Einfluss auf die Zielfunktion
		
	}
		
	
	// Als letztes muss die Matrix geladen werden, diese muss dafuer in ein eindemensionales Feld gepresst werden:
	int AnzFelder = AnzZeilen * AnzSpalten;
	
	int *zeile = new int[AnzFelder + 1];
	int *spalte = new int[AnzFelder + 1];
	double *matrix = new double[AnzFelder + 1];
	
	zeile[0] = 0;
	spalte[0] = 0;
	matrix[0] = 0;

	int aktSpalte;
	int aktZeile;
	
	int index;
	// alle Spalten durchgehen
	for (int i1 = 0; i1 < itsAnzTeilnehmer; i1++)
		for (int j1 = 0, aktVer = 0, aktAng = 0; j1 < itsAnzAngebote; j1++)
			if (anzVerProAngebot[j1] > 0) {
				for (int k1 = 0; k1 < anzVerProAngebot[j1]; k1++) {
					aktSpalte = i1 * AnzVeranstaltungen + aktVer;
							
					
					// nun alle Zeilen durchgehen			
					for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
						for (int j2 = 0; j2 < AnzBenuzterAngebote; j2++) {
							aktZeile = i2 * AnzBenuzterAngebote + j2;
							index = aktSpalte * AnzZeilen + aktZeile + 1;
							zeile[index] = aktZeile + 1;
							spalte[index] = aktSpalte + 1;
							if (i1 == i2 && aktAng == j2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
								matrix[index] = 1;
							else
								matrix[index] = 0;
						}
						
						
					for (int j2 = 0; j2 < AnzVeranstaltungen; j2++) {
						aktZeile = AnzH1 + j2;
						index = aktSpalte * AnzZeilen + aktZeile + 1;
						zeile[index] = aktZeile + 1;
						spalte[index] = aktSpalte + 1;
						if (aktVer == j2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
							matrix[index] = 1;
						else
							matrix[index] = 0;
					}
					

					
					for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++) {
						aktZeile = AnzH1 + AnzH2 + i2;
						index = aktSpalte * AnzZeilen + aktZeile + 1;
						zeile[index] = aktZeile + 1;
						spalte[index] = aktSpalte + 1;
						if (i1 == i2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
							matrix[index] = 1;
						else
							matrix[index] = 0;
											
					}	
						
					aktVer++;
				}
					
				aktAng++;
			}
			
			
	// hilfsBool Spalten			
	for (int j1 = 0, aktVer = 0, aktAng = 0; j1 < itsAnzAngebote; j1++)
		if (anzVerProAngebot[j1] > 0) {
			for (int k1 = 0; k1 < anzVerProAngebot[j1]; k1++) {
				aktSpalte = AnzHauptBools + aktVer;
						
				
				// nun alle Zeilen durchgehen			
				for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
					for (int j2 = 0; j2 < AnzBenuzterAngebote; j2++) {
						aktZeile = i2 * AnzBenuzterAngebote + j2;
						index = aktSpalte * AnzZeilen + aktZeile + 1;
						zeile[index] = aktZeile + 1;
						spalte[index] = aktSpalte + 1;
						matrix[index] = 0;
					}
					
					
				for (int j2 = 0; j2 < AnzVeranstaltungen; j2++) {
					aktZeile = AnzH1 + j2;
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					if (aktVer == j2)  // wenn es sich bei der Spalte und der Reihe um die gleichen Indizes handelt
						matrix[index] = max[aktAng];
					else
						matrix[index] = 0;
				}
				

				
				for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++) {
					aktZeile = AnzH1 + AnzH2 + i2;
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					matrix[index] = 0;				
				}	
					
				aktVer++;
			}
				
			aktAng++;


		}

	
	glp_load_matrix(meinProblem, AnzFelder, zeile, spalte, matrix);
	
	
	
	// Problem loesen
	cout << endl << endl << "Problem wird geloest: " << endl;
	glp_simplex(meinProblem, NULL);		// Problem wird geloest	
	glp_intopt(meinProblem, NULL);	
	
	
	

	
	
	// Ergebnis auslesen
	double prioritaetenMax = glp_mip_obj_val(meinProblem);
	
	
	double loesung[itsAnzTeilnehmer][AnzVeranstaltungen]; // besucht der Teilnehmer die Veranstaltung??
	
	cout << "Das Prioritaeten Maximum liegt bei: " << prioritaetenMax << "!" << endl;
	
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0, aktVer = 0; j < itsAnzAngebote; j++)
			if (anzVerProAngebot[j] > 0) {
				for (int k = 0; k < anzVerProAngebot[j]; k++) {
					nummer = i * AnzVeranstaltungen + aktVer + 1;
					loesung[i][aktVer] = glp_mip_col_val(meinProblem, nummer);
					aktVer++;
				}
			}
	

		
	double prioriVeranstaltungen[AnzVeranstaltungen];
	
	
	for (int j = 0; j < AnzVeranstaltungen; j++) {
		prioriVeranstaltungen[j] = 0;
		
		for (int i = 0; i < itsAnzTeilnehmer; i++)
			if (loesung[i][j] != 0) {
				nummer = i * AnzVeranstaltungen + j + 1;
				prioriVeranstaltungen[j] += glp_get_obj_coef(meinProblem, nummer);
			}
	}
	
	double prioriGesamt = 0;
	for (int i = 0; i < AnzVeranstaltungen; i++)
		prioriGesamt += prioriVeranstaltungen[i];
	cout << "prioriGesamt: " << prioriGesamt << endl;	
	
	
	// Das zweite Problem
	glp_prob * meinProblem2;
	meinProblem2 = glp_create_prob();
	glp_set_prob_name(meinProblem2, "Veranstaltungen ordnen");
	glp_set_obj_dir(meinProblem2, GLP_MAX);
	
	
	
	// Zunaechst wieder die Zeilen
	AnzH1 = itsAnzTeilnehmer * itsAnzTermine; //Dass kein Schueler zwei Angebote parallel besuchen muss
	AnzH2 = AnzVeranstaltungen;  // Dass keine Veranstaltung mehrfach angeboten wird
	AnzZeilen = AnzH1 + AnzH2;
	glp_add_rows(meinProblem2, AnzZeilen);
	
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int k = 0; k < itsAnzTermine; k++) {
			name = "H1_" + QString::number(i) + "_" + QString::number(k);
			nummer = i * itsAnzTermine + k + 1;
			glp_set_row_name(meinProblem2, nummer, name.toLatin1());
			if (TeilTer[i*itsAnzTermine + k] == false)   // wenn der Teilnehmer an dem noch kein Termin besucht
				glp_set_row_bnds(meinProblem2,nummer, GLP_DB, 0, 1);
			else							// falls er doch schon eine Veranstaltung an dem Termin besucht, soll er hier eingeschrenkt werden
				glp_set_row_bnds(meinProblem2,nummer, GLP_FX, 0, 0);
		}
		
	for (int j = 0; j < AnzVeranstaltungen; j++) {
		name = "H2_" + QString::number(j);
		nummer = AnzH1 + j + 1;
		glp_set_row_name(meinProblem2, nummer, name.toLatin1());
		glp_set_row_bnds(meinProblem2, nummer, GLP_DB, 0, 1);	
	}	
	
	// Als naechstes die Spalten
	AnzSpalten = AnzHauptBools = AnzVeranstaltungen * itsAnzTermine;
	
	glp_add_cols(meinProblem2, AnzSpalten);
	
	
	for (int j = 0, aktVer = 0; j < itsAnzAngebote; j++)
		if (anzVerProAngebot[j] > 0)
			for (int k = 0; k < anzVerProAngebot[j]; k++) {
				for (int t = 0; t < itsAnzTermine; t++) {			
					name = "Bool_" + QString::number(aktVer) + "_" + QString::number(t);
					nummer = aktVer * itsAnzTermine + t + 1;
					glp_set_col_name(meinProblem2, nummer, name.toLatin1());
					if (prioriVeranstaltungen[aktVer] == 0 || AngTer[j*itsAnzTermine + t] == true)
						glp_set_col_bnds(meinProblem2, nummer, GLP_FX, 0, 0);  // wenn die Veranstaltung nicht stattfindet, weil zu wenig Interessenten oder sie schon existiert, soll sie fixiert werden
					else
						glp_set_col_kind(meinProblem2, nummer, GLP_BV); // mach die Variable binaer
					glp_set_obj_coef(meinProblem2, nummer, prioriVeranstaltungen[aktVer]); // der Koeffizient fuer die Zielfunktion	
				}
			aktVer++;
			}
		
		
			
	
	
	// nun muss noch die Matrix geladen werden:
	delete [] zeile;
	delete [] spalte;
	delete [] matrix;
	
	AnzFelder = AnzZeilen * AnzSpalten;

	zeile = new int[AnzFelder + 1];
	spalte = new int[AnzFelder + 1];
	matrix = new double[AnzFelder + 1];
	
	zeile[0] = 0;
	spalte[0] = 0;
	matrix[0] = 0;
	
	// alle Spalten durchgehen
	for (int j1 = 0; j1 < AnzVeranstaltungen; j1++)
		for (int k1 = 0; k1 < itsAnzTermine; k1++) {
			aktSpalte = j1 * itsAnzTermine + k1;			
			// alle Zeilen durchgehen		
			for (int i2 = 0; i2 < itsAnzTeilnehmer; i2++)
				for (int k2 = 0; k2 < itsAnzTermine; k2++) {
					aktZeile = 	i2 * itsAnzTermine + k2;
					index = aktSpalte * AnzZeilen + aktZeile + 1;
					zeile[index] = aktZeile + 1;
					spalte[index] = aktSpalte + 1;
					if (k1 == k2 && loesung[i2][j1] != 0)  // wenn es sich um den gleichen Termin handelt und der Teilnehmer die Veranstaltung besucht
						matrix[index] = 1;
					else
						matrix[index] = 0;
				}
				
			for (int j2 = 0; j2 < AnzVeranstaltungen; j2++) {
				aktZeile = AnzH1 + j2;
				index = aktSpalte * AnzZeilen + aktZeile + 1;
				zeile[index] = aktZeile + 1;
				spalte[index] = aktSpalte + 1;
				if (j1 == j2)  // wenn es sich um die gleiche Veranstaltung handelt
					matrix[index] = 1;
				else
					matrix[index] = 0;
			}	
			cout << endl;
		}

	glp_load_matrix(meinProblem2, AnzFelder, zeile, spalte, matrix);
	
	
	
	// Problem loesen
	cout << endl << endl << "Problem2 wird geloest: " << endl;
	
	glp_simplex(meinProblem2, NULL);		// Problem wird geliest	
	glp_intopt(meinProblem2, NULL);	
	
	
	
	// Ergebnis auslesen und Veranstaltungen erstellen
	cAngebot*wunsch;
	
	bool veraenderung = false;  // hat sich was bei dem durchgang veraendert?
	
	double loesung2[AnzVeranstaltungen][itsAnzTermine];
	
	for (int i = 0; i < itsAnzTeilnehmer; i++)
		for (int j = 0, aktVer = 0; j < itsAnzAngebote; j++)
			if (anzVerProAngebot[j] > 0) {
				for (int k = 0; k < anzVerProAngebot[j]; k++) {
					for(int t = 0; t < itsAnzTermine; t++) {
						nummer = aktVer * itsAnzTermine + t + 1;
						loesung2[aktVer][t] = glp_mip_col_val(meinProblem2, nummer);
						if(loesung[i][aktVer] != 0 && glp_mip_col_val(meinProblem2, nummer) != 0) {
							
							TeilnehmerZuweisen(i, j, t); // der Teilnehmer wird zugewiesen	
							veraenderung = true; // es hat sich was veraendert	
							TeilTer[i*itsAnzTermine + t] = true; // und es soll sich alles gemerkt werden
							AngTer[j*itsAnzTermine + t] = true;
							
							wunsch = itsTeilnehmer[i].getWuensche();
							for (int w = 0; w < itsAnzWuensche; w++)
								if (wunsch[w].getId() == itsAngebote[j].getId())
									TeilWue[i*itsAnzWuensche + w] = true;
							
							
								

						}
					}					
					
					aktVer++;
				}
			}
	
	delete [] zeile;
	delete [] spalte;
	delete [] matrix;
	
	if (veraenderung == true) // es hat sich was veraendert, das ganze soll also nochmal durchlaufen
		PlanErstellenSchnell();

}
