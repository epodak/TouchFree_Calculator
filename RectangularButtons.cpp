#include "RectangularButtons.h"

RectangularButtons::RectangularButtons() 
{
	buttonType = 'R';
}

void RectangularButtons::setCorners(){
	for (int i = 1; i < 5; i++){
		for (int j = 1; j < 4; j++){
			firstCornerOfButtons.push_back(Point(100 * j, 100 * i - 15));
			lastCornerOfButtons.push_back(Point(100 * j + 70, 100 * i + 70 - 15));

		}
	}

	for (int j = 1; j < 5; j++){
		firstCornerOfButtons.push_back(Point(100 * 4, 100 * j - 15));
		lastCornerOfButtons.push_back(Point(100 * 4 + 70, 100 * j + 70 - 15));

	}
}

void RectangularButtons::drawButtons(Mat &frame){
	// ust alan
	cv::rectangle(frame, cv::Point(100, 5), cv::Point(470, 60), BORDER_COLOR, 3, 8, 0);

	// ekrana numara karelerini vcizen dongu	
	for (int j = 0; j < firstCornerOfButtons.size(); j++){
		cv::rectangle(frame, firstCornerOfButtons.at(j), lastCornerOfButtons.at(j), BORDER_COLOR, 3, 8, 0);
	}
}

void RectangularButtons::drawNumbers(Mat &frames){
	// draw 1
	putText(frames, "1", cv::Point(116, 140), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 2
	putText(frames, "2", cv::Point(216, 140), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);	
	// draw 3
	putText(frames, "3", cv::Point(316, 140), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw +
	putText(frames, "+", cv::Point(416, 140), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 4
	putText(frames, "4", cv::Point(116, 240), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);	
	// draw 5
	putText(frames, "5", cv::Point(216, 240), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);	
	// draw 6
	putText(frames, "6", cv::Point(316, 240), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw -
	putText(frames, "-", cv::Point(416, 240), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 7
	putText(frames, "7", cv::Point(116, 340), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);	
	// draw 8
	putText(frames, "8", cv::Point(216, 340), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);	
	// draw 9
	putText(frames, "9", cv::Point(316, 340), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw X
	putText(frames, "*", cv::Point(416, 340), cv::FONT_HERSHEY_SIMPLEX, 2, NUMBER_COLOR, 3);
	// draw C
	putText(frames, "C", cv::Point(116, 440), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw 0
	putText(frames, "0", cv::Point(216, 440), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw =
	putText(frames, "=", cv::Point(310, 440), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
	// draw /
	putText(frames, "/", cv::Point(416, 440), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, NUMBER_COLOR, 3);
}

void RectangularButtons::drawSettings(){
	setCorners();
}

// numarayi stringe ceviren fonksiyon 
std::string RectangularButtons::intToString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::vector<Point> RectangularButtons::getCentersOfButtons() { 
	
	for (int i = 0; i < firstCornerOfButtons.size(); i++)
	{
		centersOfButtons.push_back(Point((firstCornerOfButtons[i].x + lastCornerOfButtons[i].x) / 2, (firstCornerOfButtons[i].y + lastCornerOfButtons[i].y) / 2));
	}
	return centersOfButtons;
}