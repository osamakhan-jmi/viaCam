#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<Windows.h>
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

using namespace cv;
using namespace std;

POINT getpoint(Point p)
{
	POINT P;
	int x, y;
	x = p.x / 0.412;
	y = p.y / 1.12;
	P.x = x;
	P.y = y;
	return P;
}

int main()
{
    VideoCapture cam(0);
    int r, c, rc = 0, cc = 0;
	Point p;
	POINT P;
	cvNamedWindow("cam",CV_WINDOW_NORMAL);
    while (true)
	{
		Mat frame;
		cam.read(frame);
		cvtColor(frame, frame, CV_BGR2GRAY);
		erode(frame,frame,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		dilate(frame, frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		for (r = 0; r < frame.rows; r++)
		{
			for (c = 0; c < frame.cols; c++)
			{
				if (frame.at<uchar>(r, c) > 250 && frame.at<uchar>(r, c) < 255)
				{
					frame.at<uchar>(r, c) = 255;
					rc = r;
					cc = c;
				}
				else
					frame.at<uchar>(r, c) = 0;
			}
		}
		p.x = rc;
		p.y = cc;
		P = getpoint(p);
		//cout << "P.x = " << P.x << "P.y = " << P.y << '\n';
		SetCursorPos(P.x, P.y);
		imshow("cam",frame);
		if (waitKey(30) == 27)
			return -1;
		frame.release();
	}
	waitKey(0);
	cvDestroyAllWindows();
	cam.release();
	return 0;
}