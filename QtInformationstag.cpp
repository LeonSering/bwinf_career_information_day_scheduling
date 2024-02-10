#include "QtInformationstag.h"

QtInformationstag::QtInformationstag(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	
	ui.labelStatus->hide();
	
	// itsTread wird eingerichtet
	itsThread.setInformationstag(&itsInformationstag);
	connect(&itsThread, SIGNAL (finished()), this, SLOT(plan_erstellt()));
	abgebrochen = false;
	
	
	// Tabellen fuer die Listen werden eingerichtet (Spaltbreite veraendert)
	ui.tableAngebote->setColumnWidth(0, 30);	
	ui.tableAngebote->setColumnWidth(1, 120);
	ui.tableAngebote->setColumnWidth(2, 35);
	ui.tableAngebote->setColumnWidth(3, 35);
	
	ui.tableAngebote->verticalHeader()->hide(); // Headers sollen alle nicht angezeigt werden
	ui.tableTeilnehmer->verticalHeader()->hide();
	ui.treeVeranstaltungen->header()->hide();

	// ScrollMode aendern, so dass kontinuierliches Scrollen moeglich ist
	ui.tableAngebote->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.tableAngebote->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);	
	ui.tableTeilnehmer->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.tableTeilnehmer->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.treeVeranstaltungen->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	
	// Die Scrollarea fuer die WunschBox:
	scrollWunschBox.setParent(ui.gBoxTeilnehmer);
	scrollWunschBox.setGeometry(10, 100, 210, 180);
	
	widgetWunschBox.setParent(&scrollWunschBox);
	
	scrollWunschBox.setWidget(&widgetWunschBox);
	
	cBoxWunschBox = new QComboBox[1];
	labelWunschBox = new QLabel[0];
	
	cBoxWunschBox[0].insertItem(0, "");
	
	// Die Scrollarea fuer die Prioritaeten
	scrollPrioritaeten.setParent(ui.gBoxPrioritaeten);
	scrollPrioritaeten.setGeometry(10, 20, 150, 260);
	
	widgetPrioritaeten.setParent(&scrollPrioritaeten);
	
	scrollPrioritaeten.setWidget(&widgetPrioritaeten);
	
	sBoxPrioritaeten = new QSpinBox[0];
	labelPrioritaeten = new QLabel[0];
	
	when_sBoxAnzWuensche_changed(6); // Wuensche zeichnen
	
	// Wenn neues Angebot hinzugefuegt wurde, soll evtl., die Zufaells-Buttons deaktiviert werden
	connect(ui.btAngebotHinzufuegen, SIGNAL(clicked()), this, SLOT(when_AnzAngebote_changed()));
	connect(ui.btAngebotEntfernen, SIGNAL(clicked()), this, SLOT(when_AnzAngebote_changed()));
	connect(ui.btVorlageHinzufuegen, SIGNAL(clicked()), this, SLOT(when_AnzAngebote_changed()));
	connect(ui.btAllesNeu, SIGNAL(clicked()), this, SLOT(when_AnzAngebote_changed()));
		
	// wenn beim Nameneingaben Enter gedrueckt wird, soll der entsprechende Button geklickt werden.
	connect(ui.nameAngebot, SIGNAL (returnPressed ()), ui.btAngebotHinzufuegen, SLOT (click()));
	connect(ui.nameTeilnehmer, SIGNAL (returnPressed ()), ui.btTeilnehmerHinzufuegen, SLOT (click()));
	
	// wenn die Min bzw. Max Spinboxen veraendert werden, soll der jeweilige andere evtl. angepasst werden
	connect(ui.sBoxMax, SIGNAL(valueChanged(int)), this, SLOT(when_sBoxMax_changed(int)));
	connect(ui.sBoxMin, SIGNAL(valueChanged(int)), this, SLOT(when_sBoxMin_changed(int)));
	
	// das gleiche bei den Spinboxen AnzTermine und AnzWuensche
	connect(ui.sBoxAnzTermine, SIGNAL(valueChanged(int)), this, SLOT(when_sBoxAnzTermine_changed(int)));
	connect(ui.sBoxAnzWuensche, SIGNAL(valueChanged(int)), this, SLOT(when_sBoxAnzWuensche_changed(int)));
	
	// Wenn der Name veraendert wird, soll ggf. der entsprechende Button aktiviert oder deaktiviert werden
	connect(ui.nameAngebot, SIGNAL(textChanged (QString) ), this, SLOT(btAngebotHinzufuegen_deaktivieren(QString)));
	connect(ui.nameTeilnehmer, SIGNAL(textChanged (QString) ), this, SLOT(btTeilnehmerHinzufuegen_deaktivieren(QString)));
	
	on_btEinstellungenVerwenden_clicked();
	
}

