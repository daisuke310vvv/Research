#include<string>
#include<list>
#include <omp.h>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define MAX_STR 100

using namespace std;


class Image {

  private:
    unsigned char *pixels;
    int *iPixels;
    double *dPixels;
    char header[MAX_STR];
    int width;
    int height;
    int maxLuminance;

  public:
    Image(char *fileName);
Image();
    Image(int width, int height,int flag);	// 0で初期化された画像データが生成される
 ~Image();
   
    void normalize();		// 正規化
    void grayscaling();

    void test(char *header, int width, int height, int maxLuminace);

    unsigned char *getPixels();	//画像データを格納している配列の先頭アドレスを返す
    int *getiPixels();		// ガウス平均画像・ガウス分散画像を格納する配列の先頭アドレスを返す
    double *getdPixels();
    char *getHeader();		// 扱う画像のヘッダーを格納している配列の先頭アドレスを返す
    int getWidth();		// 扱う画像の幅。上に同じ 
    int getHeight();		// 扱う画像の高さ。上に同じ
    int getMaxLuminance();	// 扱う画像の最高輝度。上に同じ
    void skip(FILE * fp);

};


