// TouchFree Calculator
// ============================================================================
//	Includes
// ============================================================================

#include <stdio.h>
#include <stdlib.h>	// malloc(), free()
#include <string>
#include <sstream>
#include <windows.h>  // for Sleep();
#include <ctime>  // time(&timev)  icin
#include <cstring>
#ifdef __APPLE__
#  include <GLUT/glut.h>
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
#include "MarkerPoint.h"
#include "TouchFreeCalculator.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	TouchFreeCalculator calculate;

	calculate.startCalculator();

	return (0);
}