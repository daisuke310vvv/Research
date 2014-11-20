#include<fstream>
#include"Images.h"
#include<string>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define PI 3.1415926

using namespace std;

/* コンストラクタ */
Images::Images(string filePath, int numOfImage,int startNum) {
	//cout << "Images::Images() start" << endl;
	this->filePath = filePath.c_str();
	this->numOfImage = numOfImage;
	this->startNum = startNum;

	/* オフライン処理 */
	setting();
	
	loadImages();
	gaussianAverageImage = new Image(imageWidth, imageHeight,0);
	gaussianDistributeImage = new Image(imageWidth, imageHeight,0);
	gaussianHsqrtImage  = new Image(imageWidth ,imageHeight,1);
	
	gaussianAveragePixels = gaussianAverageImage->getiPixels();
	gaussianDistributePixels = gaussianDistributeImage->getiPixels();
	gaussianHsqrtPixels  = gaussianHsqrtImage->getdPixels();
	execGaussian();
	
	//char str[32];
	//sprintf(str, "%s%d.bmp", this->filePath, 26350);
	//cout << str << endl;
	//image = new Image(str);
	//online(image);
	
}

/* デストラクタ 
 * Imageリストのメモリ解放
 * */
Images::~Images() {
	//cout << "Images::~Images() start" << endl;
	//delete[]( imageHeader );
	imageHeader = NULL;

	list<Image*>::iterator it = images.begin();
	for (it = images.begin(); it != images.end(); it++) {
		delete (*it);
		*it = NULL;
	}

	delete[] (gaussianAveragePixels);
	gaussianAveragePixels = NULL;
	delete[] (gaussianDistributePixels);
	gaussianDistributePixels = NULL;
	delete[] (gaussianHsqrtPixels);
	gaussianHsqrtPixels = NULL;

	delete (image);
	image = NULL;
}

void Images::setting() {
	char str[32]; /* 数は適当 */

	sprintf(str, "%s0.bmp", filePath);
	//cout << str << endl;

	Image image(str);

	this->imageHeader = image.getHeader();
	this->imageWidth = image.getWidth();
	this->imageHeight = image.getHeight();
	this->imageMaxLuminance = image.getMaxLuminance();

	//cout << "Images::setting() exit" << endl;
}

/* 指定枚数分の画像を取り込む */
void Images::loadImages() {

	for (int i = startNum; i < startNum + numOfImage; i++) {
		char str[32];/* 数は適当 */

		sprintf(str, "%s%d.bmp", filePath, i);
		//cout << str << endl;

		Image* image = new Image(str);
		images.push_back(image);
		//if(i>30) images.pop_front();
	}
	//cout << "Images::loadImages() exit" << endl;
}

void Images::execGaussian() {
	gaussianAverage();
	gaussianDistribute();
	gaussianHsqrt();
	//cout << "execGaussian exit" << endl;
}

/* ガウス平均処理 */
void Images::gaussianAverage() {
	
	list<Image*>::iterator it;
	for (int i = 0; i < 3 * imageWidth * imageHeight; i++) {
	it = images.begin();
		while (it != images.end()) {
		/* 並列計算できそう */
			unsigned char* tmp = (*it)->getPixels();
		
			gaussianAveragePixels[i] += (int) tmp[i];
			it++;
		}
		gaussianAveragePixels[i] /= numOfImage;
	}
}
	


/* ガウス平均SEIKiKAKYORI処理 */
void Images::gaussianHsqrt() {
	double value=0.0;
        list<Image*>::iterator it;
	for (int i = 0; i < imageWidth * imageHeight; i++) {
	it  = images.begin();
        	while (it != images.end()) {
		        /* 並列計算できそう */
			  unsigned char* tmp = (*it)->getPixels();
                
			   value = tmp[i*3]* tmp[i*3]+tmp[i*3+1]*tmp[i*3+1]+ tmp[i*3+2]*tmp[i*3+2];
                        gaussianHsqrtPixels[i] +=  sqrt(value);
			   it++;	   
       		}
		
		gaussianHsqrtPixels[i] /= (double)numOfImage;
		 
        }
}

