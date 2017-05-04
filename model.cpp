#include "model.h"

Model::Model(ExpressionRecogniser *expressionRecogniser) : expressionRecogniser(expressionRecogniser)
{
    imageNum = 1;
    difficulity = 99;
    loadNextImage();
    score = 0;
}

bool Model::pass(double similarite)
{
    if(similarite >= difficulity)
    {
        score +=1;
        return true;
    }
    else
    {
        return false;
    }
}

void Model::loadNextImage()
{
    // load images of different formats
    QString path=QString(":/imagesMaterial/imagesBase/ImageEmotion%1").arg(imageNum);
    currentQImage = QImage(path);
    currentMat = QImage2cvMat(currentQImage);
    cv::cvtColor(currentMat,currentMat,CV_BGR2RGB);
    cv::cvtColor(currentMat,currentMatGray,CV_RGB2GRAY);
    //int *t = expressionRecogniser->getContour(currentMatGray);
    //rectTemplate = cv::Rect(t[1],t[2],abs(t[3]-t[1]),abs(t[4]-t[2]));
    //cv::rectangle(currentMat,rectTemplate,cv::Scalar( 0, 0, 255),2,8,0);
    //QImage image = QImage((uchar*)(currentMat.data), currentMat.cols, currentMat.rows, QImage::Format_RGB888);
    //currentQPixmap=QPixmap::fromImage(image);
    currentQPixmap=QPixmap::fromImage(currentQImage);

    // load img1Points
    expressionRecogniser->loadImg1Points(currentMatGray);
}

cv::Mat Model::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

void Model::changeImage()
{
    imageNum++;
    if(imageNum == 10)
    {
        imageNum = 1;
    }
    loadNextImage();
}