QtInformationstag::~QtInformationstag() {
	// Alle Arrays sollen freigegeben werden
	delete [] cBoxWunschBox;
	delete [] labelWunschBox;
	
	delete [] sBoxPrioritaeten;
	delete [] labelPrioritaeten;
}


////////////////////////////////////////////////////////////////////
///////////////////////////// SLOTS ////////////////////////////////
////////////////////////////////////////////////////////////////////

void QtInformationstag::on_btEinstellungenVerwenden_clicked() {
		
	itsInformationstag.TeilnehmerLoeschen();
	
	int anzTermine = ui.sBoxAnzTermine->value();
	int anzWuensche = ui.sBoxAnzWuensche->value();
	
	// itsInformationstag aktualisieren
	itsInformationstag.setAnzTermine(anzTermine);
	itsInformationstag.setAnzWuensche(anzWuensche);

	// tableTeilnehmer aktualisieren
	ui.tableTeilnehmer->clear();
	ui.tableTeilnehmer->setRowCount(0);
	
	ui.tableTeilnehmer->setColumnCount(anzWuensche + 2);  // + ID + Name
	ui.tableTeilnehmer->setColumnWidth(0, 40);
	ui.tableTeilnehmer->setColumnWidth(1, 120);
	
	QStringList headerString;
	headerString << "ID" << "Teilnehmer";
	
	for (int i = 0; i < anzWuensche; i++) {
		ui.tableTeilnehmer->setColumnWidth(2 + i, 100);
		headerString << ("Wunsch " + QString::number(i+1));
	}
	ui.tableTeilnehmer->setHorizontalHeaderLabels(headerString);

	// WunschBox erstellen
	widgetWunschBox.setGeometry(0, 0, 180, 15 + 30 * anzWuensche);
	widgetWunschBox.show();
	
	QComboBox cBoxTemp; // einer wird sich gemerkt, um die Items daraus zu kopieren
	int anzItems = cBoxWunschBox[0].count();
	for (int i = 0; i < anzItems; i++)
		cBoxTemp.insertItem(i, cBoxWunschBox[0].itemText(i));
	
	delete [] cBoxWunschBox;
	delete [] labelWunschBox;
	
	cBoxWunschBox = new QComboBox[anzWuensche];
	labelWunschBox = new QLabel[anzWuensche];
	
	for (int i = 0 ; i < anzWuensche; i++) {
		cBoxWunschBox[i].setParent(&widgetWunschBox);
		cBoxWunschBox[i].setGeometry(30, 10 + 30 * i, 140, 22);
		for (int j = 0; j < anzItems; j++)
			cBoxWunschBox[i].insertItem(j, cBoxTemp.itemText(j));
		cBoxWunschBox[i].show();
		connect(&cBoxWunschBox[i], SIGNAL(currentIndexChanged(int)), this, SLOT(wunschBox_index_changed(int)));
		connect(&cBoxWunschBox[i], SIGNAL(currentIndexChanged(int)), this, SLOT(btTeilnehmerHinzufuegen_deaktivieren(int)));
		
		labelWunschBox[i].setParent(&widgetWunschBox);
		labelWunschBox[i].setGeometry(10, 14 + 30 * i, 20, 18);
		labelWunschBox[i].setText( QString::number(i+1) + ": ");
		labelWunschBox[i].show();
	}
	
	// prioritaeten erstellen
	
	widgetPrioritaeten.setGeometry(0, 0, 130, 15 + 30 * anzWuensche);
	widgetPrioritaeten.show();
	
	delete [] sBoxPrioritaeten;
	delete [] labelPrioritaeten;
	
	sBoxPrioritaeten = new QSpinBox[anzWuensche];
	labelPrioritaeten = new QLabel[anzWuensche];
	
	for (int i = 0; i < anzWuensche; i++) {
		sBoxPrioritaeten[i].setParent(&widgetPrioritaeten);
		sBoxPrioritaeten[i].setGeometry(40, 10 + 30 * i, 71, 23);
		sBoxPrioritaeten[i].setMaximum(9999);
		sBoxPrioritaeten[i].setMinimum(1);
		sBoxPrioritaeten[i].setValue(10 + anzWuensche - i);
		sBoxPrioritaeten[i].show();
		
		labelPrioritaeten[i].setParent(&widgetPrioritaeten);
		labelPrioritaeten[i].setGeometry(10, 12 + 30 * i, 20, 18);
		labelPrioritaeten[i].setText(QString::number(i+1) + ": ");
		labelPrioritaeten[i].show();
	}
}

