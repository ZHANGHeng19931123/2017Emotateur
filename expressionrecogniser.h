#ifndef EXPRESSIONRECOGNISER_H
#define EXPRESSIONRECOGNISER_H

#include <vector>
#include <string.h>
#include <QDateTime>
#include <QImage>
#include <QPixmap>

#include "opencv/highgui.h"
#include "stasm/stasm_lib.h"
#include <math.h>

#include "EmoPoint.h"

using namespace std;

class ExpressionRecogniser
{
public:
    ExpressionRecogniser(std::string dataPath);
    void setDataPath(std::string dataPath);
    void calculDistanceSwainBallardMouth();
    void calculDistanceSwainBallardLeftEye();
    void calculDistanceSwainBallardRightEye();
    void calculDistanceSwainBallardLeftEyeBrow();
    void calculDistanceSwainBallardRightEyeBrow();
    void alignement(int posCoor1, int posCoor2, int posCoor3);
    double getSimilarity(cv::Mat_<unsigned char> img1, cv::Mat_<unsigned char> currentImg1);
    double getSimilarity(cv::Mat_<unsigned char> currentImg1);
    void loadImg1Points(cv::Mat_<unsigned char> img1);

private:
    Mat histogrammeSwainBallard1 , histogrammeSwainBallard2;
    std::string dataPath;
    int foundface;
    std::vector<EmoPoint> img1Points;
    std::vector<EmoPoint> img2Points;
    const int mouthCompareOrder[12] = {59, 60, 61, 62, 63, 64, 65, 72, 73, 74, 75, 76};
    const int mouthCompareNum = 12;
    const int leftEyeCompareOrder[8] = {30, 31, 32, 33, 34, 35, 36, 37};
    const int leftEyeCompareNum = 8;
    const int rightEyeCompareOrder[8] = {40, 41, 42, 43, 44, 45, 46, 47};
    const int rightEyeCompareNum = 8;
    const int leftEyebrowCompareOrder[6] = {16, 17, 18, 19, 20, 21};
    const int leftEyebrowCompareNum = 6;
    const int rightEyebrowCompareOrder[6] = {22, 23, 24, 25, 26, 27};
    const int rightEyebrowCompareNum = 6;
    double a, b, c, d;
    std::vector<EmoPoint> getFacePoints(cv::Mat_<unsigned char> img);
    std::vector<EmoPoint> getAllImg2FacePoints(){return img2Points;}
};

#endif // EXPRESSIONRECOGNISER_H
