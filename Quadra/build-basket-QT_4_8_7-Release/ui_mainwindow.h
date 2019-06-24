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
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_3;
    QDoubleSpinBox *lineR;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *loneG;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QDoubleSpinBox *lineB;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_7;
    QDoubleSpinBox *backR;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_6;
    QDoubleSpinBox *backG;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QDoubleSpinBox *backB;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QDoubleSpinBox *lineS;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    GLWidget *GLwidget;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
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
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_7->addWidget(label_3);

        lineR = new QDoubleSpinBox(centralWidget);
        lineR->setObjectName(QString::fromUtf8("lineR"));
        lineR->setMaximum(255);
        lineR->setValue(255);

        verticalLayout_7->addWidget(lineR);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_6->addWidget(label_2);

        loneG = new QDoubleSpinBox(centralWidget);
        loneG->setObjectName(QString::fromUtf8("loneG"));
        loneG->setMaximum(255);
        loneG->setValue(255);

        verticalLayout_6->addWidget(loneG);


        horizontalLayout_3->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);

        lineB = new QDoubleSpinBox(centralWidget);
        lineB->setObjectName(QString::fromUtf8("lineB"));
        lineB->setMaximum(255);
        lineB->setValue(255);

        verticalLayout_5->addWidget(lineB);


        horizontalLayout_3->addLayout(verticalLayout_5);


        horizontalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_2);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_10->addWidget(label_7);

        backR = new QDoubleSpinBox(centralWidget);
        backR->setObjectName(QString::fromUtf8("backR"));
        backR->setMaximum(255);

        verticalLayout_10->addWidget(backR);


        horizontalLayout_4->addLayout(verticalLayout_10);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_9->addWidget(label_6);

        backG = new QDoubleSpinBox(centralWidget);
        backG->setObjectName(QString::fromUtf8("backG"));
        backG->setMaximum(255);

        verticalLayout_9->addWidget(backG);


        horizontalLayout_4->addLayout(verticalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_8->addWidget(label_5);

        backB = new QDoubleSpinBox(centralWidget);
        backB->setObjectName(QString::fromUtf8("backB"));
        backB->setMaximum(255);

        verticalLayout_8->addWidget(backB);


        horizontalLayout_4->addLayout(verticalLayout_8);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        lineS = new QDoubleSpinBox(centralWidget);
        lineS->setObjectName(QString::fromUtf8("lineS"));
        lineS->setMinimum(1);
        lineS->setMaximum(100);
        lineS->setValue(1);

        horizontalLayout_5->addWidget(lineS);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_2);

        GLwidget = new GLWidget(centralWidget);
        GLwidget->setObjectName(QString::fromUtf8("GLwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GLwidget->sizePolicy().hasHeightForWidth());
        GLwidget->setSizePolicy(sizePolicy);
        GLwidget->setMaximumSize(QSize(500, 500));

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
        label_4->setText(QApplication::translate("MainWindow", "Line color", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "G", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "B", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Background color", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "G", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "B", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Size", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Bresenham", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Limpar Arquibancadas", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
