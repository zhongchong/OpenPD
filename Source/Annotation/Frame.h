#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

class Frame
{
public:
    Frame(string str1,string str2,string str3);
    Frame();
    virtual ~Frame();
    string getFileName();
    string getFilePath();
    Mat image();
    int addBody(Rect &rect);
    vector<Rect> getBody();
    void clearBody();
    void load();
    void save();

protected:
    Mat mat;    //Image File Vector OpenCV::Mat
    string filePath;    //Image File Path eg. /home/usr/001.jpg
    string imageFileName;    //Image File Name eg. 001.jpg
    string bodyFileName;    //body file name eg. 001.txt
    vector<Rect> body;  //Body Rect in Image
    void split(const string& src, const string& separator, vector<string>& dest);
};
