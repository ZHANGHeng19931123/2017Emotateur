#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();
    void addImage(QImage img1, QImage img2);

private slots:

    void on_closeButton__clicked();

private:
    Ui::ResultDialog *ui;
    int imgNum;
    QVBoxLayout * vLayout;
};

#endif // RESULTDIALOG_H
