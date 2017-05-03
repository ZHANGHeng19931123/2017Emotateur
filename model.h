#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QPixmap>
#include <QSize>
#include <QString>
#include <QImage>
#include <QDebug>

#include <iostream>
#include "opencv2/opencv.hpp"
#include "stasm/stasm_lib.h"

#include "expressionrecogniser.h"


class Model
{
public:
    Model(ExpressionRecogniser *expressionRecogniser);
    bool pass(double similarite);

    double getScore(){return score;}

    cv::Rect getRectangle(){return rectTemplate;}

    cv::Mat_<unsigned char> getCurrentMatGray(){return currentMatGray;}
    cv::Mat getCurrentMat(){ return currentMat;}
    QPixmap getCurrentQPixmap(){return currentQPixmap;}
    QImage getCurrentQImage(){return currentQImage;}

    int getImageNum(){return imageNum;}
    void changeImage();
    void loadNextImage();

private:
    QVector<QPixmap> *imgBase;

    int score;
    int imageNum;
    ExpressionRecogniser *expressionRecogniser;

    cv::Rect rectTemplate;
    cv::Mat QImage2cvMat(QImage image);
    double difficulity;

    QImage currentQImage;
    cv::Mat currentMat;
    cv::Mat_<unsigned char> currentMatGray;
    QPixmap currentQPixmap;

};

#endif // MODEL_H
