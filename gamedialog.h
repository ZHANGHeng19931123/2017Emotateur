#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPixmap>
#include <QWidget>
#include <QDir>
#include <QSize>
#include <QImage>
#include <QMessageBox>
#include <QPainter>

#include <cmath>
#include "opencv2/opencv.hpp"
#include "stasm/stasm_lib.h"

#include "expressionrecogniser.h"
#include "model.h"
#include "resultdialog.h"
#include "EmoPoint.h"


using namespace cv;

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = 0);
    ~GameDialog();

private:
    Ui::GameDialog *ui;    

    int timeLeft;
    int waitTime;
    int gameTime;
    bool gameStart;

    Mat srcMat;
    QImage srcQImage;
    QPixmap srcQPixmap;
    cv::Mat_<unsigned char> srcMatGray;

    QTimer checkSimilarityTimer;
    QTimer secondCountDownTimer;

    VideoCapture videoCap;
    ExpressionRecogniser *expressRecogniser;
    ResultDialog * resultDialog;

    QSize imageSize;
    Model * model;

    void showMessage(QString message);
    void drawLine(QPixmap * p, int i);

private slots:
    void updateImage();
    void secondCountDown();
    void on_changeButton_clicked();
    void on_quitButton_clicked();

};

#endif // GAMEDIALOG_H
