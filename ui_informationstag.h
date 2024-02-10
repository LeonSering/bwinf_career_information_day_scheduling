/********************************************************************************
** Form generated from reading ui file 'informationstag.ui'
**
** Created: Sun Mar 23 16:13:47 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFORMATIONSTAG_H
#define UI_INFORMATIONSTAG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

class Ui_InformationstagClass
{
public:

    void setupUi(QWidget *InformationstagClass)
    {
    if (InformationstagClass->objectName().isEmpty())
        InformationstagClass->setObjectName(QString::fromUtf8("InformationstagClass"));
    InformationstagClass->resize(400, 300);

    retranslateUi(InformationstagClass);

    QMetaObject::connectSlotsByName(InformationstagClass);
    } // setupUi

    void retranslateUi(QWidget *InformationstagClass)
    {
    InformationstagClass->setWindowTitle(QApplication::translate("InformationstagClass", "Informationstag", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InformationstagClass);
    } // retranslateUi

};

namespace Ui {
    class InformationstagClass: public Ui_InformationstagClass {};
} // namespace Ui

#endif // UI_INFORMATIONSTAG_H
