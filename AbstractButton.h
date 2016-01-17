#ifndef ABSTRACTBUTTON_HEADER
#define ABSTRACTBUTTON_HEADER
#include <string>
#include "opencv2/opencv.hpp"
using namespace cv;
class AbstractButton
{
protected:
	char buttonType;
public:
	char getButtonType();
	virtual void drawButtons(Mat &frame) = 0;
	virtual void drawNumbers(Mat &frame) = 0;
	virtual void drawSettings() = 0;
	AbstractButton();
	~AbstractButton();
};
#endif