void QtInformationstag::on_btAllesNeu_clicked() {
	
	// einfach alles leeren
	on_btEinstellungenVerwenden_clicked();
	on_btAngebotEntfernen_clicked();
	on_btVeranstaltungenEntfernen_clicked();
	
	ui.nameTeilnehmer->setText("");
	ui.nameAngebot->setText("");
	ui.sBoxMax->setValue(20);
	ui.sBoxMin->setValue(10);
	
	
}


void QtInformationstag::on_btAngebotHinzufuegen_clicked() {
	int min = ui.sBoxMin->value();
	int max = ui.sBoxMax->value();
	QString name = ui.nameAngebot->text();
	
	// zunaechst das Angebot bei itsInformationstag hinzufuegen
	int id = itsInformationstag.AngebotHinzufuegen(min, max, name);  // angebot zurueckgegeben und id gespeichert
	
	
	if (id == -1) {// wenn ein Fehler zurueckgegeben wurde
		cout << "Fehler beim Hinzufuegen eines Angebots!" << endl;
		return;  // soll abgebrochen werden
	}
	
	// Dann das Fenster aktualsieren (in die Liste eintragen)	
	ui.nameAngebot->setText("");
	ui.nameAngebot->setFocus();
	
	ui.tableAngebote->insertRow(id);
	ui.tableAngebote->setItem(id, 0, new QTableWidgetItem(QString::number(id)));
	ui.tableAngebote->setItem(id, 1, new QTableWidgetItem(name));
	ui.tableAngebote->setItem(id, 2, new QTableWidgetItem(QString::number(min)));
	ui.tableAngebote->setItem(id, 3, new QTableWidgetItem(QString::number(max)));	
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	for (int i = 0; i < anzWuensche; i++)
		cBoxWunschBox[i].insertItem(id+1, name);
}

void QtInformationstag::on_btAngebotEntfernen_clicked() {
	
	// wenn die Angebote entfernt werden sollen, muessen auch alle Teilnehmer entfernt werden
	ui.tableAngebote->clearContents();
	ui.tableAngebote->setRowCount(0);
	ui.tableTeilnehmer->clearContents();
	ui.tableTeilnehmer->setRowCount(0);
	
	itsInformationstag.AllesLoeschen();
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	for (int i = 0; i < anzWuensche; i++) {
		cBoxWunschBox[i].clear();
		cBoxWunschBox[i].insertItem(0, "");
	}
	
	ui.btVorlageHinzufuegen->setEnabled(true);
}


void QtInformationstag::on_btTeilnehmerHinzufuegen_clicked() {
	QString name = ui.nameTeilnehmer->text();
	
	// erstmal auslesen
	int anzWuensche = itsInformationstag.getAnzWuensche();

	int wuensche[anzWuensche];
	for (int i = 0; i < anzWuensche; i++)
		wuensche[i] = cBoxWunschBox[i].currentIndex() - 1;
	
	// dann itsInformationstag aktualisieren
	int id = itsInformationstag.TeilnehmerHinzufuegen(wuensche, name);
	
	
	if (id == -1) { // Wenn Fehler zuruckegegeben wurde
		cout << "Fehler beim Hinzufuegen eines Teilnehmers!" << endl;
		return; // soll abgebrochen werden
	}

	// und in die Liste eintragen
	ui.nameTeilnehmer->setText("");
	ui.nameTeilnehmer->setFocus();
	
	ui.tableTeilnehmer->insertRow(id);
	
	ui.tableTeilnehmer->setItem(id, 0, new QTableWidgetItem(QString::number(id))); 
	ui.tableTeilnehmer->setItem(id, 1, new QTableWidgetItem(name)); 
	
	for (int i = 0; i < anzWuensche; i++)
		ui.tableTeilnehmer->setItem(id, i + 2, new QTableWidgetItem(cBoxWunschBox[i].currentText()));
	
}

void QtInformationstag::on_btTeilnehmerEntfernen_clicked() {
	ui.tableTeilnehmer->clearContents();
	ui.tableTeilnehmer->setRowCount(0);
	
	itsInformationstag.TeilnehmerLoeschen();
}


