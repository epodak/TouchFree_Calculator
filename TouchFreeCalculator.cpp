#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#include <string>
#include <sstream>
#include <windows.h>  // for Sleep();
#include <ctime>  // time(&timev)  icin
#include <cstring>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <AR/gsub.h>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
#include "TouchFreeCalculator.h"

using namespace std;

TouchFreeCalculator::TouchFreeCalculator() 
{
	//buttonRect = new RectangularButtons();
	//buttonRect = new CircularButtons();
	mp = MarkerPoint::getSingleMarkerPoint();


}

TouchFreeCalculator::~TouchFreeCalculator()
{
}

void TouchFreeCalculator::startCalculator(){
	// kamerayi acmak icin dosya adresi
	char *cparam_name = "Data/camera_para.dat";
	char *vconf = "";
	char *patt_name = "Data/patt.hiro";
	bool choiceScreen = true;
	video = cv::VideoCapture(0);  // kameradan görüntü alirken
	int frame_width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// setup Camera (Kameranin markeri tanimasi icin)
	arParamLoad(cparam_name, 1, &gARTCparam);
	arParamChangeSize(&gARTCparam, 640, 480, &gARTCparam);
	arInitCparam(&gARTCparam);

	// Load marker(s).
	if (!mp->setupMarker(patt_name)) {
		fprintf(stderr, "main(): Unable to set up AR markerrr.\n");
		//exit(-1);
	}

	//rec->setCorners();
	char key = 0;
	int time = 1;
	while (choiceScreen){
		video.read(frame);

		if (!frame.empty()){
			flip(frame, frame, 1);
			cv::Point markerPosition = mp->positionOfMarker(frame);
			putText(frame, "Choose your design..", cv::Point(50, 150), cv::FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(255, 255, 0), 3);
			rectangle(frame, Point(200, 200), Point(300, 300), Scalar(255,0,0), 3, 8, 0);
			circle(frame, Point(400, 250), 50, Scalar(0, 0, 255), 3, 8, 0);
			int choice = chooseType(markerPosition);
			if (choice == 1 || choice == 2)
			{
				choiceScreen = false;
				timeCounter = 0;
				
				keyTurn = -1;
				if (choice == 1){
					buttonRect = new RectangularButtons();
					buttonRect->drawSettings();
					rect = dynamic_cast<RectangularButtons*>(buttonRect);
				}
				else if (choice == 2){
					buttonRect = new CircularButtons();
					buttonRect->drawSettings();
					circ = dynamic_cast<CircularButtons*>(buttonRect);

				}

			}
			// kamera goruntusunu pencerede goster
			imshow("TouchFree Typing", frame);
		}
		cv::waitKey(20);


	}

	while (key != 'q'){
		video.read(frame);
		
		if (!frame.empty()){
			flip(frame, frame, 1);
			cv::Point markerPosition = mp->positionOfMarker(frame);
			
			//Point markerPosition = findMarkers(frame);
			//drawPoint(markerPosition.x, markerPosition.y);
			//cout << "\t" << returnPosition(markerPosition.x, markerPosition.y) << endl;
			//buttonRect->drawWindow(markerPosition);
			buttonRect->drawButtons(frame);
			buttonRect->drawNumbers(frame);
			drawWindow(markerPosition);
			// kamera goruntusunu pencerede goster
			imshow("TouchFree Typing", frame);
		}
		
		key = cv::waitKey(20);
	}
	MarkerPoint::resetMarker();
	delete buttonRect;
}

// ekrana arti isaretini cizmeye yarayan fonksiyon
void TouchFreeCalculator::drawPoint(int x, int y){
	//cv::circle(frames, cv::Point(x, y), 20, cv::Scalar(0, 255, 0), 2);
	if (x != -1 && y != -1){
		if (y - 25 > 0)
			cv::line(frame, cv::Point(x, y), cv::Point(x, y - 25), cv::Scalar(0, 255, 0), 2);
		else cv::line(frame, cv::Point(x, y), cv::Point(x, 0), cv::Scalar(0, 255, 0), 2);
		if (y + 25 < 480)
			cv::line(frame, cv::Point(x, y), cv::Point(x, y + 25), cv::Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(x, 480), cv::Scalar(0, 255, 0), 2);
		if (x - 25 > 0)
			line(frame, cv::Point(x, y), cv::Point(x - 25, y), cv::Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(0, y), cv::Scalar(0, 255, 0), 2);
		if (x + 25 < 640)
			line(frame, cv::Point(x, y), cv::Point(x + 25, y), cv::Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(640, y), cv::Scalar(0, 255, 0), 2);

		putText(frame, intToString(x) + "," + intToString(y), cv::Point(x, y + 30), 1, 1, cv::Scalar(0, 255, 0), 2);
	}
}

