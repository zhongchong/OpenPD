#include "ImageAnnotate.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <fstream>

Mat ImageAnnotate::src;
Mat ImageAnnotate::dst;
Mat ImageAnnotate::tmp;
string ImageAnnotate::filePath = "../../PETS2015/ARENA/A1_ARENA-Tg_ENV_RGB_3/";
int ImageAnnotate::count=1;
int ImageAnnotate::num=295;
string ImageAnnotate::title = "Annotate";
vector<Rect> ImageAnnotate::body;

ImageAnnotate::ImageAnnotate(void)
{

}

string ImageAnnotate::getFileName(string filePath,int count)
{
	if(count < 0)
		return filePath;
	char ch[200];
	sprintf(ch,"%05d.jpg",count);
	return filePath+ch;
}

int ImageAnnotate::nextFrame()
{
	if(count <= num)
	{
		string fileName = getFileName(filePath,count);
		cout<<fileName<<endl;
		src = imread(fileName);
		dst = src.clone();
		tmp = Mat();
		return 1;
	}
	return 0;
}

void ImageAnnotate::on_mouse(int event,int x,int y,int flags,void *ustc)
{
	static Point pre = Point(-1,-1);
	static Point cur = pre;

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pre = Point(x,y);
		cur = pre;
	}
	else if (event == CV_EVENT_MOUSEMOVE && !flags)
	{
		tmp = dst.clone();
/*		sprintf_s(temp,"image%d(%d,%d)",count,x,y);*/
		cur = Point(x,y);
/*		putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));*/
		imshow(title,tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		tmp = dst.clone();
/*		sprintf_s(temp,"image%d(%d,%d)",count,x,y);*/
		cur = Point(x,y);
/*		putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));*/
		rectangle(tmp,pre,cur,Scalar(255,0,0),1,8,0);
		imshow(title,tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		cur = Point(x,y);
		if(cur != pre)
		{
			Rect rect = Rect(pre,cur);
			body.push_back(rect);
			rectangle(dst,pre,cur,Scalar(255,0,0),1,8,0);
			tmp = dst.clone();
// 			sprintf_s(temp,"image%d(%d,%d)",count,x,y);
// 			putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
			imshow(title,tmp);
		}
	}
	else if(event == CV_EVENT_RBUTTONDOWN)
	{
		dst = src.clone();
		body.clear();
		vector<Rect> tmp2;
		body.swap(tmp2);
	}
}

void ImageAnnotate::save()
{
	fstream file;
	char ch[200];
	sprintf(ch,"%05d.txt",count);
	file.open(filePath+string(ch),ios::out);
	if( !file.is_open() )
		cerr<<"feature point file failed to write"<<endl;
	for(size_t i = 0; i < body.size(); ++i)
	{
		Rect rect = body.at(i);
		file<<rect.x<<","<<rect.y<<"-"<<rect.height<<","<<rect.width<<endl;
	}
	file.close();
}

void ImageAnnotate::split(const string& src, const string& separator, vector<string>& dest)
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

void ImageAnnotate::load()
{
	fstream file;
	char ch[200];
	sprintf(ch,"%05d.txt",count);
	file.open(filePath+ch,ios::in);
	if( !file.is_open() )
	{
		cerr<<"feature point file failed to read"<<endl;
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

void ImageAnnotate::draw()
{
	for(string::size_type i = 0; i < body.size(); ++i)
	{
		rectangle(dst,body.at(i),Scalar(255,0,0),1,8,0);
	}
}

void ImageAnnotate::annotate()
{
	namedWindow(title);
	setMouseCallback(title,on_mouse);
	while( nextFrame() )
	{
		vector<Rect> tmp1;
		body.swap(tmp1);
		load();
		draw();
		imshow(title,dst);
		waitKey(0);
		save();
		++count;
	}
}

ImageAnnotate::~ImageAnnotate(void)
{
}