void QtInformationstag::on_btPlanErstellen_clicked(){
	on_btVeranstaltungenEntfernen_clicked(); // zunaechst das TreeFeld wieder loeschen
	
	// Das Fenster aktualisieren
	ui.labelStatus->show();
	ui.btPlanErstellen->setEnabled(false);
	ui.btAbbrechen->setEnabled(true);
	
	// und dann die Aufgabe an itsThread weiterleiten
	if (ui.cBoxOptimal->checkState() == Qt::Checked)	
		itsThread.setOptimal(true);
	else
		itsThread.setOptimal(false);
	itsThread.start();
}

void QtInformationstag::plan_erstellt() {
	
	// ist der Thread mit seiner Aufgabe fertig, wurde der Plan erstellt
	
	ui.treeVeranstaltungen->clear();  // Zunächst wird das Feld nochmal gelöscht
	
 	ui.labelStatus->hide();
	ui.btPlanErstellen->setEnabled(true);
	ui.btAbbrechen->setEnabled(false);
 	
 	// Falls er abgebrochen wurde, soll kein Plan angezeigt werden
 	if (abgebrochen == true) {
 		ui.labelStatus->setText(QString::fromUtf8("Berechnung läuft..."));
 		abgebrochen = false;
 		return;
 	}
 	
 	// itsInformationstag auslesen
	int anzTermine = itsInformationstag.getAnzTermine();
	int anzVeranstaltungen = itsInformationstag.getAnzVeranstaltungen();
	cVeranstaltung * veranstaltungen = itsInformationstag.getVeranstaltungen(); // die Veranstaltungen  
	
	int anzTeilnehmer;  // Die Teilnehmer pro Veranstaltunge
	
	// dann den Plan im TreeWidget ausgeben
	QTreeWidgetItem * itemTermin;
	QTreeWidgetItem * itemVeranstaltung;
	QTreeWidgetItem * itemTeilnehmer;
	
	QFont font;
	int gesTeilnehmer;
	
	for (int i = 0; i < anzTermine; i++) {
		itemTermin = new QTreeWidgetItem(1);  // neues Item mit nur einer Spalte
		
		gesTeilnehmer = 0;
			
		for (int j = 0; j < anzVeranstaltungen; j++)
			if (veranstaltungen[j].getTermin() == i) {
				itemVeranstaltung = new QTreeWidgetItem(1);
				
				anzTeilnehmer = veranstaltungen[j].getAnzTeilnehmer();
				for (int k = 0; k < anzTeilnehmer; k++) {
					itemTeilnehmer = new QTreeWidgetItem(1);
					itemTeilnehmer->setText(0, veranstaltungen[j].getTeilnehmer(k)->getName());
					
					itemVeranstaltung->addChild(itemTeilnehmer);
				}
				
				itemVeranstaltung->setText(0, veranstaltungen[j].getTyp()->getName() + "   ( " + QString::number(veranstaltungen[j].getAnzTeilnehmer()) + " )");
				font.setBold(true);
				font.setUnderline(false);
				itemVeranstaltung->setFont(0, font);				
				
					
				itemTermin->addChild(itemVeranstaltung);
				gesTeilnehmer += veranstaltungen[j].getAnzTeilnehmer();
			}
			
		itemTermin->setText(0, "Termin " + QString::number(i+1) + "   ( " + QString::number(itemTermin->childCount()) + "  -  " + QString::number(gesTeilnehmer) + " )");
		font.setBold(true);
		font.setUnderline(true);
		itemTermin->setFont(0,font);
	
		ui.treeVeranstaltungen->addTopLevelItem(itemTermin);
		ui.treeVeranstaltungen->topLevelItem(i)->setExpanded(true);
		
	}
}

void QtInformationstag::on_btAbbrechen_clicked() {
	
	// da es etwas dauert, bis itsThread abgebrochen ist, soll er sich erstmal merken, dass abgebrochen wurde
	abgebrochen = true;	
	itsThread.terminate();
	
	on_btVeranstaltungenEntfernen_clicked(); // und das Feld wieder geleert
	
	// solange das Abbrechen dauert, wird dies angezeigt
	ui.labelStatus->setText("Berechnung wird abgebrochen!");
	

	// in der Zeit kann man keinen Button klicken
	ui.btPlanErstellen->setEnabled(false);
	ui.btAbbrechen->setEnabled(false);
}

void QtInformationstag::on_btVeranstaltungenEntfernen_clicked() {
	ui.treeVeranstaltungen->clear();
	itsInformationstag.VeranstaltungenLoeschen();
}



