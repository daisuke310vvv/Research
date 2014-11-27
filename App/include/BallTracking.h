#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>

/* --------------------------------------------------------------- */
// 構造体
/* --------------------------------------------------------------- */
struct origin{
	int x;
	int y;
};

struct size{
	int width;
	int height;
};

typedef struct ball{
	int radius;		//半径
	cv::Point center;		//ボールの中心座標
	origin origin;	//ボールの左上座標
	size size;		//ボールの横幅、縦幅
}ball;

/* --------------------------------------------------------------- */

/* --------------------------------------------------------------- */
// ハフ変換によるボール検出
/* --------------------------------------------------------------- */
// @param inputImg 入力画像(グレイ画像)
void ballTrackingByHoughTransform(cv::Mat inputImg);
/* --------------------------------------------------------------- */