// numarayi stringe ceviren fonksiyon 
std::string TouchFreeCalculator::intToString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

// marker'in hangi numara ustunde oldugunu ve donduren fonkiyon
int TouchFreeCalculator::returnPosition(double x, double y){
	int counter = 1;
	for (int i = 1; i < 5; i++){
		for (int j = 1; j < 4; j++){
			if (x < 100 * j + 50 && x > 100 * j && y < 100 * i + 50 && y > 100 * i)
				return counter;
			else
				counter++;
		}
	}

	for (int i = 1; i < 5; i++){
			if (x < 100 * 4 + 50 && x > 100 * 4 && y < 100 * i + 50 && y > 100 * i)
				return counter;
			else
				counter++;
	}

	return -1;
}

int TouchFreeCalculator::chooseType(cv::Point& coordinate){

	int temp = -1;
	if (coordinate.x != -1 && coordinate.y != -1){
		if (coordinate.x < 300 && coordinate.x > 200 && coordinate.y < 300 && coordinate.y > 200)
			temp = 1;
		else if (coordinate.x < 450 && coordinate.x > 350 && coordinate.y < 300 && coordinate.y > 200)
			temp = 2;
		//cout << temp << endl;
		// eger temp 0'dan buyukse ve keyTurn onceden bir tusun ustunde bulunmussa timeCounter artilir
		if (temp > 0 && temp == keyTurn){
			timeCounter++;
		}
		// eger temp 0'dan buykse ama keyTurn tempe esit degilse , ilk kez o numaraya giriyor demektir , timeCounter 1 yapilir ve keyTurn'e temp degeri atanir
		else if (temp > 0){
			keyTurn = temp;
			timeCounter = 1;
		}
		// bunlarin hicbiri olmamissa timeCounter ve keyTurn default degerlerine dondurulur
		else{
			keyTurn = -1;
			timeCounter = 0;
		}

		// dairesel progress bar ciz
		//drawProgressBar(temp);
		if (temp != -1){
			if (temp == 1) {
				progress.drawProgressBar(frame, Point(250, 250), Size(50, 50), timeCounter);
			}
			else if (temp == 2)
			{
				progress.drawProgressBar(frame, Point(400, 250), Size(50, 50), timeCounter);
			}
		}

		// eger timeCounter degeri istenen miktara ulasmissa bu deger artik bir input olmus demektir

		// marker icin arti isaretini ciz
		if (temp == -1)
		{
			drawPoint(coordinate.x, coordinate.y);
		}
	}

	// marker bulunamamissa keyTurn ve timeCounter degerlerini default degerlerine getir
	else{
		keyTurn = -1;
		timeCounter = 0;
	}
	if (timeCounter >= TIME_COUNTER)
		return temp;
	else
		return -1;
}