void QtInformationstag::on_btPrioritaetenVerwenden_clicked() {
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	int prioritaeten[anzWuensche];
	
	// Auslesen
	for (int i = 0; i < anzWuensche; i++)
		prioritaeten[i] = sBoxPrioritaeten[i].value();	

	//  an itsInformationstag weiterleiten
	itsInformationstag.setPrioritaeten(prioritaeten);
}

void QtInformationstag::on_btVorlageHinzufuegen_clicked() {

	ui.btVorlageHinzufuegen->setEnabled(false);

	// aktuelle Werte merken
	
	int min = ui.sBoxMin->value();
	int max = ui.sBoxMax->value();
	QString name = ui.nameAngebot->text();

	////// Vorgefertige Angebote: ////////

	ui.sBoxMin->setValue(25);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Manager");
	on_btAngebotHinzufuegen_clicked();

	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(35);
	ui.nameAngebot->setText("Pilot");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(50);
	ui.nameAngebot->setText("Politiker");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(25);
	ui.sBoxMax->setValue(45);
	ui.nameAngebot->setText("Programmierer");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Koordinator");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(30);
	ui.nameAngebot->setText("Schauspieler");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(35);
	ui.nameAngebot->setText(QString::fromUtf8("Gärtner"));
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Architekt");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(25);
	ui.sBoxMax->setValue(45);
	ui.nameAngebot->setText("Designer");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(45);
	ui.nameAngebot->setText(QString::fromUtf8("Künstler"));
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(60);
	ui.nameAngebot->setText("Reporter");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Journalist");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(25);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Schriftsteller");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(50);
	ui.nameAngebot->setText("Verleger");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(30);
	ui.sBoxMax->setValue(55);
	ui.nameAngebot->setText("Erzieher");
	on_btAngebotHinzufuegen_clicked();
	
	ui.sBoxMin->setValue(20);
	ui.sBoxMax->setValue(40);
	ui.nameAngebot->setText("Arzt");
	on_btAngebotHinzufuegen_clicked();
	
	// alten Werte wieder laden
	ui.sBoxMin->setValue(min);
	ui.sBoxMax->setValue(max);
	ui.nameAngebot->setText(name);
}	
	
void QtInformationstag::on_btZufaellig1_clicked() {
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	int anzahlAngebote = ui.tableAngebote->rowCount();
	if (anzahlAngebote < anzWuensche)  // wenns zu wenige sind, soll abgebrochen werden
		return;
	
	ui.nameTeilnehmer->setText( QString::fromUtf8("Schüler ") + QString::number(ui.tableTeilnehmer->rowCount() + 1));
	
	int wunsch[anzWuensche];
	
	for (int i = 0; i < anzWuensche; i++) { // fuer jeden Wunsch
		wunsch[i] = (rand() % anzahlAngebote) + 1; // soll solange zufaellig ein Wunsch ausgewaehlt werden
		
		for (int j = 0; j < i; j++)
			if (wunsch[j] == wunsch[i]) { // bis er sich von allen vorigen Wuensche unterscheidet
				i--;  // ansonsten muss ein neuer Wunsch zufaellig ermittelt werden
				break;
			}
	}

	for (int i = 0; i < anzWuensche; i++)  // die Wuensche in die ComboBox eintragen
		cBoxWunschBox[i].setCurrentIndex(wunsch[i]); 
	
}

void QtInformationstag::on_btZufaellig10_clicked() {
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	// alte Werte merken
	QString currentName = ui.nameTeilnehmer->text();
	int currentIndex[anzWuensche];
	
	for (int i = 0; i < anzWuensche; i++)
		currentIndex[i] = cBoxWunschBox[i].currentIndex();
	
	if( ui.tableAngebote->rowCount() < anzWuensche)
		return;
	
	// 10-mal Zufaellig einen Teilnehmer erstellen
	for (int i = 0; i < 10; i++) {
		on_btZufaellig1_clicked();
		on_btTeilnehmerHinzufuegen_clicked();
	}


	// Alten Werte wieder erstellen
	ui.nameTeilnehmer->setText(currentName);
	
	for (int i = 0; i < anzWuensche; i++)
		cBoxWunschBox[i].setCurrentIndex(currentIndex[i]);	
	
}



void QtInformationstag::when_sBoxMax_changed(int value) {
	// Min immer kleiner als Max
	if (ui.sBoxMin->value() >= value)
		ui.sBoxMin->setValue(value - 1);
}

