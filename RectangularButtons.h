#ifndef RECTANGULARBUTTON_HEADER
#define RECTANGULARBUTTON_HEADER
#include "AbstractButton.h"
#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;
using namespace std;

#define NUMBER_COLOR			cv::Scalar(0, 0, 255)	// Sayilarin rengi
#define NUMBER2_COLOR			cv::Scalar(0, 200, 200)	// Secilen Sayilarin ekrandaki rengi
#define BORDER_COLOR			CV_RGB(120, 250, 120)	// cizgilerin rengi

class RectangularButtons : public AbstractButton
{
private:
	std::vector<Point> centersOfButtons;
	std::vector<Point> firstCornerOfButtons;
	std::vector<Point> lastCornerOfButtons;
public:
	void drawButtons(Mat &frame);
	void drawNumbers(Mat &frame);
	void drawSettings();
	std::vector<Point> getCentersOfButtons();
	void setCorners();
	std::string intToString(int number);
	RectangularButtons();
};
#endif

