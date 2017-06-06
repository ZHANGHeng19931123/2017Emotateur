#include "expressionrecogniser.h"

ExpressionRecogniser::ExpressionRecogniser(std::string dataPath): dataPath(dataPath)
{
}

void ExpressionRecogniser::setDataPath(std::string dataPath)
{
    this->dataPath = dataPath;
}

std::vector<EmoPoint> ExpressionRecogniser::getFacePoints(cv::Mat_<unsigned char> img)
{

    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords

    if  (!stasm_search_single(&foundface,  landmarks,
                              (char*)img.data, img.cols, img.rows, this->dataPath.c_str(), this->dataPath.c_str()))
    {
        printf("Error in stasm_search_single: %s\n", stasm_lasterr()); exit(1);
    }

    if (!foundface)
    {
        return std::vector<EmoPoint>();
    }
    else
    {
        stasm_force_points_into_image(landmarks,  img.cols,  img.rows);
        std::vector<EmoPoint> landmarkVector;
        for (int i = 0; i < stasm_NLANDMARKS; i++)
            landmarkVector.push_back(EmoPoint(landmarks[i*2+1], landmarks[i*2]));
        return landmarkVector;
    }
}

void ExpressionRecogniser::loadImg1Points(cv::Mat_<unsigned char> img1)
{
    img1Points.clear();
    img1Points = this->getFacePoints(img1);
}

double ExpressionRecogniser::getSimilarity(cv::Mat_<unsigned char> img1, cv::Mat_<unsigned char> img2)
{
    loadImg1Points(img1);
    return this->getSimilarity(img2);
}

void ExpressionRecogniser::alignement(int posCoor1, int posCoor2, int posCoor3){
    a = (double(img1Points.at(posCoor2).getY())-double(img1Points.at(posCoor1).getY()))/(double(img2Points.at(posCoor2).getY())-double(img2Points.at(posCoor1).getY()));
    a = fabs(a);
    c = double(img1Points.at(posCoor3).getX()) - a*double(img2Points.at(posCoor3).getX());
    d = double(img1Points.at(posCoor3).getY()) - a*double(img2Points.at(posCoor3).getY());
}

void ExpressionRecogniser::calculDistanceSwainBallardMouth()
{
    Point points1[1][12];
    for (int i = 0; i < mouthCompareNum; ++i) {
        points1[0][i] = img1Points.at(mouthCompareOrder[i]).toPoint();
    }
    const Point* pt1[1] = { points1[0] };
    int npt1[1] = {mouthCompareNum};
    polylines( histogrammeSwainBallard1, pt1, npt1, 1, 1, Scalar(255)) ;
    fillPoly( histogrammeSwainBallard1, pt1, npt1, 1, Scalar(255), 8);
    if(foundface)
    {
        alignement(59, 65, 62);
        Point points2[1][12];
        for (int i = 0; i < mouthCompareNum; ++i) {
            points2[0][i] = img2Points.at(mouthCompareOrder[i]).afterChange(a,c,d).toPoint();
            //points2[0][i] = img2Points.at(mouthCompareOrder[i]).toPoint();
        }
        const Point* pt2[1] = { points2[0] };
        int npt2[1] = {mouthCompareNum};
        polylines( histogrammeSwainBallard2, pt2, npt2, 1, 1, Scalar(255)) ;
        fillPoly( histogrammeSwainBallard2, pt2, npt2, 1, Scalar(255), 8);
    }
}

void ExpressionRecogniser::calculDistanceSwainBallardLeftEye(){
    Point points1[1][8];
    for (int i = 0; i < leftEyeCompareNum; ++i) {
        points1[0][i] = img1Points.at(leftEyeCompareOrder[i]).toPoint();
    }
    const Point* pt1[1] = { points1[0] };
    int npt1[1] = {leftEyeCompareNum};
    polylines( histogrammeSwainBallard1, pt1, npt1, 1, 1, Scalar(255)) ;
    fillPoly( histogrammeSwainBallard1, pt1, npt1, 1, Scalar(255), 8);
    if(foundface)
    {
        alignement(34, 30, 38);
        Point points2[1][8];
        for (int i = 0; i < leftEyeCompareNum; ++i) {
            points2[0][i] = img2Points.at(leftEyeCompareOrder[i]).afterChange(a,c,d).toPoint();
            //points2[0][i] = img2Points.at(leftEyeCompareOrder[i]).toPoint();
        }
        const Point* pt2[1] = { points2[0] };
        int npt2[1] = {leftEyeCompareNum};
        polylines( histogrammeSwainBallard2, pt2, npt2, 1, 1, Scalar(255)) ;
        fillPoly( histogrammeSwainBallard2, pt2, npt2, 1, Scalar(255), 8);
    }
}

