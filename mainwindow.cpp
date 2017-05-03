#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setAutoFillBackground(true);

    QPixmap pixmap(":/interface/imagesInterface/background.png");
    QPalette palette;
    palette.setBrush(ui->centralWidget->backgroundRole(),QBrush(pixmap));
    ui->centralWidget->setPalette(palette);
    ui->centralWidget->setAutoFillBackground(true);

    this->setFixedSize(pixmap.size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_start_clicked()
{
    GameDialog fenetreJeu(this);
    fenetreJeu.exec();
}

void MainWindow::on_button_intro_clicked()
{
    IntroDialog introDia(this);
    introDia.exec();
}
