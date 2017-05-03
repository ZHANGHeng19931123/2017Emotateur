#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "opencv/highgui.h"
#include "C:\\Users\\ACER\\Desktop\\semetre4\\couleur\\projet\\Stasm\\stasm4.1.0\\stasm\\stasm_lib.h"
#include "expressionrecogniser.h"

int main()
{
    static const char* path = "C:\\Users\\ACER\\Desktop\\kingguanzhang1.jpg";
    cv::Mat_<unsigned char> img(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE)); if (!img.data)
    {
        printf("Cannot load %s\n", path); exit(1);
    }

    static const char* path2 = "C:\\Users\\ACER\\Desktop\\lena.jpg";
    cv::Mat_<unsigned char> img2(cv::imread(path2, CV_LOAD_IMAGE_GRAYSCALE)); if (!img.data)
    {
        printf("Cannot load %s\n", path); exit(1);
    }

    ExpressionRecogniser er = ExpressionRecogniser("C:\\Users\\ACER\\Desktop\\semetre4\\couleur\\projet\\Stasm\\stasm4.1.0\\data");
//    std::vector<Point> points = er.getFacePoints(img);
//    for(unsigned int i = 0; i < points.size(); i++)
//    {
//        img(cvRound(points.at(i).getX()), cvRound(points.at(i).getY())) = 0;
//    }

//    int foundface;
//    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords

//    if  (!stasm_search_single(&foundface,  landmarks,
//                              (char*)img.data, img.cols, img.rows, path, "/home/heng/Documents/TSE/FISE2/Semestre 8/Projet Couleur/Stasm/stasm4.1.0/data"))
//    {
//        printf("Error in stasm_search_single: %s\n", stasm_lasterr()); exit(1);
//    }

//    if (!foundface)
//        printf("No face found in %s\n", path);
//    else
//    {
//        // draw the landmarks on the image as white dots
//        stasm_force_points_into_image(landmarks,  img.cols,  img.rows);
//        for (int i = 0; i < stasm_NLANDMARKS; i++)
//            img(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
//    }

   // cv::imshow("stasm minimal", img); cv::waitKey();

    printf("S = %f\n", er.getSimilarity(img, img2));
    return 0;
}
