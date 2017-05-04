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

    std::cout << "Sucess: load image! size: " << img1Points.size() << std::endl;
}

double ExpressionRecogniser::getSimilarity(cv::Mat_<unsigned char> img1, cv::Mat_<unsigned char> img2)
{
    loadImg1Points(img1);
    return this->getSimilarity(img2);
}


void ExpressionRecogniser::getAbcd(int posCoor1, int posCoor2)
{
    // M
    double m[2][2] = {{img2Points.at(posCoor1).getX(), img2Points.at(posCoor1).getY()}, {img2Points.at(posCoor2).getX(), img2Points.at(posCoor2).getY()}};
    cv::Mat M = cv::Mat(2, 2, CV_64F, m);
    cv::invert(M,M);

    // Y1
    double y1[2][1] = {{img1Points.at(posCoor1).getX()},{img1Points.at(posCoor2).getX()}};
    cv::Mat Y1(2,1,CV_64F,y1);

    // a and b
    cv::Mat ab = cv::Mat(2, 1, CV_64F);
    ab = M*Y1;
    a = ab.at<double>(0,0);
    b = ab.at<double>(1,0);

    // Y2
    double y2[2][1] = {{img1Points.at(posCoor1).getY()},{img1Points.at(posCoor2).getY()}};
    cv::Mat Y2(2,1,CV_64F,y2);

    // c and d
    cv::Mat cd = cv::Mat(2, 1, CV_64F);
    cd = M*Y2;
    c = cd.at<double>(0,0);
    d = cd.at<double>(1,0);
}

void ExpressionRecogniser::distanceIntersection()
{
    cout << "" << histo1[0] << " " << histo1[1] << " " << histo1[2] << " " << histo1[3] << " " << histo1[4] << endl;
    cout << "" << histo2[0] << " " << histo2[1] << " " << histo2[2] << " " << histo2[3] << " " << histo2[4] << endl;
    double temp0, temp1, temp2;
    for (int i = 0; i < 5; i ++)
    {
        temp0 += std::min(histo1[i], histo2[i]);
        temp1 += histo1[i];
        temp2 += histo2[i];
    }

    similarity = temp0/std::min(temp1, temp2);
}

