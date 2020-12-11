#ifndef CREATEDATABASE_H
#define CREATEDATABASE_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <io.h>

using namespace cv;
using namespace std;

vector<string> getFileNames(const string& path) {
    vector<string> files;
    long long hFile = 0;
    struct _finddata_t fileinfo {};
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            files.emplace_back(fileinfo.name);
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    return files;
}

string int2str(int x) {

    if (x == 0) return "0";
    string res;
    while (x) {
        res.push_back('0' + x % 10);
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

Mat createDatabase(const string& trainPath) {

    auto fileNames = getFileNames(trainPath);
    int trainNumber = 0;
    for (const auto& x : fileNames) {
        if (x != "." and x != ".." and x != "Thumbs.db") {
            trainNumber++;
        }
    }

    string path;
    Mat T, img;
    for (int i = 1; i <= trainNumber; i++) {
        path = trainPath + '\\' + int2str(i) + ".jpg";
        img = imread(path, 0);
        img = img.reshape(0, img.rows * img.cols);
        if (i == 1) {
            T = img;
        }
        else {
            hconcat(T, img, T);
        }
    }
    return T;
}

#endif //CREATEDATABASE_H