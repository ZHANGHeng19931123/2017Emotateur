#include "introdialog.h"
#include "ui_introdialog.h"
#include<iostream>

IntroDialog::IntroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroDialog)
{
    ui->setupUi(this);

    QPixmap pixmap(":/interface/imagesInterface/images.jpeg");
    QPalette palette;
    palette.setBrush(ui->label->backgroundRole(),QBrush(pixmap));
    ui->label->setPalette(palette);
    ui->label->setAutoFillBackground(true);
}

IntroDialog::~IntroDialog()
{
    delete ui;
}
