/********************************************************************************
** Form generated from reading UI file 'Director.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTOR_H
#define UI_DIRECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Director
{
public:

    void setupUi(QWidget *Director)
    {
        if (Director->objectName().isEmpty())
            Director->setObjectName(QStringLiteral("Director"));
        Director->resize(800, 600);

        retranslateUi(Director);

        QMetaObject::connectSlotsByName(Director);
    } // setupUi

    void retranslateUi(QWidget *Director)
    {
        Director->setWindowTitle(QApplication::translate("Director", "Director", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Director: public Ui_Director {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTOR_H