/* ガウス分散処理 */
void Images::gaussianDistribute() {
        
	list<Image*>::iterator it;
	for (int i = 0; i < 3 * imageWidth * imageHeight; i ++) {

		it = images.begin();
		while (it != images.end()) {
			/* 並列計算できそう */
			unsigned char* tmp = (*it)->getPixels();
			int tmp2;
			tmp2 = (int) tmp[i] - gaussianAveragePixels[i];
			gaussianDistributePixels[i] += tmp2 * tmp2;
			
			it++;
		}
		gaussianDistributePixels[i] = gaussianDistributePixels[i] / numOfImage;
		if(i==0)cout << "gaussianDistributePixels[i]" << gaussianDistributePixels[i] <<endl;
	}

}

void Images::online(Image* image) {

	printf("node online start\n");
	int color;
	double angle,hfsqrt;

	unsigned char* pixels = image->getPixels();

	for (int i = 0; i < imageWidth * imageHeight; i ++) {

		if (gaussianDistributePixels[i*3] == 0)
			gaussianDistributePixels[i*3] = 1;
		if (gaussianDistributePixels[i*3 + 1] == 0)
			gaussianDistributePixels[i*3 + 1] = 1;
		if (gaussianDistributePixels[i*3 + 2] == 0)
			gaussianDistributePixels[i*3 + 2] = 1;

		double hsqrt = sqrt(double(pixels[i*3]*pixels[i*3]+pixels[i*3+1]*pixels[i*3+1]+pixels[i*3+2]*pixels[i*3+2]));
		double seki = pixels[i*3]*gaussianAveragePixels[i*3]+pixels[i*3+1]*gaussianAveragePixels[i*3+1]+pixels[i*3+2]*gaussianAveragePixels[i*3+2];
 
		double tt = abs(gaussianHsqrtPixels[i]-hsqrt);
		if(i==0)cout << "gaussianAveragePixels[i*3]" << gaussianAveragePixels[i*3] <<endl;

		if(tt<30){

			color = 0;

			if(gaussianAveragePixels[i*3] - pixels[i*3] > 60){
			color++;
			} 
			if(gaussianAveragePixels[i*3+1] - pixels[i*3+1] > 60){
			color++;
			}
			if(gaussianAveragePixels[i*3+2] - pixels[i*3+2] > 60){
			color++;
			}
			if(color == 1){
			angle = 0.0;
			}
			else{
			angle = 1.0;
			}
		}
		else{
			if(hsqrt < 100){
			angle = 0.0;			
			}
			else if(gaussianHsqrtPixels[i] < 150 && hsqrt > 180){
			angle = 0.0;			
			}
			else{
			hfsqrt = gaussianHsqrtPixels[i]*hsqrt;
			angle = seki/hfsqrt;			
			
				if(angle > 1.0)
				angle = 1.0;
			}
		}

		

		if(angle<=0.795){
			pixels[i*3]= 255;
			pixels[i*3+1]= 255;
			pixels[i*3+2]= 255;

		}
		else{
			//updateGA(i);

			pixels[i*3]= 0;
			pixels[i*3+1]= 0;
			pixels[i*3+2]= 0;
		}
		//Renew Average
		
		/* TODO 更新 */
		//list<Image*>::iterator it = images.begin();
		//unsigned char* oldtmp = (*it)->getPixels();
		/* 古いのから上書きしてガウス平均を生成しなおす？ */
		//gaussianAveragePixels[i] = ( gaussianAveragePixels[i] * numOfImage +   ) / numOfImage;
	}

	test(image);
	printf("test image output done\n");

}

void Images::online(unsigned char* pixels) {
	printf("node online start\n");

	for (int i = 0; i < imageWidth * imageHeight; i ++) {
		bgSub(pixels, i);
		updateGA(i);
	}

	test(image);
	printf("test image output done\n");

}



