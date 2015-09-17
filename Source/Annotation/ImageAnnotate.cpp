#include "ImageAnnotate.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <fstream>

Mat ImageAnnotate::image_display;
Mat ImageAnnotate::image_tmp;
string ImageAnnotate::filePath = "../../PETS2015/ARENA/A1_ARENA-Tg_ENV_RGB_3/";
int ImageAnnotate::current_num=1;
int ImageAnnotate::total_num=295;
string ImageAnnotate::title = "Annotate";
Frame ImageAnnotate::frame;

ImageAnnotate::ImageAnnotate(void)
{

}

int ImageAnnotate::nextFrame()
{
	if(current_num <= total_num)
	{
		char ch[20];
		snprintf(ch,10,"%05d.jpg",current_num);
		string imageFileName(ch);
		snprintf(ch,10,"%05d.txt",current_num);
		string bodyFilename(ch);
		cout<<filePath+imageFileName<<endl;
		frame = Frame(filePath, imageFileName, bodyFilename);
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
		image_tmp = image_display.clone();
/*		sprintf_s(temp,"image%d(%d,%d)",count,x,y);*/
		cur = Point(x,y);
/*		putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));*/
		imshow(title,image_tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		image_tmp = image_display.clone();
/*		sprintf_s(temp,"image%d(%d,%d)",count,x,y);*/
		cur = Point(x,y);
/*		putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));*/
		rectangle(image_tmp,pre,cur,Scalar(255,0,0),1,8,0);
		imshow(title,image_tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		cur = Point(x,y);
		if(cur != pre)
		{
			Rect rect = Rect(pre,cur);
			frame.addBody(rect);
			rectangle(image_display,pre,cur,Scalar(255,0,0),1,8,0);
			image_tmp = image_display.clone();
// 			sprintf_s(temp,"image%d(%d,%d)",count,x,y);
// 			putText(tmp,temp,Point(660,40),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
			imshow(title,image_display);
		}
	}
	else if(event == CV_EVENT_RBUTTONDOWN)
	{
		image_display = frame.image().clone();
		frame.clearBody();
		image_tmp = image_display.clone();
		imshow(title,image_tmp);
	}
}

void ImageAnnotate::draw()
{
	vector<Rect> body = frame.getBody();
	for(string::size_type i = 0; i < body.size(); ++i)
	{
		rectangle(image_display,body.at(i),Scalar(255,0,0),1,8,0);
	}
}

void ImageAnnotate::annotate()
{
	namedWindow(title);
	setMouseCallback(title,on_mouse);
	while( nextFrame() )
	{
		image_display = frame.image().clone();
		draw();
		imshow(title,image_display);
		waitKey(0);
		frame.save();
		++current_num;
	}
}

ImageAnnotate::~ImageAnnotate(void)
{
}
