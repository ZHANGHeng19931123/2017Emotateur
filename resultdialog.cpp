#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    vLayout = new QVBoxLayout();
    imgNum = 0;

    QWidget *client = new QWidget;

    ui->scrollArea_->setBackgroundRole(QPalette::Light);
    ui->scrollArea_->setWidgetResizable(true);
    ui->scrollArea_->setWidget(client);

    client->setLayout(vLayout);

}


ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::addImage(QImage img1, QImage img2)
{
    imgNum++;

    ui->resultLabel_->setText("Vous avez reussi a imiter " + QString::number(imgNum) + " expressions!");

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->setAlignment(Qt::AlignHCenter);

    hLayout->addStretch();

    QLabel *originalImageLabel = new QLabel();
    originalImageLabel->setPixmap(QPixmap::fromImage(img1));
    originalImageLabel->resize(img1.size());
    hLayout->addWidget(originalImageLabel);

    QLabel *imitImageLabel = new QLabel();
    imitImageLabel->setPixmap(QPixmap::fromImage(img2));
    imitImageLabel->resize(img2.size());
    hLayout->addWidget(imitImageLabel);

    hLayout->addStretch();

    vLayout->addLayout(hLayout);
}


void ResultDialog::on_closeButton__clicked()
{
    this->close();
}
