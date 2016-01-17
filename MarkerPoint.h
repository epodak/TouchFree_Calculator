#ifndef MARKER_HEADER
#define MARKER_HEADER
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
class MarkerPoint
{
private:
	int markerID;
	cv::Mat bgraFrame;
	ARUint8 *markerFrame;
	int checkIfMarker(ARMarkerInfo *marker_info, int markerSize);
	uchar* convertToBGRA(cv::Mat currentFrame);
	MarkerPoint();
	static MarkerPoint* singleMarker;

public:
	static MarkerPoint* getSingleMarkerPoint();
	static void resetMarker();
	int setupMarker(const char *patt_name);
	cv::Point positionOfMarker(cv::Mat currentFrame);
	~MarkerPoint();
};
#endif

