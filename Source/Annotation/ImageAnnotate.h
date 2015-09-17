#pragma once

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>
#include "Frame.h"

using namespace std;
using namespace cv;

class ImageAnnotate
{
private:
	ImageAnnotate(void);
	~ImageAnnotate(void);

public:
	static void annotate();
	static void on_mouse(int event,int x,int y,int flags,void *ustc);
	static int nextFrame();
	static void draw();

	static Mat image_display;  //display image
	static Mat image_tmp;	//temp display image
	static Frame frame;		//current frame
	static string filePath;	//image file path
	static string title;	//window title
	static int total_num;	//totle image numbers
	static int current_num;		//current image number
};
