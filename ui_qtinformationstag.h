/********************************************************************************
** Form generated from reading ui file 'qtinformationstag.ui'
**
** Created: Tue Apr 1 05:48:26 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QTINFORMATIONSTAG_H
#define UI_QTINFORMATIONSTAG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_QtInformationstagClass
{
public:
    QLabel *labelInformationstag;
    QPushButton *btBeenden;
    QGroupBox *gBoxAngebot;
    QLabel *labelNameAngebot;
    QLabel *labelMin;
    QLabel *labelMax;
    QLineEdit *nameAngebot;
    QSpinBox *sBoxMin;
    QSpinBox *sBoxMax;
    QPushButton *btAngebotHinzufuegen;
    QTableWidget *tableAngebote;
    QPushButton *btVorlageHinzufuegen;
    QPushButton *btAngebotEntfernen;
    QGroupBox *gBoxTeilnehmer;
    QLabel *labelNameTeilnehmer;
    QLineEdit *nameTeilnehmer;
    QPushButton *btTeilnehmerHinzufuegen;
    QTableWidget *tableTeilnehmer;
    QPushButton *btTeilnehmerEntfernen;
    QPushButton *btZufaellig1;
    QPushButton *btZufaellig10;
    QGroupBox *gBoxVeranstaltungen;
    QTreeWidget *treeVeranstaltungen;
    QPushButton *btVeranstaltungenEntfernen;
    QPushButton *btPlanErstellen;
    QCheckBox *cBoxOptimal;
    QPushButton *btAbbrechen;
    QLabel *labelStatus;
    QGroupBox *gBoxEinstellungen;
    QPushButton *btEinstellungenVerwenden;
    QSpinBox *sBoxAnzWuensche;
    QSpinBox *sBoxAnzTermine;
    QLabel *labelAnzahlTermine;
    QLabel *labelAnzahlWuensche;
    QPushButton *btAllesNeu;
    QGroupBox *gBoxPrioritaeten;
    QPushButton *btPrioritaetenVerwenden;
    QLabel *label;

    void setupUi(QWidget *QtInformationstagClass)
    {
    if (QtInformationstagClass->objectName().isEmpty())
        QtInformationstagClass->setObjectName(QString::fromUtf8("QtInformationstagClass"));
    QtInformationstagClass->resize(952, 626);
    QtInformationstagClass->setMinimumSize(QSize(952, 626));
    QtInformationstagClass->setMaximumSize(QSize(952, 626));
    labelInformationstag = new QLabel(QtInformationstagClass);
    labelInformationstag->setObjectName(QString::fromUtf8("labelInformationstag"));
    labelInformationstag->setGeometry(QRect(10, 10, 931, 36));
    QFont font;
    font.setPointSize(20);
    font.setBold(false);
    font.setWeight(50);
    labelInformationstag->setFont(font);
    labelInformationstag->setAlignment(Qt::AlignCenter);
    btBeenden = new QPushButton(QtInformationstagClass);
    btBeenden->setObjectName(QString::fromUtf8("btBeenden"));
    btBeenden->setGeometry(QRect(830, 590, 111, 27));
    gBoxAngebot = new QGroupBox(QtInformationstagClass);
    gBoxAngebot->setObjectName(QString::fromUtf8("gBoxAngebot"));
    gBoxAngebot->setGeometry(QRect(200, 80, 481, 191));
    labelNameAngebot = new QLabel(gBoxAngebot);
    labelNameAngebot->setObjectName(QString::fromUtf8("labelNameAngebot"));
    labelNameAngebot->setGeometry(QRect(20, 60, 57, 18));
    labelMin = new QLabel(gBoxAngebot);
    labelMin->setObjectName(QString::fromUtf8("labelMin"));
    labelMin->setGeometry(QRect(20, 120, 57, 18));
    labelMax = new QLabel(gBoxAngebot);
    labelMax->setObjectName(QString::fromUtf8("labelMax"));
    labelMax->setGeometry(QRect(20, 90, 57, 18));
    nameAngebot = new QLineEdit(gBoxAngebot);
    nameAngebot->setObjectName(QString::fromUtf8("nameAngebot"));
    nameAngebot->setGeometry(QRect(90, 60, 131, 23));
    sBoxMin = new QSpinBox(gBoxAngebot);
    sBoxMin->setObjectName(QString::fromUtf8("sBoxMin"));
    sBoxMin->setGeometry(QRect(150, 120, 71, 23));
    sBoxMin->setMinimum(1);
    sBoxMin->setValue(10);
    sBoxMax = new QSpinBox(gBoxAngebot);
    sBoxMax->setObjectName(QString::fromUtf8("sBoxMax"));
    sBoxMax->setGeometry(QRect(150, 90, 71, 23));
    sBoxMax->setMinimum(2);
    sBoxMax->setValue(20);
    btAngebotHinzufuegen = new QPushButton(gBoxAngebot);
    btAngebotHinzufuegen->setObjectName(QString::fromUtf8("btAngebotHinzufuegen"));
    btAngebotHinzufuegen->setEnabled(false);
    btAngebotHinzufuegen->setGeometry(QRect(10, 150, 101, 27));
    tableAngebote = new QTableWidget(gBoxAngebot);
    tableAngebote->setObjectName(QString::fromUtf8("tableAngebote"));
    tableAngebote->setGeometry(QRect(230, 20, 241, 161));
    tableAngebote->setSelectionMode(QAbstractItemView::SingleSelection);
    tableAngebote->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableAngebote->setColumnCount(4);
    btVorlageHinzufuegen = new QPushButton(gBoxAngebot);
    btVorlageHinzufuegen->setObjectName(QString::fromUtf8("btVorlageHinzufuegen"));
    btVorlageHinzufuegen->setGeometry(QRect(110, 20, 111, 27));
    btAngebotEntfernen = new QPushButton(gBoxAngebot);
    btAngebotEntfernen->setObjectName(QString::fromUtf8("btAngebotEntfernen"));
    btAngebotEntfernen->setGeometry(QRect(120, 150, 101, 27));
    gBoxTeilnehmer = new QGroupBox(QtInformationstagClass);
    gBoxTeilnehmer->setObjectName(QString::fromUtf8("gBoxTeilnehmer"));
    gBoxTeilnehmer->setGeometry(QRect(10, 280, 491, 331));
    labelNameTeilnehmer = new QLabel(gBoxTeilnehmer);
    labelNameTeilnehmer->setObjectName(QString::fromUtf8("labelNameTeilnehmer"));
    labelNameTeilnehmer->setGeometry(QRect(10, 70, 57, 18));
    nameTeilnehmer = new QLineEdit(gBoxTeilnehmer);
    nameTeilnehmer->setObjectName(QString::fromUtf8("nameTeilnehmer"));
    nameTeilnehmer->setGeometry(QRect(90, 70, 131, 23));
    btTeilnehmerHinzufuegen = new QPushButton(gBoxTeilnehmer);
    btTeilnehmerHinzufuegen->setObjectName(QString::fromUtf8("btTeilnehmerHinzufuegen"));
    btTeilnehmerHinzufuegen->setEnabled(false);
    btTeilnehmerHinzufuegen->setGeometry(QRect(10, 290, 101, 27));
    tableTeilnehmer = new QTableWidget(gBoxTeilnehmer);
    tableTeilnehmer->setObjectName(QString::fromUtf8("tableTeilnehmer"));
    tableTeilnehmer->setGeometry(QRect(230, 20, 251, 301));
    tableTeilnehmer->setSelectionMode(QAbstractItemView::SingleSelection);
    tableTeilnehmer->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableTeilnehmer->setColumnCount(8);
    btTeilnehmerEntfernen = new QPushButton(gBoxTeilnehmer);
    btTeilnehmerEntfernen->setObjectName(QString::fromUtf8("btTeilnehmerEntfernen"));
    btTeilnehmerEntfernen->setGeometry(QRect(120, 290, 101, 27));
    btZufaellig1 = new QPushButton(gBoxTeilnehmer);
    btZufaellig1->setObjectName(QString::fromUtf8("btZufaellig1"));
    btZufaellig1->setEnabled(false);
    btZufaellig1->setGeometry(QRect(10, 30, 101, 27));
    btZufaellig10 = new QPushButton(gBoxTeilnehmer);
    btZufaellig10->setObjectName(QString::fromUtf8("btZufaellig10"));
    btZufaellig10->setEnabled(false);
    btZufaellig10->setGeometry(QRect(120, 30, 101, 27));
    gBoxVeranstaltungen = new QGroupBox(QtInformationstagClass);
    gBoxVeranstaltungen->setObjectName(QString::fromUtf8("gBoxVeranstaltungen"));
    gBoxVeranstaltungen->setGeometry(QRect(690, 80, 251, 501));
    treeVeranstaltungen = new QTreeWidget(gBoxVeranstaltungen);
    treeVeranstaltungen->setObjectName(QString::fromUtf8("treeVeranstaltungen"));
    treeVeranstaltungen->setGeometry(QRect(10, 130, 231, 321));
    btVeranstaltungenEntfernen = new QPushButton(gBoxVeranstaltungen);
    btVeranstaltungenEntfernen->setObjectName(QString::fromUtf8("btVeranstaltungenEntfernen"));
    btVeranstaltungenEntfernen->setGeometry(QRect(70, 460, 111, 27));
    btPlanErstellen = new QPushButton(gBoxVeranstaltungen);
    btPlanErstellen->setObjectName(QString::fromUtf8("btPlanErstellen"));
    btPlanErstellen->setGeometry(QRect(20, 60, 101, 27));
    cBoxOptimal = new QCheckBox(gBoxVeranstaltungen);
    cBoxOptimal->setObjectName(QString::fromUtf8("cBoxOptimal"));
    cBoxOptimal->setGeometry(QRect(30, 30, 83, 22));
    btAbbrechen = new QPushButton(gBoxVeranstaltungen);
    btAbbrechen->setObjectName(QString::fromUtf8("btAbbrechen"));
    btAbbrechen->setEnabled(false);
    btAbbrechen->setGeometry(QRect(130, 60, 101, 27));
    labelStatus = new QLabel(gBoxVeranstaltungen);
    labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
    labelStatus->setGeometry(QRect(10, 100, 231, 20));
    QPalette palette;
    QBrush brush(QColor(139, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    QBrush brush1(QColor(119, 119, 121, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    labelStatus->setPalette(palette);
    QFont font1;
    font1.setBold(true);
    font1.setWeight(75);
    labelStatus->setFont(font1);
    labelStatus->setAlignment(Qt::AlignCenter);
    gBoxEinstellungen = new QGroupBox(QtInformationstagClass);
    gBoxEinstellungen->setObjectName(QString::fromUtf8("gBoxEinstellungen"));
    gBoxEinstellungen->setGeometry(QRect(10, 80, 181, 191));
    btEinstellungenVerwenden = new QPushButton(gBoxEinstellungen);
    btEinstellungenVerwenden->setObjectName(QString::fromUtf8("btEinstellungenVerwenden"));
    btEinstellungenVerwenden->setGeometry(QRect(40, 110, 101, 27));
    sBoxAnzWuensche = new QSpinBox(gBoxEinstellungen);
    sBoxAnzWuensche->setObjectName(QString::fromUtf8("sBoxAnzWuensche"));
    sBoxAnzWuensche->setGeometry(QRect(100, 70, 71, 23));
    sBoxAnzWuensche->setMinimum(1);
    sBoxAnzWuensche->setMaximum(20);
    sBoxAnzWuensche->setValue(6);
    sBoxAnzTermine = new QSpinBox(gBoxEinstellungen);
    sBoxAnzTermine->setObjectName(QString::fromUtf8("sBoxAnzTermine"));
    sBoxAnzTermine->setGeometry(QRect(100, 30, 71, 23));
    sBoxAnzTermine->setMinimum(1);
    sBoxAnzTermine->setMaximum(10);
    sBoxAnzTermine->setValue(4);
    labelAnzahlTermine = new QLabel(gBoxEinstellungen);
    labelAnzahlTermine->setObjectName(QString::fromUtf8("labelAnzahlTermine"));
    labelAnzahlTermine->setGeometry(QRect(10, 30, 52, 18));
    labelAnzahlWuensche = new QLabel(gBoxEinstellungen);
    labelAnzahlWuensche->setObjectName(QString::fromUtf8("labelAnzahlWuensche"));
    labelAnzahlWuensche->setGeometry(QRect(10, 70, 61, 18));
    btAllesNeu = new QPushButton(gBoxEinstellungen);
    btAllesNeu->setObjectName(QString::fromUtf8("btAllesNeu"));
    btAllesNeu->setGeometry(QRect(40, 150, 101, 27));
    gBoxPrioritaeten = new QGroupBox(QtInformationstagClass);
    gBoxPrioritaeten->setObjectName(QString::fromUtf8("gBoxPrioritaeten"));
    gBoxPrioritaeten->setGeometry(QRect(510, 280, 171, 331));
    btPrioritaetenVerwenden = new QPushButton(gBoxPrioritaeten);
    btPrioritaetenVerwenden->setObjectName(QString::fromUtf8("btPrioritaetenVerwenden"));
    btPrioritaetenVerwenden->setGeometry(QRect(30, 290, 111, 27));
    label = new QLabel(QtInformationstagClass);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 50, 931, 20));
    label->setAlignment(Qt::AlignCenter);

    retranslateUi(QtInformationstagClass);
    QObject::connect(btBeenden, SIGNAL(clicked()), QtInformationstagClass, SLOT(close()));

    QMetaObject::connectSlotsByName(QtInformationstagClass);
    } // setupUi

    void retranslateUi(QWidget *QtInformationstagClass)
    {
    QtInformationstagClass->setWindowTitle(QApplication::translate("QtInformationstagClass", "Informationstag", 0, QApplication::UnicodeUTF8));
    labelInformationstag->setText(QApplication::translate("QtInformationstagClass", "Informationstag", 0, QApplication::UnicodeUTF8));
    btBeenden->setText(QApplication::translate("QtInformationstagClass", "Beenden", 0, QApplication::UnicodeUTF8));
    gBoxAngebot->setTitle(QApplication::translate("QtInformationstagClass", "Angebote", 0, QApplication::UnicodeUTF8));
    labelNameAngebot->setText(QApplication::translate("QtInformationstagClass", "Name:", 0, QApplication::UnicodeUTF8));
    labelMin->setText(QApplication::translate("QtInformationstagClass", "Minimal:", 0, QApplication::UnicodeUTF8));
    labelMax->setText(QApplication::translate("QtInformationstagClass", "Maximal:", 0, QApplication::UnicodeUTF8));
    nameAngebot->setText(QString());
    btAngebotHinzufuegen->setText(QApplication::translate("QtInformationstagClass", "Hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
    if (tableAngebote->columnCount() < 4)
        tableAngebote->setColumnCount(4);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    __colItem->setText(QApplication::translate("QtInformationstagClass", "ID", 0, QApplication::UnicodeUTF8));
    tableAngebote->setHorizontalHeaderItem(0, __colItem);

    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    __colItem1->setText(QApplication::translate("QtInformationstagClass", "Angebot", 0, QApplication::UnicodeUTF8));
    tableAngebote->setHorizontalHeaderItem(1, __colItem1);

    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    __colItem2->setText(QApplication::translate("QtInformationstagClass", "Min", 0, QApplication::UnicodeUTF8));
    tableAngebote->setHorizontalHeaderItem(2, __colItem2);

    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    __colItem3->setText(QApplication::translate("QtInformationstagClass", "Max", 0, QApplication::UnicodeUTF8));
    tableAngebote->setHorizontalHeaderItem(3, __colItem3);
    btVorlageHinzufuegen->setText(QApplication::translate("QtInformationstagClass", "Vorlage", 0, QApplication::UnicodeUTF8));
    btAngebotEntfernen->setText(QApplication::translate("QtInformationstagClass", "Entfernen", 0, QApplication::UnicodeUTF8));
    gBoxTeilnehmer->setTitle(QApplication::translate("QtInformationstagClass", "Teilnehmer", 0, QApplication::UnicodeUTF8));
    labelNameTeilnehmer->setText(QApplication::translate("QtInformationstagClass", "Name:", 0, QApplication::UnicodeUTF8));
    btTeilnehmerHinzufuegen->setText(QApplication::translate("QtInformationstagClass", "Hinzuf\303\274gen", 0, QApplication::UnicodeUTF8));
    if (tableTeilnehmer->columnCount() < 8)
        tableTeilnehmer->setColumnCount(8);

    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    __colItem4->setText(QApplication::translate("QtInformationstagClass", "ID", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(0, __colItem4);

    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    __colItem5->setText(QApplication::translate("QtInformationstagClass", "Teilnehmer", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(1, __colItem5);

    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    __colItem6->setText(QApplication::translate("QtInformationstagClass", "Wunsch 1", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(2, __colItem6);

    QTableWidgetItem *__colItem7 = new QTableWidgetItem();
    __colItem7->setText(QApplication::translate("QtInformationstagClass", "Wunsch 2", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(3, __colItem7);

    QTableWidgetItem *__colItem8 = new QTableWidgetItem();
    __colItem8->setText(QApplication::translate("QtInformationstagClass", "Wunsch 3", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(4, __colItem8);

    QTableWidgetItem *__colItem9 = new QTableWidgetItem();
    __colItem9->setText(QApplication::translate("QtInformationstagClass", "Wunsch 4", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(5, __colItem9);

    QTableWidgetItem *__colItem10 = new QTableWidgetItem();
    __colItem10->setText(QApplication::translate("QtInformationstagClass", "Wunsch 5", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(6, __colItem10);

    QTableWidgetItem *__colItem11 = new QTableWidgetItem();
    __colItem11->setText(QApplication::translate("QtInformationstagClass", "Wunsch 6", 0, QApplication::UnicodeUTF8));
    tableTeilnehmer->setHorizontalHeaderItem(7, __colItem11);
    btTeilnehmerEntfernen->setText(QApplication::translate("QtInformationstagClass", "Entfernen", 0, QApplication::UnicodeUTF8));
    btZufaellig1->setText(QApplication::translate("QtInformationstagClass", "Zuf\303\244llig (1)", 0, QApplication::UnicodeUTF8));
    btZufaellig10->setText(QApplication::translate("QtInformationstagClass", "Zuf\303\244llig (10)", 0, QApplication::UnicodeUTF8));
    gBoxVeranstaltungen->setTitle(QApplication::translate("QtInformationstagClass", "Veranstaltungen", 0, QApplication::UnicodeUTF8));
    treeVeranstaltungen->headerItem()->setText(0, QApplication::translate("QtInformationstagClass", "1", 0, QApplication::UnicodeUTF8));
    btVeranstaltungenEntfernen->setText(QApplication::translate("QtInformationstagClass", "Entfernen", 0, QApplication::UnicodeUTF8));
    btPlanErstellen->setText(QApplication::translate("QtInformationstagClass", "Plan erstellen", 0, QApplication::UnicodeUTF8));
    cBoxOptimal->setText(QApplication::translate("QtInformationstagClass", "Optimal", 0, QApplication::UnicodeUTF8));
    btAbbrechen->setText(QApplication::translate("QtInformationstagClass", "Abbrechen", 0, QApplication::UnicodeUTF8));
    labelStatus->setText(QApplication::translate("QtInformationstagClass", "Berechnung l\303\244uft...", 0, QApplication::UnicodeUTF8));
    gBoxEinstellungen->setTitle(QApplication::translate("QtInformationstagClass", "Einstellungen", 0, QApplication::UnicodeUTF8));
    btEinstellungenVerwenden->setText(QApplication::translate("QtInformationstagClass", "Verwenden", 0, QApplication::UnicodeUTF8));
    labelAnzahlTermine->setText(QApplication::translate("QtInformationstagClass", "Termine:", 0, QApplication::UnicodeUTF8));
    labelAnzahlWuensche->setText(QApplication::translate("QtInformationstagClass", "W\303\274nsche:", 0, QApplication::UnicodeUTF8));
    btAllesNeu->setText(QApplication::translate("QtInformationstagClass", "Alles Neu", 0, QApplication::UnicodeUTF8));
    gBoxPrioritaeten->setTitle(QApplication::translate("QtInformationstagClass", "Priorit\303\244ten", 0, QApplication::UnicodeUTF8));
    btPrioritaetenVerwenden->setText(QApplication::translate("QtInformationstagClass", "Verwenden", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("QtInformationstagClass", "Ein Beitrag zum 26. Bundeswettbewerb Informatik von Leon Sering", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(QtInformationstagClass);
    } // retranslateUi

};

namespace Ui {
    class QtInformationstagClass: public Ui_QtInformationstagClass {};
} // namespace Ui

#endif // UI_QTINFORMATIONSTAG_H
