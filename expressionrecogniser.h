#ifndef EXPRESSIONRECOGNISER_H
#define EXPRESSIONRECOGNISER_H

#include <vector>
#include <string.h>
#include <QDateTime>
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <math.h>
#include "opencv/highgui.h"
#include "stasm/stasm_lib.h"

#include "point.h"

using namespace std;

class ExpressionRecogniser
{
public:
    ExpressionRecogniser(std::string dataPath);
    void setDataPath(std::string dataPath);
    int* getContour(cv::Mat_<unsigned char> img);
    std::vector<EmoPoint> getFacePoints(cv::Mat_<unsigned char> img);
    std::vector<EmoPoint> getAllImg2FacePoints(){return img2Points;}
    std::vector<EmoPoint> getPartImg1FacePoints(){std::cout << "img1 part points size: " << img1PartPoints.size() << std::endl;return img1PartPoints;}
    std::vector<EmoPoint> getPartImg2FacePoints(){std::cout << "img2 part points size: " << img2PartPoints.size() << std::endl;return img2PartPoints;}
    double getSimilarity(cv::Mat_<unsigned char> img1, cv::Mat_<unsigned char> currentImg1);
    double getSimilarity(cv::Mat_<unsigned char> currentImg1);
    void loadImg1Points(cv::Mat_<unsigned char> img1);

private:
    std::string dataPath;
    int foundface;
    std::vector<EmoPoint> img1Points;
    std::vector<EmoPoint> img2Points;
    std::vector<EmoPoint> img1PartPoints;
    std::vector<EmoPoint> img2PartPoints;

    const int mouthComparePosCoor1 = 59;
    const int mouthComparePosCoor2 = 65;
    const int mouthCompareOrder[2] = {62, 74};
    const int mouthCompareNum = 2;
//    double mouthDistance;
    const double mouthWeighting = 0.5;

    const int leftEyeComparePosCoor1 = 30;
    const int leftEyeComparePosCoor2 = 34;
    const int leftEyeCompareOrder[2] = {32, 36};
    const int leftEyeCompareNum = 2;
//    double leftEyeDistance;
    const double leftEyeWeighting = 0.17;

    const int rightEyeComparePosCoor1 = 40;
    const int rightEyeComparePosCoor2 = 44;
    const int rightEyeCompareOrder[2] = {42, 46};
    const int rightEyeCompareNum = 2;
//    double rightEyeDistance;
    const double rightEyeWeighting = 0.17;

    const int leftEyebrowComparePosCoor1 = 30;
    const int leftEyebrowComparePosCoor2 = 34;
    const int leftEyebrowCompareOrder[2] = {36, 17};
    const int leftEyebrowCompareNum = 2;
//    double LeftEyebrowDistance;
    const double leftEyeBrowWeighting = 0.1;

    const int rightEyebrowComparePosCoor1 = 40;
    const int rightEyebrowComparePosCoor2 = 44;
    const int rightEyebrowCompareOrder[2] = {48, 24};
    const int rightEyebrowCompareNum = 2;
//    double rightEyebrowDistance;
    const double rightEyeBrowWeighting = 0.1;

    float a, b, c, d;
    double similarity;
    double histo1[5] = {0,0,0,0,0};
    double histo2[5] = {0,0,0,0,0};
    void getAbcd(int posCoor1, int posCoor2);
    void distanceIntersection();
};

#endif // EXPRESSIONRECOGNISER_H