void ExpressionRecogniser::calculDistanceSwainBallardRightEye(){
    Point points1[1][8];
    for (int i = 0; i < rightEyeCompareNum; ++i) {
        points1[0][i] = img1Points.at(rightEyeCompareOrder[i]).toPoint();
    }
    const Point* pt1[1] = { points1[0] };
    int npt1[1] = {rightEyeCompareNum};
    polylines( histogrammeSwainBallard1, pt1, npt1, 1, 1, Scalar(255)) ;
    fillPoly( histogrammeSwainBallard1, pt1, npt1, 1, Scalar(255), 8);
    if(foundface)
    {
        alignement(40, 44, 39);
        Point points2[1][8];
        for (int i = 0; i < rightEyeCompareNum; ++i) {
            points2[0][i] = img2Points.at(rightEyeCompareOrder[i]).afterChange(a,c,d).toPoint();
            //points2[0][i] = img2Points.at(rightEyeCompareOrder[i]).toPoint();
        }
        const Point* pt2[1] = { points2[0] };
        int npt2[1] = {rightEyeCompareNum};
        polylines( histogrammeSwainBallard2, pt2, npt2, 1, 1, Scalar(255)) ;
        fillPoly( histogrammeSwainBallard2, pt2, npt2, 1, Scalar(255), 8);
    }
}

void ExpressionRecogniser::calculDistanceSwainBallardLeftEyeBrow(){
    Point points1[1][6];
    for (int i = 0; i < leftEyebrowCompareNum; ++i) {
        points1[0][i] = img1Points.at(leftEyebrowCompareOrder[i]).toPoint();
    }
    const Point* pt1[1] = { points1[0] };
    int npt1[1] = {leftEyebrowCompareNum};
    polylines( histogrammeSwainBallard1, pt1, npt1, 1, 1, Scalar(255)) ;
    fillPoly( histogrammeSwainBallard1, pt1, npt1, 1, Scalar(255), 8);
    if(foundface)
    {
        alignement(18, 21, 21);
        Point points2[1][6];
        for (int i = 0; i < leftEyebrowCompareNum; ++i) {
            points2[0][i] = img2Points.at(leftEyebrowCompareOrder[i]).afterChange(a,c,d).toPoint();
            //points2[0][i] = img2Points.at(leftEyebrowCompareOrder[i]).toPoint();
        }
        const Point* pt2[1] = { points2[0] };
        int npt2[1] = {leftEyebrowCompareNum};
        polylines( histogrammeSwainBallard2, pt2, npt2, 1, 1, Scalar(255)) ;
        fillPoly( histogrammeSwainBallard2, pt2, npt2, 1, Scalar(255), 8);
    }
}

void ExpressionRecogniser::calculDistanceSwainBallardRightEyeBrow(){
    Point points1[1][6];
    for (int i = 0; i < rightEyebrowCompareNum; ++i) {
        points1[0][i] = img1Points.at(rightEyebrowCompareOrder[i]).toPoint();
    }
    const Point* pt1[1] = { points1[0] };
    int npt1[1] = {rightEyebrowCompareNum};
    polylines( histogrammeSwainBallard1, pt1, npt1, 1, 1, Scalar(255)) ;
    fillPoly( histogrammeSwainBallard1, pt1, npt1, 1, Scalar(255), 8);
    if(foundface)
    {
        alignement(22, 25, 22);
        Point points2[1][6];
        for (int i = 0; i < rightEyebrowCompareNum; ++i) {
            points2[0][i] = img2Points.at(rightEyebrowCompareOrder[i]).afterChange(a,c,d).toPoint();
            //points2[0][i] = img2Points.at(rightEyebrowCompareOrder[i]).toPoint();
        }
        const Point* pt2[1] = { points2[0] };
        int npt2[1] = {rightEyebrowCompareNum};
        polylines( histogrammeSwainBallard2, pt2, npt2, 1, 1, Scalar(255)) ;
        fillPoly( histogrammeSwainBallard2, pt2, npt2, 1, Scalar(255), 8);
    }
}

double ExpressionRecogniser::getSimilarity(cv::Mat_<unsigned char> img2)
{
    img2Points = this->getFacePoints(img2);
    histogrammeSwainBallard1 = Mat(240, 320, CV_8UC1, Scalar(0));
    histogrammeSwainBallard2 = Mat(240, 320, CV_8UC1, Scalar(0));
    calculDistanceSwainBallardMouth();
    calculDistanceSwainBallardLeftEye();
    calculDistanceSwainBallardRightEye();
    calculDistanceSwainBallardLeftEyeBrow();
    calculDistanceSwainBallardRightEyeBrow();
    if(foundface){
        double temp1 = 0;
        double temp2 = 0;
        for(int i = 0; i < histogrammeSwainBallard1.rows; i++){
            for (int j = 0; j < histogrammeSwainBallard1.cols; j ++){
                if(histogrammeSwainBallard1.at<uchar>(i,j) == 255){
                    temp1++;
                }
                if(histogrammeSwainBallard2.at<uchar>(i,j) == 255 && histogrammeSwainBallard1.at<uchar>(i,j) == 255){
                    temp2++;
                }
            }
        }
        return temp2/temp1;
    }else{
        return 0.00;
    }
}
