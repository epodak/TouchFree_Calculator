#include "CircularProgressBar.h"


CircularProgressBar::CircularProgressBar()
{
}



// ekrana arti isaretini cizmeye yarayan fonksiyon
void CircularProgressBar::drawObject(Mat &frames, int x, int y){
	//cv::circle(frames, cv::Point(x, y), 20, cv::Scalar(0, 255, 0), 2);
	if (y - 25>0)
		cv::line(frames, cv::Point(x, y), cv::Point(x, y - 25), cv::Scalar(0, 255, 0), 2);
	else cv::line(frames, cv::Point(x, y), cv::Point(x, 0), cv::Scalar(0, 255, 0), 2);
	if (y + 25<480)
		cv::line(frames, cv::Point(x, y), cv::Point(x, y + 25), cv::Scalar(0, 255, 0), 2);
	else line(frames, cv::Point(x, y), cv::Point(x, 480), cv::Scalar(0, 255, 0), 2);
	if (x - 25>0)
		line(frames, cv::Point(x, y), cv::Point(x - 25, y), cv::Scalar(0, 255, 0), 2);
	else line(frames, cv::Point(x, y), cv::Point(0, y), cv::Scalar(0, 255, 0), 2);
	if (x + 25<640)
		line(frames, cv::Point(x, y), cv::Point(x + 25, y), cv::Scalar(0, 255, 0), 2);
	else line(frames, cv::Point(x, y), cv::Point(640, y), cv::Scalar(0, 255, 0), 2);
}

/* secilen kutucuk cevresine cember cizen fonksiyon */
void CircularProgressBar::drawProgressBar(Mat frames, Point center, Size size, int timeCounter){
		// dairesel progress bar ciz
	cv::ellipse(frames, center, size, 0, -90, -90 + 180.0*(timeCounter / TIME_COUNTER), PROGRESSBAR_COLOR, 6, 8, 0);
	cv::ellipse(frames, center, size, 0, -90, -90 + -180.0*(timeCounter / TIME_COUNTER), PROGRESSBAR_COLOR, 6, 8, 0);
}
