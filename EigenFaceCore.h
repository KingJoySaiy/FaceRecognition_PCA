#ifndef EIGENFACECORE_H
#define EIGENFACECORE_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

tuple<Mat, Mat, Mat> EigenFaceCore(Mat T) {

    Mat M, A = Mat::zeros(Size(T.cols, T.rows), CV_64F);
    double tmp;
    for (int i = 0; i < T.rows; i++) {
        tmp = mean(T.row(i))[0];
        M.push_back(tmp);
        for (int j = 0; j < T.cols; j++) {
            A.at<double>(i, j) = double(T.at<uchar>(i, j)) - tmp;
        }
    }

    Mat D, V, eigenFaces;
    eigen(A.t() * A, D, V);

    for (int i = D.rows - 1; i >= 0; i--) {
        if (D.at<double>(i, 0) > 1) {
            if (eigenFaces.rows == 0) {
                eigenFaces = V.row(i).reshape(0, V.cols);
            }
            else {
                hconcat(eigenFaces, V.row(i).reshape(0, V.cols), eigenFaces);
            }
        }
    }
   
    eigenFaces = A * eigenFaces;
    return make_tuple(M, A, eigenFaces);
}

#endif	//EIGENFACECORE_H
