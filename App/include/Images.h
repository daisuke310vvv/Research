#include<list>

#ifndef ONCE
#define ONCE
//２重インクルード防止
#include"Image.h"
#include<string>
#endif

using namespace std;


class Images{
  private:
    const char* filePath;
    int numOfImage;
    int startNum;
    char* imageHeader;
    int imageWidth, imageHeight;
    int imageMaxLuminance;
    list<Image*> images;

	Image* gaussianAverageImage;
	Image* gaussianDistributeImage;
	Image*gaussianHsqrtImage;
	int* gaussianAveragePixels;
	int* gaussianDistributePixels;
	double *gaussianHsqrtPixels;
	Image* image;


public:
	Images(string , int , int);
	~Images();
	void setting();
	void loadImages();
	void execGaussian();
	void gaussianAverage();
	void gaussianDistribute();
	void gaussianHsqrt();
	void online(Image* image);
	void online(unsigned char*);
	void test(Image* image);
	Image* getimage();
	bool updateGA(int );
	bool bgSub(unsigned char *, int);

};
