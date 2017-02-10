#ifndef CAPTURE_H
#define CAPTURE_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include <fstream>
#include "tsukuba_def.h"

//SURF追加
#include "opencv2/xfeatures2d.hpp"
#include <stdio.h>
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
int camera_open(void);
int capture (robot_t *IH);
int capture2 (robot_t *IH);
int capture0 (char *save_point);
void featureTracking(Mat img_1, Mat img_2, vector<Point2f>& points1, vector<Point2f>& points2, vector<uchar>& status);
void SURFdesu(Mat img_1, vector<Point2f>& points1, vector<KeyPoint>& keypoints_1);
int sfm(char *save_point,robot_t *IH);
#endif
