/********************************************************************************
** Form generated from reading UI file 'LimitUsageGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIMITUSAGEGUI_H
#define UI_LIMITUSAGEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LimitUsageGUIClass
{
public:
    QWidget *centralWidget;
    QLabel *debugLabel;

    void setupUi(QMainWindow *LimitUsageGUIClass)
    {
        if (LimitUsageGUIClass->objectName().isEmpty())
            LimitUsageGUIClass->setObjectName(QStringLiteral("LimitUsageGUIClass"));
        LimitUsageGUIClass->resize(180, 16);
        LimitUsageGUIClass->setMaximumSize(QSize(180, 16));
        centralWidget = new QWidget(LimitUsageGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        debugLabel = new QLabel(centralWidget);
        debugLabel->setObjectName(QStringLiteral("debugLabel"));
        debugLabel->setGeometry(QRect(0, 0, 181, 16));
        LimitUsageGUIClass->setCentralWidget(centralWidget);

        retranslateUi(LimitUsageGUIClass);

        QMetaObject::connectSlotsByName(LimitUsageGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *LimitUsageGUIClass)
    {
        debugLabel->setText(QString());
        Q_UNUSED(LimitUsageGUIClass);
    } // retranslateUi

};

namespace Ui {
    class LimitUsageGUIClass: public Ui_LimitUsageGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIMITUSAGEGUI_H
