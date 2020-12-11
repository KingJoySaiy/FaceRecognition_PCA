#ifndef RECOGNITION_H
#define RECOGNITION_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include "CreateDatabase.h"

using namespace cv;
using namespace std;

string recognition(const string& testImage, tuple<Mat, Mat, Mat> data) {

    Mat M = get<0>(data), A = get<1>(data), eigenFaces = get<2>(data);
    Mat projectedImages, tmp;
    int trainNumber = eigenFaces.cols;
    for (int i = 0; i < trainNumber; i++) {
        tmp = eigenFaces.t() * A.col(i);
        if (i == 0) {
            projectedImages = tmp;
        }
        else {
            hconcat(projectedImages, tmp, projectedImages);
        }
    }

    Mat image = imread(testImage, 0);
    image = image.reshape(0, image.rows * image.cols);
    image.convertTo(tmp, CV_64F);
    Mat projectedTestImage = eigenFaces.t() * (tmp - M);

    double Min = 1e100, now;
    int minId = 1;
    for (int i = 0; i < trainNumber; i++) {
        now = fabs(norm(projectedTestImage - projectedImages.col(i)));
        if (now <= Min) {
            Min = now;
            minId = i + 1;
        }
    }
    return int2str(minId);
}

#endif	//RECOGNITION_H