bool Images::updateGA(int i){

	/* TODO 更新 */
		list<Image*>::iterator it = images.begin();
		unsigned char* oldtmp = (*it)->getPixels();

		list<Image*>::iterator newit = images.end();
		unsigned char* newtmp = (*newit)->getPixels();

		delete *it;
		images.pop_front();

		/* 古いのから上書きしてガウス平均を生成しなおす？ */
		//for (int i = 0; i < imageWidth * imageHeight; i ++) {
		gaussianAveragePixels[i*3] = ( gaussianAveragePixels[i*3] * numOfImage - oldtmp[i*3] +  newtmp[i*3] ) / numOfImage;
		gaussianAveragePixels[i*3+1] = ( gaussianAveragePixels[i*3+1] * numOfImage  - oldtmp[i*3+1] + newtmp[i*3+1]  ) / numOfImage;
		gaussianAveragePixels[i*3+2] = ( gaussianAveragePixels[i*3+2] * numOfImage  - oldtmp[i*3+2]+ newtmp[i*3+2] ) / numOfImage;
		//}


	return true;
}


bool Images::bgSub(unsigned char *pixels, int i){
	int color;
	double angle,hfsqrt;

		if (gaussianDistributePixels[i*3] == 0)
			gaussianDistributePixels[i*3] = 1;
		if (gaussianDistributePixels[i*3 + 1] == 0)
			gaussianDistributePixels[i*3 + 1] = 1;
		if (gaussianDistributePixels[i*3 + 2] == 0)
			gaussianDistributePixels[i*3 + 2] = 1;

		double hsqrt = sqrt(double(pixels[i*3]*pixels[i*3]+pixels[i*3+1]*pixels[i*3+1]+pixels[i*3+2]*pixels[i*3+2]));
		double seki = pixels[i*3]*gaussianAveragePixels[i*3]+pixels[i*3+1]*gaussianAveragePixels[i*3+1]+pixels[i*3+2]*gaussianAveragePixels[i*3+2];

		double tt = abs(gaussianHsqrtPixels[i]-hsqrt);

		if(tt<30){

			color = 0;

			if(gaussianAveragePixels[i*3] - pixels[i*3] > 60){
			color++;
			}
			if(gaussianAveragePixels[i*3+1] - pixels[i*3+1] > 60){
			color++;
			}
			if(gaussianAveragePixels[i*3+2] - pixels[i*3+2] > 60){
			color++;
			}
			if(color == 1){
			angle = 0.0;
			}
			else{
			angle = 1.0;
			}
		}
		else{
			if(hsqrt < 100){
			angle = 0.0;
			}
			else if(gaussianHsqrtPixels[i] < 150 && hsqrt > 180){
			angle = 0.0;
			}
			else{
			hfsqrt = gaussianHsqrtPixels[i]*hsqrt;
			angle = seki/hfsqrt;

				if(angle > 1.0)
				angle = 1.0;
			}
		}

		if(angle<=0.995){
			pixels[i*3]= 255;
			pixels[i*3+1]= 255;
			pixels[i*3+2]= 255;

		}
		else{

			pixels[i*3]= 0;
			pixels[i*3+1]= 0;
			pixels[i*3+2]= 0;
		}
		return true;

}





void Images::test(Image* image) {
	FILE *fp;
	

	if ((fp = fopen("online.ppm", "w")) == NULL) {
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	//cout << imageHeader << endl;
	//cout << imageWidth << " " << imageHeight << endl;
	//cout << imageMaxLuminance << endl;

	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", imageWidth, imageHeight);
	fprintf(fp, "%d\n", imageMaxLuminance);

	unsigned char* tmp = image->getPixels();
	fwrite(tmp, sizeof(char), 3 * imageWidth * imageHeight, fp);
	
	fclose(fp);

}

Image* Images::getimage() {
	return image;
}

