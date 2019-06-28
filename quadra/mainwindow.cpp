#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openGLWidget->context();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    OGLWidget::_LINESIZE = 1.0f + (position * 0.05f);
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    OGLWidget::_COLOR.r = GLfloat (value / 255.0);
}

void MainWindow::on_spinBox_2_valueChanged(int value)
{
    OGLWidget::_COLOR.g = GLfloat (value / 255.0);
}

void MainWindow::on_spinBox_3_valueChanged(int value)
{
    OGLWidget::_COLOR.b = GLfloat (value / 255.0);
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Naive 1")
    {
        OGLWidget::_NAIVE1ALGO = true;
        OGLWidget::_NAIVE2ALGO = false;
    }
    else if(arg1 == "Naive 2")
    {
        OGLWidget::_NAIVE1ALGO = false;
        OGLWidget::_NAIVE2ALGO = true;
    }
    else if(arg1 == "Bresenham")
    {
        OGLWidget::_NAIVE1ALGO = false;
        OGLWidget::_NAIVE2ALGO = false;
    }
}

