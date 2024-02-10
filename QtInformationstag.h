#ifndef QTINFORMATIONSTAG_H
#define QTINFORMATIONSTAG_H

#include <iostream>
using namespace std;

// Qt
#include <QString>
#include <QScrollArea>
#include <QComboBox>
#include <QHeaderView>
#include <QList>
#include <QPalette>


#include "ui_qtinformationstag.h"

// eigene
#include "cInformationstag.h"
#include "cThread.h"

class QtInformationstag : public QWidget
{
    Q_OBJECT

public:
    QtInformationstag(QWidget *parent = 0);
    ~QtInformationstag();
    
private:
	cInformationstag itsInformationstag;

    Ui::QtInformationstagClass ui;
    
    // WunschBox
    QScrollArea scrollWunschBox;
    QWidget widgetWunschBox;
    QComboBox * cBoxWunschBox;
    QLabel * labelWunschBox;
    
    // Prioritaeten
    QScrollArea scrollPrioritaeten;
    QWidget widgetPrioritaeten;
    QSpinBox * sBoxPrioritaeten;
    QLabel * labelPrioritaeten;
    
    // Thread
    cThread itsThread; // um Berechnungen im Hintergrund laufen lassen zu koennen
    bool abgebrochen; // merkt sich, ob abgebrochen wurde (da das Abbrechen-Klicken und "fertig abgebrochen" zeitlich auseinander liegen )
    
    
    bool IndexDoppelt(int index);
    
public slots:

	// Button-Slots
	void on_btEinstellungenVerwenden_clicked();
	void on_btAllesNeu_clicked();

	void on_btAngebotHinzufuegen_clicked();
	void on_btAngebotEntfernen_clicked();
		
	void on_btTeilnehmerHinzufuegen_clicked();
	void on_btTeilnehmerEntfernen_clicked();
	
	void on_btPlanErstellen_clicked();
	void on_btVeranstaltungenEntfernen_clicked();
	void on_btAbbrechen_clicked();
	
	void on_btVorlageHinzufuegen_clicked();
	void on_btZufaellig1_clicked();
	void on_btZufaellig10_clicked();
	
	void on_btPrioritaetenVerwenden_clicked();
	
	// Groesser-Kleiner-Slots
	void when_sBoxMax_changed(int value);
	void when_sBoxMin_changed(int value);
	
	void when_sBoxAnzWuensche_changed(int value);
	void when_sBoxAnzTermine_changed(int value);
	
	// Buttondeaktivier-Slots
	void btAngebotHinzufuegen_deaktivieren(QString text);
	void btTeilnehmerHinzufuegen_deaktivieren(QString text);
	void btTeilnehmerHinzufuegen_deaktivieren(int nix);  // Parameter macht nichts, ist nur fuer die Verknuepfung mit dem Signal
	
	// WuenschBox modifizieren
	void when_AnzAngebote_changed();
	void wunschBox_index_changed(int index);
	
	// Planerstellen
	void plan_erstellt();  // wird aufgerufen, sobald itsThread den Plan fertig erstellt hat. Plan wird hier ausgegeben


};

#endif // QTINFORMATIONSTAG_H
