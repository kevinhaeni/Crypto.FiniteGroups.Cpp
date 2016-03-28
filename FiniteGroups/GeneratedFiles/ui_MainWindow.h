/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModuloClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbInput;
    QLabel *label_2;
    QComboBox *cbOperation;
    QSpacerItem *horizontalSpacer;
    QCheckBox *cbSubGroups;
    QPushButton *btnDraw;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ModuloClass)
    {
        if (ModuloClass->objectName().isEmpty())
            ModuloClass->setObjectName(QStringLiteral("ModuloClass"));
        ModuloClass->resize(887, 719);
        centralWidget = new QWidget(ModuloClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        sbInput = new QSpinBox(centralWidget);
        sbInput->setObjectName(QStringLiteral("sbInput"));
        sbInput->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(sbInput);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        cbOperation = new QComboBox(centralWidget);
        cbOperation->setObjectName(QStringLiteral("cbOperation"));
        cbOperation->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(cbOperation);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cbSubGroups = new QCheckBox(centralWidget);
        cbSubGroups->setObjectName(QStringLiteral("cbSubGroups"));

        horizontalLayout->addWidget(cbSubGroups);

        btnDraw = new QPushButton(centralWidget);
        btnDraw->setObjectName(QStringLiteral("btnDraw"));
        btnDraw->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(btnDraw);


        verticalLayout->addLayout(horizontalLayout);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        ModuloClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModuloClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 887, 21));
        ModuloClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ModuloClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ModuloClass->setStatusBar(statusBar);

        retranslateUi(ModuloClass);

        QMetaObject::connectSlotsByName(ModuloClass);
    } // setupUi

    void retranslateUi(QMainWindow *ModuloClass)
    {
        ModuloClass->setWindowTitle(QApplication::translate("ModuloClass", "Finite Groups", 0));
        label->setText(QApplication::translate("ModuloClass", "Modulo:", 0));
        label_2->setText(QApplication::translate("ModuloClass", "Operation", 0));
        cbSubGroups->setText(QApplication::translate("ModuloClass", "Include Subgroups", 0));
        btnDraw->setText(QApplication::translate("ModuloClass", "Draw group", 0));
    } // retranslateUi

};

namespace Ui {
    class ModuloClass: public Ui_ModuloClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
