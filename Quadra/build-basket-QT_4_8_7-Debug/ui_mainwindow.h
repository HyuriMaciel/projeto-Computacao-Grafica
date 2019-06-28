/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *X;
    QDoubleSpinBox *Y;
    QDoubleSpinBox *Z;
    QLabel *label_2;
    QDoubleSpinBox *R;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    GLWidget *GLwidget;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 480);
        MainWindow->setMinimumSize(QSize(640, 480));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        X = new QDoubleSpinBox(centralWidget);
        X->setObjectName(QString::fromUtf8("X"));
        X->setMinimum(-99);

        horizontalLayout_2->addWidget(X);

        Y = new QDoubleSpinBox(centralWidget);
        Y->setObjectName(QString::fromUtf8("Y"));
        Y->setMinimum(-99);

        horizontalLayout_2->addWidget(Y);

        Z = new QDoubleSpinBox(centralWidget);
        Z->setObjectName(QString::fromUtf8("Z"));
        Z->setMinimum(-99);

        horizontalLayout_2->addWidget(Z);


        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        R = new QDoubleSpinBox(centralWidget);
        R->setObjectName(QString::fromUtf8("R"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(R->sizePolicy().hasHeightForWidth());
        R->setSizePolicy(sizePolicy);
        R->setValue(1);

        verticalLayout->addWidget(R);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_2);

        GLwidget = new GLWidget(centralWidget);
        GLwidget->setObjectName(QString::fromUtf8("GLwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(GLwidget->sizePolicy().hasHeightForWidth());
        GLwidget->setSizePolicy(sizePolicy1);
        pushButton->raise();

        horizontalLayout->addWidget(GLwidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(released()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Basket", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Position", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Radius", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
