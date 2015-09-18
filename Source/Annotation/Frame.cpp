#include "Frame.h"
#include <fstream>
#include <iostream>

using std::fstream;

Frame::Frame(string str1, string str2, string str3):filePath(str1),imageFileName(str2), bodyFileName(str3)
{
    mat = imread(filePath+imageFileName);
    load();
}

Frame::Frame()
{

}

Frame::~Frame()
{

}

Mat Frame::image()
{
    return mat;
}

vector<Rect> Frame::getBody()
{
    return body;
}

void Frame::clearBody()
{
    body.shrink_to_fit();
}

string Frame::getFileName()
{
    return imageFileName;
}

string Frame::getFilePath()
{
    return filePath;
}

int Frame::addBody(Rect &rect)
{
    body.push_back(rect);
}

void Frame::split(const string& src, const string& separator, vector<string>& dest)
{
    string str = src;
    string substring;
    string::size_type start = 0, index;

    do
    {
        index = str.find_first_of(separator,start);
        if (index != string::npos)
        {
            substring = str.substr(start,index-start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == string::npos) return;
        }
    }while(index != string::npos);

    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
}

void Frame::load()
{
    fstream file;   //body rect file eg. 001.txt if image file eg. 001.jpg
    file.open(filePath+bodyFileName,ios::in);
    if( !file.is_open() )
    {
        file.open(filePath+bodyFileName, ios::out);
        file.close();
        file.open(filePath+bodyFileName, ios::in);
    }
    if( !file.is_open() )
    {
        cerr<<"human body point file failed to read"<<endl;
    }
    while(!file.eof())
    {
        string str;
        file>>str;
        if( !str.empty() )
        {
            Rect rect;
            vector<string> size;
            vector<string> pt;
            split(str,"-",size);
            string subStr;

            subStr = size.at(0);
            split(subStr,",",pt);
            rect.x = atoi( pt.at(0).c_str() );
            rect.y = atoi( pt.at(1).c_str() );

            subStr = size.at(1);
            pt.clear();
            split(subStr,",",pt);
            rect.height = atoi( pt.at(0).c_str() );
            rect.width = atoi( pt.at(1).c_str() );
            body.push_back(rect);
        }
    }
    file.close();
}

void Frame::save()
{
    fstream file;
    file.open(filePath+bodyFileName,ios::out);
    if( !file.is_open() )
        cerr<<"human body point file failed to write"<<endl;
    for(size_t i = 0; i < body.size(); ++i)
    {
        Rect rect = body.at(i);
        file<<rect.x<<","<<rect.y<<"-"<<rect.height<<","<<rect.width<<endl;
    }
    file.close();
}