// ekrana çizen fonksiyon.
void TouchFreeCalculator::drawWindow(cv::Point& coordinate){
	
	// secilen sayilari ekrana basar
	if (buttonRect->getButtonType() == 'C') {
		putText(frame, numbers, cv::Point(75, 51), 5, 3, NUMBER2_COLOR, 3);
	}
	else {
		putText(frame, numbers, cv::Point(105, 51), 5, 3, NUMBER2_COLOR, 3);
	}

	if (coordinate.x != -1 && coordinate.y != -1){
		int temp = returnPosition(coordinate.x, coordinate.y);
		//cout << temp << endl;
		// eger temp 0'dan buyukse ve keyTurn onceden bir tusun ustunde bulunmussa timeCounter artilir
		if (temp > 0 && temp == keyTurn){
			timeCounter++;
		}
		// eger temp 0'dan buykse ama keyTurn tempe esit degilse , ilk kez o numaraya giriyor demektir , timeCounter 1 yapilir ve keyTurn'e temp degeri atanir
		else if (temp > 0){
			keyTurn = temp;
			timeCounter = 1;
		}
		// bunlarin hicbiri olmamissa timeCounter ve keyTurn default degerlerine dondurulur
		else{
			keyTurn = -1;
			timeCounter = 0;
		}

		// dairesel progress bar ciz
		//drawProgressBar(temp);
		if (temp != -1){
			if (buttonRect->getButtonType() == 'C') {
				progress.drawProgressBar(frame, circ->getCentersOfButtons().at(temp - 1), Size(36, 36), timeCounter);
			}
			else
			{
				progress.drawProgressBar(frame, rect->getCentersOfButtons().at(temp - 1), Size(36, 36), timeCounter);
			}
		}


		// eger timeCounter degeri istenen miktara ulasmissa bu deger artik bir input olmus demektir
		if (timeCounter >= TIME_COUNTER){
			// eger bu deger 11'den kucuk ve 0'dan buyuk ise bu bir rakam demektir , 10'a gore mod alinir
			if (keyTurn < 10 && keyTurn>0){
				keyTurn = keyTurn % 10;
				printf("Deger %d\n", keyTurn);
				numbers = numbers + intToString(keyTurn);
			}
			// 10 ise iptal butonudur
			else if (keyTurn == 10){
				printf("RESET\n");
				num_color = true;
				numbers = "";
			}
			// 11 ise "0" butonudur
			else if (keyTurn == 11){
				printf("Deger 0\n");
				numbers = numbers + "0";
			}
			// 12 =
			else if (keyTurn == 12){
				printf("=\n");
				if (numbers[0] == '-'){
					string numbersZero = "0" + numbers;
					const char * c = numbersZero.c_str();
					cal.calculate(c);

				}
				else{
					const char * c = numbers.c_str();
					cal.calculate(c);
				}
				numbers = "" + intToString(cal.getResult());
			}// 13 +
			else if (keyTurn == 13){
				printf("+\n");
				numbers = numbers + "+";
				num_color = false;
			}// 14 -
			else if (keyTurn == 14){
				printf("-\n");
				numbers = numbers + "-";
				num_color = false;
			}
			// 15 *
			else if (keyTurn == 15){
				printf("*\n");
				numbers = numbers + "*";
				num_color = false;
			}
			// 16 /
			else if (keyTurn == 16){
				printf("/\n");
				numbers = numbers + "/";
				num_color = false;
			}
			// timeCounter ve keyTurn degerlerini default degerlerine getir
			timeCounter = 0;
			keyTurn = -1;
		}
		// marker icin arti isaretini ciz
		if (temp == -1)
		{
			drawPoint(coordinate.x, coordinate.y);
		}
	}

	// marker bulunamamissa keyTurn ve timeCounter degerlerini default degerlerine getir
	else{
		keyTurn = -1;
		timeCounter = 0;
	}
}



/*
Point TouchFreeCalculator::findMarkers(Mat frame){
	Mat  frameGray, edges;					// gerekli mat objeleri
	std::vector<std::vector<cv::Point> > contours;	// contour icin
	std::vector<cv::Vec4i> hierarchy;				// hierarchy icin
	namedWindow("edges", 1);
	int frameCounter = 0;
	char key = 0;									// donguden cikma sarti icin , q olmadikca cýk
	while (key != 'q'){
		cvtColor(frame, frameGray, CV_BGR2GRAY);	// gray kanalina cevir

		threshold(frameGray, frameGray, 100, 255, CV_THRESH_BINARY);		// threshold uygula
		imshow("THRESHOLD", frameGray);
		Canny(frameGray, edges, 100, 255, 3);								// canny edge uygula
		imshow("edges", edges);

		// contour elemanlarini bul
		findContours(edges, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));


		// bulunan contour elemanlarini dolas
		for (int i = 0; i < contours.size(); i++)
		{
			int save = i;
			int count = 0;
			vector<Point> approx;


			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

			// eger contour child sahibi ise marker ara , degilse arama
			if (hierarchy[i][3] == -1 && hierarchy[i][2] != -1 && approx.size() == 4 & fabs(contourArea(Mat(approx))) > 1000)
			{

				int child = hierarchy[i][2];
				// child sahibi oldukca diger child'a sicra ve sayac tut
				while (hierarchy[child][2] != -1){
					count++;
					child = hierarchy[child][2];
				}

				Moments mu = moments(contours[save], false);
				Point2f center = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
				circle(frame, center, 5, cv::Scalar(0, 0, 255), 2, 2);
				drawContours(frame, contours, save, cv::Scalar(255, 0, 0), 2, 8, hierarchy, 0, cv::Point());

				return center;
				frameCounter++;

				// bu sayac 8 ise dairelerin oldugu marker'lardan biridir

				i = save;

			}
		}
		

}
*/