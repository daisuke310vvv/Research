//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

/* --------------------------------------------------------------- */
// 構造体
/* --------------------------------------------------------------- */
struct Origin{
	int x;
	int y;
};

 struct Size{
	int width;
	int height;
};

typedef struct ball{
	int radius;		//半径
	cv::Point center;		//ボールの中心座標
	Origin origin;	//ボールの左上座標
	Size size;		//ボールの横幅、縦幅
}ball;

/* --------------------------------------------------------------- */

/* --------------------------------------------------------------- */
// ハフ変換によるボール検出
/* --------------------------------------------------------------- */
// @param inputImg 入力画像(グレイ画像)
void ballTrackingByHoughTransform(cv::Mat inputImg);
/* --------------------------------------------------------------- */


