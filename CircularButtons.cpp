#include "CircularButtons.h"

CircularButtons::CircularButtons()
{
	buttonType = 'C';
}

void CircularButtons::setRadius(int r){
	radius = r;
}

void CircularButtons::setCenters(){
	for (int i = 1; i < 5; i++){
		for (int j = 1; j < 4; j++){
			centersOfButtons.push_back(cv::Point(100 * j + 25, 100 * i + 25));
		}
	}
	for (int j = 1; j < 5; j++){
		centersOfButtons.push_back(cv::Point(100 * 4 + 25, 100 * j + 25));
	}
}

void CircularButtons::drawButtons(Mat &frame){
	// ust alan
	cv::rectangle(frame, cv::Point(70, 5), cv::Point(470, 60), BORDER_COLOR, 3, 8, 0);
	// ekrana numara karelerini vcizen dongu	
	for (int j = 0; j < centersOfButtons.size(); j++){
		circle(frame, centersOfButtons.at(j), radius, BORDER_COLOR, 3, 8, 0);
	}
}

void CircularButtons::drawNumbers(Mat &frames){
	// draw 1
	putText(frames, "1", cv::Point(106, 145), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 2
	putText(frames, "2", cv::Point(206, 145), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 3
	putText(frames, "3", cv::Point(306, 145), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw +
	putText(frames, "+", cv::Point(400, 145), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 4
	putText(frames, "4", cv::Point(106, 245), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 5
	putText(frames, "5", cv::Point(206, 245), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 6
	putText(frames, "6", cv::Point(306, 245), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw -
	putText(frames, "-", cv::Point(400, 245), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 7
	putText(frames, "7", cv::Point(106, 345), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 8
	putText(frames, "8", cv::Point(206, 345), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 9
	putText(frames, "9", cv::Point(306, 345), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw X
	putText(frames, "*", cv::Point(406, 345), cv::FONT_HERSHEY_SIMPLEX, 2, NUMBER_COLOR, 3);
	// draw C
	putText(frames, "C", cv::Point(103, 445), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 0
	putText(frames, "0", cv::Point(206, 445), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw =
	putText(frames, "=", cv::Point(300, 445), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw /
	putText(frames, "/", cv::Point(406, 445), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
}

void CircularButtons::drawSettings(){
	setRadius(36);
	setCenters();
}