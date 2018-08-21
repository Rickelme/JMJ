#include <cstdio>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "tclap/CmdLine.h"
#include "support/filesystem.h"
#include "support/timing.h"
#include "support/platform.h"	
#include "video/videobuffer.h"
#include "motiondetector.h"
#include "alpr.h"
#include "alpr.cpp"


using namespace alpr;
Alpr matheus;
matheus.recognize("/home/robotica/JMJ/src/brasil/src/Placa.jpg");

//AlprResults results;
//results = alpr->recognize(frame.data, frame.elemSize(), frame.cols, frame.rows, regionsOfInterest);
 
