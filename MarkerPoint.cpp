#include "MarkerPoint.h"


MarkerPoint* MarkerPoint::singleMarker;

MarkerPoint::MarkerPoint()
{
}

MarkerPoint::~MarkerPoint()
{
}


MarkerPoint* MarkerPoint::getSingleMarkerPoint(){
	if (singleMarker == NULL){
		std::cout << "SINGLETON\n";
		singleMarker = new MarkerPoint();
	}
	return singleMarker;
}


int MarkerPoint::setupMarker(const char *patt_name)
{
	// Loading only 1 pattern in this example.
	if ((markerID = arLoadPatt(patt_name)) < 0) {
		fprintf(stderr, "setupMarker(): pattern load error !!\n");
		return (FALSE);
	}

	return (TRUE);
}



void MarkerPoint::resetMarker(){
	delete singleMarker;
	singleMarker = NULL;
}

cv::Point MarkerPoint::positionOfMarker(cv::Mat currentFrame){
	int markerNum, markerIndex;
	cv::Point markerPoint;
	ARMarkerInfo *marker_info;
	markerFrame = convertToBGRA(currentFrame);
	if (arDetectMarker(markerFrame, 100, &marker_info, &markerNum) < 0) {
		return cv::Point(-1, -1);
	}
	markerIndex = checkIfMarker(marker_info, markerNum);
	if (markerIndex != -1)
		markerPoint = cv::Point(marker_info[markerIndex].pos[0], marker_info[markerIndex].pos[1]);
	else
		markerPoint = cv::Point(-1, -1);
	return markerPoint;
}

int MarkerPoint::checkIfMarker(ARMarkerInfo *marker_info, int markerSize){
	int index = -1;
	for (int i = 0; i < markerSize; i++) {
		if (marker_info[i].id == markerID) {
			if (index == -1) index = i; // First marker detected.
			else if (marker_info[i].cf > marker_info[i].cf) index = i; // Higher confidence marker detected.
		}
	}
	return index;
}

uchar* MarkerPoint::convertToBGRA(cv::Mat currentFrame){
	cvtColor(currentFrame, bgraFrame, cv::COLOR_BGR2BGRA);
	return bgraFrame.data;
}
