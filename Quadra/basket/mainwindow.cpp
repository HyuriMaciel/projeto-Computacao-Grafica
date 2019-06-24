#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    this->ui->GLwidget->bresenham = checked;
}

void MainWindow::on_lineR_valueChanged(double arg1)
{
    this->ui->GLwidget->lineColorR = arg1;
}

void MainWindow::on_loneG_valueChanged(double arg1)
{
    this->ui->GLwidget->lineColorG = arg1;
}

void MainWindow::on_lineB_valueChanged(double arg1)
{
    this->ui->GLwidget->lineColorB = arg1;
}

void MainWindow::on_backR_valueChanged(double arg1)
{
    this->ui->GLwidget->backColorR = arg1;
}

void MainWindow::on_backG_valueChanged(double arg1)
{
    this->ui->GLwidget->backColorG = arg1;
}

void MainWindow::on_backB_valueChanged(double arg1)
{
    this->ui->GLwidget->backColorB = arg1;
}

void MainWindow::on_lineS_valueChanged(double arg1)
{
    this->ui->GLwidget->lineS = arg1;
}

void MainWindow::on_pushButton_2_pressed()
{
    printf("Checked");
    this->ui->GLwidget->reset = true;
}