double ExpressionRecogniser::getSimilarity(cv::Mat_<unsigned char> img2)
{
    img2Points = this->getFacePoints(img2);
    if(foundface)
    {
        std::cout << "Face found : " << QDateTime::currentDateTime().toString().toStdString() << std::endl;

        // compare mouth
        getAbcd(mouthComparePosCoor1, mouthComparePosCoor2);

        //        mouthDistance = 0;

        // load img2 and img1 part points
        //        img1PartPoints.clear();
        //        img2PartPoints.clear();

        // load img2 and img1 part points
        //        img1PartPoints.push_back(img2Points.at(mouthComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(mouthComparePosCoor1));
        //        img1PartPoints.push_back(img2Points.at(mouthComparePosCoor2).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(mouthComparePosCoor2));

        histo1[0] = img1Points.at(mouthCompareOrder[0]).getDistanceY(img1Points.at(mouthCompareOrder[1]));
        histo2[0] = img2Points.at(mouthCompareOrder[0]).getDistanceY(img2Points.at(mouthCompareOrder[1]));


        //        for(int i = 0; i < mouthCompareNum; i ++)
        //        {
        //            // calcul distance of mouth
        //            mouthDistance += img1Points.at(mouthCompareOrder[i]).getDistanceY(img2Points.at(mouthCompareOrder[i]).afterChange(a,b,c,d));
        //            // load img2 and img1 part points
        //            img1PartPoints.push_back(img2Points.at(mouthCompareOrder[i]).afterChange(a,b,c,d));
        //            img2PartPoints.push_back(img2Points.at(mouthCompareOrder[i]));
        //         }

        // compare left eye
        getAbcd(leftEyeComparePosCoor1, leftEyeComparePosCoor2);

        // load img2 and img1 part points
        //        img1PartPoints.push_back(img2Points.at(leftEyeComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(leftEyeComparePosCoor2));
        //        img1PartPoints.push_back(img2Points.at(leftEyeComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(leftEyeComparePosCoor2));

        histo1[1] = img1Points.at(leftEyeCompareOrder[0]).getDistanceY(img1Points.at(leftEyeCompareOrder[1]));
        histo2[1] = img2Points.at(leftEyeCompareOrder[0]).getDistanceY(img2Points.at(leftEyeCompareOrder[1]));

        //        leftEyeDistance = 0;
        //        for(int i = 0; i < leftEyeCompareNum; i ++)
        //        {
        //            leftEyeDistance += img1Points.at(leftEyeCompareOrder[i]).getDistanceY(img2Points.at(leftEyeCompareOrder[i]).afterChange(a,b,c,d));

        //            // load img2 and img1 part points
        //            img1PartPoints.push_back(img2Points.at(leftEyeCompareOrder[i]).afterChange(a,b,c,d));
        //            img2PartPoints.push_back(img2Points.at(leftEyeCompareOrder[i]));
        //        }

        // compare rightEye
        getAbcd(rightEyeComparePosCoor1, rightEyeComparePosCoor2);

        // load img2 and img1 part points
        //        img1PartPoints.push_back(img2Points.at(rightEyeComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(rightEyeComparePosCoor1));
        //        img1PartPoints.push_back(img2Points.at(rightEyeComparePosCoor2).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(rightEyeComparePosCoor2));

        histo1[2] = img1Points.at(rightEyeCompareOrder[0]).getDistanceY(img1Points.at(rightEyeCompareOrder[1]));
        histo2[2] = img2Points.at(rightEyeCompareOrder[0]).getDistanceY(img2Points.at(rightEyeCompareOrder[1]));

        //        rightEyeDistance = 0;
        //        for(int i = 0; i < rightEyeCompareNum; i ++)
        //        {
        //            rightEyeDistance += img1Points.at(rightEyeCompareOrder[i]).getDistanceY(img2Points.at(rightEyeCompareOrder[i]).afterChange(a,b,c,d));
        //            // load img2 and img1 part points
        //            img1PartPoints.push_back(img2Points.at(rightEyeCompareOrder[i]).afterChange(a,b,c,d));
        //            img2PartPoints.push_back(img2Points.at(rightEyeCompareOrder[i]));
        //        }

        // compare left eyebrow
        getAbcd(leftEyebrowComparePosCoor1, leftEyebrowComparePosCoor2);

        // load img2 and img1 part points
        //        img1PartPoints.push_back(img2Points.at(leftEyebrowComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(leftEyebrowComparePosCoor1));
        //        img1PartPoints.push_back(img2Points.at(leftEyebrowComparePosCoor2).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(leftEyebrowComparePosCoor2));

        histo1[3] = img1Points.at(leftEyebrowCompareOrder[0]).getDistanceY(img1Points.at(leftEyebrowCompareOrder[1]));
        histo2[3] = img2Points.at(leftEyebrowCompareOrder[0]).getDistanceY(img2Points.at(leftEyebrowCompareOrder[1]));

        //        LeftEyebrowDistance = 0;
        //        for(int i = 0; i < leftEyebrowCompareNum; i ++)
        //        {
        //            LeftEyebrowDistance += img1Points.at(leftEyebrowCompareOrder[i]).getDistanceY(img2Points.at(leftEyebrowCompareOrder[i]).afterChange(a,b,c,d));
        //            // load img2 and img1 part points
        //            img1PartPoints.push_back(img2Points.at(leftEyebrowCompareOrder[i]).afterChange(a,b,c,d));
        //            img2PartPoints.push_back(img2Points.at(leftEyebrowCompareOrder[i]));
        //        }

        // compare right eyebrow
        getAbcd(rightEyebrowComparePosCoor1, rightEyebrowComparePosCoor2);

        // load img2 and img1 part points
        //        img1PartPoints.push_back(img2Points.at(rightEyebrowComparePosCoor1).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(rightEyebrowComparePosCoor1));
        //        img1PartPoints.push_back(img2Points.at(rightEyebrowComparePosCoor2).afterChange(a,b,c,d));
        //        img2PartPoints.push_back(img2Points.at(rightEyebrowComparePosCoor2));

        histo1[4] = img1Points.at(rightEyebrowCompareOrder[0]).getDistanceY(img1Points.at(rightEyebrowCompareOrder[1]));
        histo2[4] = img2Points.at(rightEyebrowCompareOrder[0]).getDistanceY(img2Points.at(rightEyebrowCompareOrder[1]));

        //        rightEyebrowDistance = 0;
        //        for(int i = 0; i < rightEyebrowCompareNum; i ++)
        //        {
        //            rightEyebrowDistance += img1Points.at(rightEyebrowCompareOrder[i]).getDistanceY(img2Points.at(rightEyebrowCompareOrder[i]).afterChange(a,b,c,d));
        //            // load img2 and img1 part points
        //            img1PartPoints.push_back(img2Points.at(rightEyebrowCompareOrder[i]).afterChange(a,b,c,d));
        //            img2PartPoints.push_back(img2Points.at(rightEyebrowCompareOrder[i]));
        //        }

        //        distance = mouthDistance*mouthWeighting + rightEyeDistance*rightEyeWeighting + LeftEyebrowDistance*leftEyeBrowWeighting + leftEyeDistance*leftEyeWeighting;
        distanceIntersection();
        //        double seuil = 100;
        std::cout << "similarity : " << similarity << std::endl;
        return similarity;
    }
    else
    {
        std::cout << "No face found : " << QDateTime::currentDateTime().toString().toStdString() << std::endl;
        return 0.00;
    }


}

int* ExpressionRecogniser::getContour(cv::Mat_<unsigned char> img)
{
    std::vector<EmoPoint> points = this->getFacePoints(img);
    if(!foundface)
    {
        return &foundface;
    }
    else
    {
        int x1 = points.at(1).getY();
        int y1 = points.at(14).getX();
        int x2 = points.at(11).getY();
        int y2 = points.at(6).getX();

        return new int[5]{foundface,x1,y1, x2, y2};
}
}
