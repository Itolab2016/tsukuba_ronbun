//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include "vo_features.h"
#include "vo_features2.h"

#include <iterator>
#include <vector>
#include <algorithm>

//PCL関連
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
//
#include "tsukuba_def.h"
#include "tsukuba_tkk.h"
#include "navigation.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

  char file5[]=GPS;
  ofstream GPSscale(file5);
  char file6[]=T_F;
  ofstream imgT_F(file6); 
  char file7[]=GPSDATA;
  ofstream GPSdata(file7);
 
  ifstream ifs("/home/tomas/sasai/12011430/scale.txt");
  vector<float> scaledata;


int main()
{
  Mat img_1, img_2,point4D;
  Mat dest;
  char filename1[100];
  char filename2[100];
  char str[20];
  Mat Rt=cv::Mat::eye(3, 4, CV_64FC1);
  Mat R,t,E,Rvec;
  Mat R_f= cv::Mat::eye(3, 3, CV_64FC1);
  Mat t_f= cv::Mat::zeros(3, 1, CV_64FC1);
  Mat Meye = cv::Mat::eye(3, 4, CV_64FC1);
  Mat M0 = cv::Mat::eye(3, 4, CV_64FC1);
  Mat M1=cv::Mat::eye(3, 4, CV_64FC1);
  Mat descriptor1, descriptor2;
  Mat mask;
  int frameNo=0;
  int count=0;
  int x,y,z;
  float tfx,tfy,tfz;
  float scale,scale1;
  vector<Point3f> point3DW;
  vector<Point3f> pointme;
  robot_t robo;
//  open_TKK();//TKK使用時open
  scale1=0;
  int k=1;
  double ido1,ido2,keido1,keido2;
  float takasa=60;
  vectar point1,point2,point;

//内部パラメータ行列(usbカメラ)
  Mat K=(Mat_<double>(3,3,CV_64FC1) <<490.2152,0,295.0464,0,487.5284,221.9754,0,0,1);
//歪み係数
  Mat distortionCoefficient=(cv::Mat_<float>(4,1) <<0.12736,-0.20937,0.003467,-0.002242,0.008104);
//焦点距離（usbカメラ）
  double focal = 489;
//中心座標(usbカメラ)
  Point2d pp(295.0464, 221.9754);
  VideoCapture cap(0);
  cout<<"1"<<endl;
  if(!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
  {
    //読み込みに失敗したときの処理
    cout<<"読み込みエラー"<<endl;
    return -1;
  }



//------------------------------------------------------------------------------------------------


  while(1){



    Mat frame;
    cap >> frame;

    //カメラからキャプチャーしている特徴点を表示
    vector<KeyPoint> camkey;
    vector<Point2f> camp;
    SURFdesu(frame, camp, camkey);
    Mat img_keypoints;
    drawKeypoints( frame, camkey, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    imshow("Keypoints", img_keypoints );

    int key = waitKey(1);
    if(key == 48)//0ボタンが押されたとき 終了
    {
      break;
    }
    else if(key == 52)//4が押されたとき TKK参照
    {

	save_wp(&robo);
	ido1=robo.lat;
	keido1=robo.lon;

	point1 = blh2ecef(ido1, keido1, takasa);
	point2 = blh2ecef(ido2, keido2, takasa);
	point = ecef2enu(point1, point2);
	
	scale=sqrt(SQR(point.a[0])+SQR(point.a[1]));

	cout<<"scale="<<scale<<endl;
    }
    else if(key == 49)//1が押されたとき　1.4mで計算
    {
	cout<<"長直進"<<endl;
	scale=1.400;
    }
    else if(key == 50)//2が押されたとき　0mで計算
    {
	cout<<"カーブ"<<endl;
	scale=0;
    }
    else if(key == 51)//3が押されたとき　0.3mで計算
    {
	cout<<"短直進"<<endl;
	scale=0.300;
    }

    else if(key == 53)//5が押されたとき　txtデータから移動量読み込み
    {
	copy(istream_iterator<float>(ifs), istream_iterator<float>(), back_inserter(scaledata));
	cout<<"scaletxt"<<scaledata[count]<<endl;
	scale=scaledata[count];
    }


    else if(key == 13)//Enterが押されたとき　三次元復元開始
    {

	ido2=ido1;
	keido2=keido1;

	//scaleデータをtxt化
	sprintf(str,"%f",scale);
	GPSscale<<str<<endl;

	//緯度経度データをtxt化
	sprintf(str,"%d\t%lf\t%lf\t%d",count,robo.lat,robo.lon,k);
	GPSdata<<str<<endl;
	
      //フレーム画像を保存する．
	cout<<"scale="<<scale<<endl;
	sprintf(str,"/home/tomas/sasai/data/surf%04d.png",count++);
        cv::imwrite(str, frame);
	cout<<count-1<<"回撮ったよ"<<endl;
	frameNo++;
	if(count>=2){/*ここに本文*///}


//読み込む画像　場所を指定

sprintf(filename1, "/home/tomas/sasai/12011430/surf%04d.png",count-2);
sprintf(filename2, "/home/tomas/sasai/12011430/surf%04d.png",count-1);



//比較用画像を読み込む 
Mat img_1_c = imread(filename1);
Mat img_2_c = imread(filename2);

// グレーにする
cvtColor(img_1_c, img_1, COLOR_BGR2GRAY);
cvtColor(img_2_c, img_2, COLOR_BGR2GRAY);
   
//特徴抽出準備
vector<KeyPoint> keypoints1;
vector<KeyPoint> keypoints2;
vector<KeyPoint> keypoints11;
vector<KeyPoint> keypoints22;
vector<Point2f> points1;
vector<Point2f> points2;


// 特徴点抽出
//SURF
SURFdesu(img_1, points1,keypoints1);
SURFdesu(img_2, points2,keypoints2);
//


cout<<"point1.size()="<<points1.size()<<endl;

// 特徴記述

//SURF
SURF::create()->compute(img_1, keypoints1, descriptor1);
SURF::create()->compute(img_2, keypoints2, descriptor2);
//

// マッチング (アルゴリズムにはBruteForceを使用)
Ptr<cv::DescriptorMatcher> knnmatcher = cv::DescriptorMatcher::create("BruteForce");
vector<cv::DMatch> match;
vector< vector<DMatch> > knnmatch12,knnmatch21;
knnmatcher->knnMatch(descriptor1, descriptor2, knnmatch12, 2); //上位2位までの点を探す
knnmatcher->knnMatch(descriptor2, descriptor1, knnmatch21, 2);
//knntest
    vector<DMatch> bestMatches12;
    vector<KeyPoint> bestkey112,bestkey212;
    vector<Point2f> p1;
    vector<Point2f> p2;
    vector<Point2f> p11;
    vector<Point2f> p22;


    float match12_par = .5f; //対応点のしきい値
    for (int i=0; i<knnmatch12.size(); i++){
      float dist1 = knnmatch12[i][0].distance;
      float dist2 = knnmatch12[i][1].distance;
      //良い点を残す（最も類似する点と次に類似する点の類似度から）
      if (dist1 <= dist2 * match12_par && dist1<=0.2f) {

        bestMatches12.push_back(knnmatch12[i][0]);
        bestkey112.push_back(keypoints1[knnmatch12[i][0].queryIdx]);
        bestkey212.push_back(keypoints2[knnmatch12[i][0].trainIdx]);
	p1.push_back(keypoints1[knnmatch12[i][0].queryIdx].pt);
	p2.push_back(keypoints2[knnmatch12[i][0].trainIdx].pt);
      }
    }
    cout << "BestMatch12=" << bestMatches12.size() << endl;
    cout<<endl;


//E行列からR,tを求める
vector<cv::DMatch> inlinerMatch;
  	E = findEssentialMat(p1, p2, focal, pp, RANSAC, 0.999, 1.0, mask);
  	recoverPose(E, p1, p2, R, t, focal, pp, mask);
  	Rodrigues( R, Rvec);

//mask処理
	
	for (size_t i = 0; i < mask.rows; ++i) {
	        uchar *inliner = mask.ptr<uchar>(i);
	        if (inliner[0] == 1) {
			inlinerMatch.push_back(bestMatches12[i]);
			p11.push_back(keypoints1[bestMatches12[i].queryIdx].pt);
			p22.push_back(keypoints2[bestMatches12[i].trainIdx].pt);
        	}
	}
KeyPoint::convert(p11,keypoints11);
KeyPoint::convert(p22,keypoints22);


drawMatches(img_1, keypoints1, img_2, keypoints2, inlinerMatch, dest);


cout<<"p11.size()="<<p11.size()<<endl;

//移動量計算
	//scale=sqrt(x*x+y*y+z*z);
	t=t*scale;

//Rt作
  	for(double m=0 ; m < 3; m++)
  		{
  		for(double b=0 ; b < 3; b++)
  			{
  			Rt.at<double>(m,b)=R.at<double>(m,b);
  			}
		}
	Rt.at<double>(0,3)=t.at<double>(0);
	Rt.at<double>(1,3)=t.at<double>(1);
	Rt.at<double>(2,3)=t.at<double>(2);
cout<<"Rt="<<Rt<<endl;


//透視射影行列作成
	M0=K*Meye;
  	M1=K*Rt;

	Mat point4Dh=(Mat_<float>(1,p11.size()*4,CV_32FC1));
	vector<Point3f> point3D;
	triangulatePoints(M0, M1, p11, p22, point4D);


//ch変更1to4		
	int n=0;
	for(int i=0;i<p11.size()/*match.size()*/;i++)
	{
		point4Dh.at<float>(0,n)=point4D.at<float>(0,i);
		point4Dh.at<float>(0,n+1)=point4D.at<float>(1,i);
		point4Dh.at<float>(0,n+2)=point4D.at<float>(2,i);
		point4Dh.at<float>(0,n+3)=point4D.at<float>(3,i);
		n=n+4;
	}

		
//
	convertPointsFromHomogeneous(point4Dh.reshape(4,1),point3D);

//遠い点群,地面の特徴点は除去

for(int i=0;point3D.size()>i;i++){
	if((point3D[i].z)<=-15 || point3D[i].z>=15)
	{
		point3D[i].x=0;
		point3D[i].y=0;
		point3D[i].z=0;
	}
}

cout<<"R="<<Rvec<<endl;
cout<<"t="<<t<<endl;

//原点からの座標に変換
for(int i=0;point3D.size()>i;i++){
	point3D[i].x=point3D[i].x-t_f.at<double>(0);
	point3D[i].y=point3D[i].y-t_f.at<double>(1);
	point3D[i].z=point3D[i].z-t_f.at<double>(2);	


	}

//総移動量計算

	t_f = t_f + R_f*t;
	R_f = R*R_f;


//座標情報を貯める

for(int i=0;point3D.size()>i;i++){
	point3DW.push_back(point3D[i]);
}

pointme.push_back(Point3f(t_f));
		
		cout<<"t_f="<<t_f<<endl<<endl;
		cout<<"R_f="<<R_f<<endl<<endl;
		cout<<"---------------------------------------------------------------------------"<<endl;
//

Mat img_keypoints11,img_keypoints22;	

drawKeypoints( img_1, keypoints11, img_keypoints11, Scalar(1,1,255), DrawMatchesFlags::DEFAULT );
drawKeypoints( img_2, keypoints22, img_keypoints22, Scalar(1,255,1), DrawMatchesFlags::DEFAULT );

namedWindow( "gray11", WINDOW_AUTOSIZE );
namedWindow( "gray22", WINDOW_AUTOSIZE );
namedWindow( "dest", WINDOW_AUTOSIZE );

//pcl関係
//点群データをpcdファイルに変換

			pcl::PointCloud<pcl::PointXYZRGB> xp;
			xp.width=point3DW.size();
			xp.height=3;
  			xp.points.resize(xp.width*xp.height);			
			int xpcount=0;
  			for(size_t i=0;i<point3DW.size();i++){
				xp.points[xpcount].x=point3DW[xpcount].x;
				xp.points[xpcount].y=-point3DW[xpcount].y;
				xp.points[xpcount].z=-point3DW[xpcount].z;
				xp.points[xpcount].r=255;	//点群に色を反映
				xpcount++;
  			}
			
			pcl::io::savePCDFileASCII ("/home/tomas/sasai/xp.pcd", xp);
		
    		imshow("gray22",img_keypoints22);
		
		imshow("gray11",img_keypoints11);
    		
		imshow("dest",dest);
	
	 	int key = waitKey(1);
	    	if(key == 115)//sボタンが押されたとき
	    		{
	      		imwrite("/home/tomas/sasai/test1.png", img_1);
			imwrite("/home/tomas/sasai/test2.png", img_2);
			imwrite("/home/tomas/sasai/test3.png", dest);
	    		}
	    	if(key == 13)//Enterボタンが押されたとき
	    		{
	      		break;
	    		}
}
}


return 0;
}
}
