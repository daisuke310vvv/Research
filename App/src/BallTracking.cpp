#include "BallTracking.h"

void ballTrackingByHoughTransform(IplImage inputImg){

	//opencv2.4.9
	//std::vector<cv::Vec3f>circles;

	int i;
	float *p;
	IplImage *src_img = 0, *src_img_gray = 0;
	CvMemStorage *storage;
	CvSeq *circles = 0;

	IplImage *inputImg_gray = cvLoadImage(inputImg,CV_LOAD_IMAGE_GRAYSCALE);

	// (2)ハフ変換のための前処理（画像の平滑化を行なわないと誤検出が発生しやすい）
	cvSmooth (inputImg_gray,inputImg_gray, CV_GAUSSIAN, 11, 11, 0, 0);
	storage = cvCreateMemStorage (0);

	// (3)ハフ変換による円の検出と検出した円の描画
	circles = cvHoughCircles (
			inputImg_gray,
			storage,
			CV_HOUGH_GRADIENT,
			1,
			30,
			100,
			10,
			10,
			30
			);

	//circles.size()個の数で配列を生成
	//この配列に検出した数分、ボールの構造体を格納
	ball *balls = (ball*)malloc(sizeof(ball) * circles->total);


	for (i = 0; i < circles->total; i++) {

		p = (float *) cvGetSeqElem (circles, i);

		ball b;

		//中心
		cv::Point center(cvRound(p[0]),cvRound(p[1]));
		b.center.x = center.x;
		b.center.y = center.y;

		//半径
		b.radius = cvRound(p[2]);

		//原点
		b.origin.x = b.center.x - b.radius;
		b.origin.y = b.center.y - b.radius;

		//サイズ
		b.size.width = b.radius * 2;
		b.size.height = b.radius * 2;

		balls[i] = b;

	}

	/* opencv2.4.9
	   cv::HoughCircles(inputImg,					// image		- 8Bit Gray Scale Image.
	   circles,			// circles		- 検出された円を出力するベクトル(x,y,radius)
	   CV_HOUGH_GRADIENT,	// method		- 検出手法
	   1,					// dp			- 画像分解能に対する投票分解能の比率の逆数 
	   30,					// minDist		- 検出される円の中心同士の最小距離
	   100,				// param1		- Canny()エッジ検出での大きい方の閾値
	   10,					// param2		- 円の中心を検出する再の投票数の閾値.より多くの投票を獲得した円が最初に出力される
	   10,					// minRadius	- 円の半径の最小値
	   30					// maxRadius	- 円の半径の最大値
	   );
	   */

	/*
	 * TODO:
	 * ハフ変換の結果に対してボールの色情報検索
	 * */


	/*
	for(size_t i = 0;i<circles.size();++i){

		ball b;

		//中心
		cv::Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
		b.center.x = center.x;
		b.center.y = center.y;

		//半径
		b.radius = cvRound(circles[i][2]);

		//原点
		b.origin.x = b.center.x - b.radius;
		b.origin.y = b.center.y - b.radius;

		//サイズ
		b.size.width = b.radius * 2;
		b.size.height = b.radius * 2;

		balls[i] = b;
	}
	*/

}
