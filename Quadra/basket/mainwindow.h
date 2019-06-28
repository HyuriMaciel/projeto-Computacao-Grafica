#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_clicked(bool checked);

    void on_lineR_valueChanged(double arg1);

    void on_loneG_valueChanged(double arg1);

    void on_lineB_valueChanged(double arg1);

    void on_backR_valueChanged(double arg1);

    void on_backG_valueChanged(double arg1);

    void on_backB_valueChanged(double arg1);

    void on_lineS_valueChanged(double arg1);

    void on_pushButton_2_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
