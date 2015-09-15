#pragma once

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

class ImageAnnotate
{
private:
	ImageAnnotate(void);
	~ImageAnnotate(void);

public:
	static void annotate();
	static void on_mouse(int event,int x,int y,int flags,void *ustc);
	static string getFileName(string filePath,int count);
	static int nextFrame();
	static void save();
	static void load();
	static void draw();
	static void split(const string& src, const string& separator, vector<string>& dest);

	static Mat src;
	static Mat dst;
	static Mat tmp;
	static string filePath;
	static string title;
	static int count;
	static int num;
	static vector<Rect> body; 
};