void QtInformationstag::when_sBoxMin_changed(int value) {
	// Max immer groesser als Min
	if (ui.sBoxMax->value() <= value)
		ui.sBoxMax->setValue(value + 1);
}


void QtInformationstag::when_sBoxAnzTermine_changed(int value) {
	// AnzWuensche immer groesser gleich AnzTermine
	if (ui.sBoxAnzWuensche->value() < value)
		ui.sBoxAnzWuensche->setValue(value);
}

void QtInformationstag::when_sBoxAnzWuensche_changed(int value) {
	// anz Termine immer kleiner gleich AnzWuensche
	if (ui.sBoxAnzTermine->value() > value)
		ui.sBoxAnzTermine->setValue(value);
}



void QtInformationstag::btAngebotHinzufuegen_deaktivieren(QString text) {
	// wenn kein Name eingetragen wurde, soll der Button deaktiviert werden
	if (text != "")
		ui.btAngebotHinzufuegen->setEnabled(true);
	else
		ui.btAngebotHinzufuegen->setEnabled(false);
}
	
void QtInformationstag::btTeilnehmerHinzufuegen_deaktivieren(QString text) {
	// wenn kein Name eingetragen wurde, oder ein Wunsch doppelt oder gar nicht ausgewaehlt wurde, soll der Button deaktivert werden
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	bool indexdoppelt = false;

	for (int i = 0; i < anzWuensche; i++)
		if (IndexDoppelt(cBoxWunschBox[i].currentIndex()) == true || cBoxWunschBox[i].currentIndex() == 0) // wenn ein Wunsch doppelt oder gar nicht ausgewaehlt wurde
			indexdoppelt = true;
	
	if (text != "" && indexdoppelt == false)
		ui.btTeilnehmerHinzufuegen->setEnabled(true);
	else
		ui.btTeilnehmerHinzufuegen->setEnabled(false);
	
}

void QtInformationstag::btTeilnehmerHinzufuegen_deaktivieren(int nix) { 
	// Damit der Slot aufgerufen werden kann, wenn ein Index von einer der WunschBoxen geaendert wurde
	if (nix != -1) // bedingung stimmt immmer! nur zum Benutzern von nix und umgehen eines Errors!
		btTeilnehmerHinzufuegen_deaktivieren(ui.nameTeilnehmer->text()); // leitet die Aufgabe an den anderen Slot weiter
}

void QtInformationstag::when_AnzAngebote_changed() {
	// wenn noch zu wenig Angebote bestehen, soll man nicht zufaellig Teilnehmer erstellen duerfen
	if( ui.tableAngebote->rowCount() >= itsInformationstag.getAnzWuensche()) {
		ui.btZufaellig1->setEnabled(true);
		ui.btZufaellig10->setEnabled(true);
	}
	else {		
		ui.btZufaellig1->setEnabled(false);
		ui.btZufaellig10->setEnabled(false);
	}
}

void QtInformationstag::wunschBox_index_changed(int index) {
	// Wenn ein Index einer wunschBox geaendert wurde, soll geguckt werden, ob ein Index doppelt existiert und dann rot einfaerben
	int anzWuensche = itsInformationstag.getAnzWuensche();
	QPalette standardPalette;
	QPalette rotePalette;
	rotePalette.setColor(QPalette::ButtonText, Qt::red);
	for (int i = 0; i < anzWuensche; i++) {
		index = cBoxWunschBox[i].currentIndex();
		if (IndexDoppelt(index) == true) {  // wenn es den Index doppelt gibt, sollen alle Rot eingefaerbt werden
			for (int j = 0; j < anzWuensche; j++)
				if (cBoxWunschBox[j].currentIndex() == index)
					cBoxWunschBox[j].setPalette(rotePalette);
		}
		else 
			cBoxWunschBox[i].setPalette(standardPalette);
	}
}


bool QtInformationstag::IndexDoppelt(int index) {
	// Die Hilfsmethode prueft, ob der uebergebene Index doppelt existiert
	if (index == 0) // 0 ist eine ausnahme
		return false;
	
	int anzahl = 0;
	
	int anzWuensche = itsInformationstag.getAnzWuensche();
	
	for (int i = 0; i < anzWuensche; i++)
		if (cBoxWunschBox[i].currentIndex() == index)
			anzahl++;
	
	if (anzahl > 1) // wenn er haeufiger als einmal vorgekommen ist, so gibt es ihn doppelt
		return true;
	else
		return false;
}
