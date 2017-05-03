#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "introdialog.h"

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
    void on_button_start_clicked();

    void on_button_intro_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
