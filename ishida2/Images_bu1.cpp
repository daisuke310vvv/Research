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
Images::Images(string filePath, int numOfImage) {
	cout<<"Images start"<<endl;
	//cout << "Images::Images() start" << endl;
	this->filePath = filePath.c_str();
	this->numOfImage = numOfImage;

	/* オフライン処理 */
	setting();
	
	loadImages();
	gaussianAverageImage = new Image(imageWidth, imageHeight);
	
	gaussianHsqrtImage  = new double[imageWidth * imageHeight];
	
	gaussianDistributeImage = new Image(imageWidth, imageHeight);
	gaussianAveragePixels = gaussianAverageImage->getiPixels();
	gaussianDistributePixels = gaussianDistributeImage->getiPixels();
	cout<<"mem alloced"<<endl;
	//gaussianHsqrtPixels  = gaussianHsqrtImage->getiPi

	execGaussian();
	/******************/

	//clock_t start, end;
	/* オンライン処理 */
	//start = clock();

	char str[32];
	sprintf(str, "%s%d.bmp", this->filePath, numOfImage);
	//cout << str << endl;
	image = new Image(str);
	cout<<"node online start"<<endl;
	online(image);
	//end = clock();
	//printf( "online exec time: %f [s]\n",(double)(end - start) / CLOCKS_PER_SEC);
	//cout << "Images::Images() exit" << endl;
	//test(image);
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

	for (int i = 0; i < numOfImage; i++) {
		char str[32];/* 数は適当 */

		sprintf(str, "%s%d.bmp", filePath, i);
		//cout << str << endl;

		Image* image = new Image(str);
		images.push_back(image);
		if(i>30) images.pop_front();
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

	list<Image*>::iterator it = images.begin();
	while (it != images.end()) {
		/* 並列計算できそう */
		unsigned char* tmp = (*it)->getPixels();
		for (int i = 0; i < 3 * imageWidth * imageHeight; i++) {
			gaussianAveragePixels[i] += (int) tmp[i];
		}
		it++;
	}
	/* 並列計算できそう */
	for (int i = 0; i < 3 * imageWidth * imageHeight; i++) {
		gaussianAveragePixels[i] /= numOfImage;
	}
}


/* ガウス平均SEIKiKAKYORI処理 */
void Images::gaussianHsqrt() {
	printf("3 \n");
	double value=0.0;
        list<Image*>::iterator it = images.begin();
	printf("3.1 \n");
        while (it != images.end()) {
                /* 並列計算できそう */
		  printf("3.1.1 \n");
                unsigned char* tmp = (*it)->getPixels();
                for (int i = 0; i < imageWidth * imageHeight; i ++) {
			   printf("3.2 \n");
			   value = tmp[i]* tmp[i]+tmp[i*3+1]*tmp[i*3+1]+ tmp[i*3+2]*tmp[i*3+2];
                        gaussianHsqrtPixels[i] +=  sqrt(value);
			//printf("i = %d,it = %d\n",i,it);
			   
                }
               
        }
	printf("4 \n");
        /* 並列計算できそう */
        for (int i = 0; i <  imageWidth * imageHeight; i++) {
                gaussianHsqrtPixels[i] /= (double)numOfImage;
		 //printf("hsqrt = %f\n",gaussianHsqrtPixels[i]);
        }
}





/* ガウス分散処理 */
void Images::gaussianDistribute() {
        
	list<Image*>::iterator it;
	for (int i = 0; i < 3 * imageWidth * imageHeight; i += 3) {

		it = images.begin();
		while (it != images.end()) {
			/* 並列計算できそう */
			unsigned char* tmp = (*it)->getPixels();
			int tmp2[3];
			tmp2[0] = (int) tmp[i] - gaussianAveragePixels[i];
			tmp2[1] = (int) tmp[i + 1] - gaussianAveragePixels[i + 1];
			tmp2[2] = (int) tmp[i + 2] - gaussianAveragePixels[i + 2];
			gaussianDistributePixels[i] += tmp2[0] * tmp2[0];
			gaussianDistributePixels[i + 1] += tmp2[1] * tmp2[1];
			gaussianDistributePixels[i + 2] += tmp2[2] * tmp2[2];
			it++;
		}

		gaussianDistributePixels[i] = gaussianDistributePixels[i] / numOfImage;
		gaussianDistributePixels[i + 1] = gaussianDistributePixels[i + 1]
				/ numOfImage;
		gaussianDistributePixels[i + 2] = gaussianDistributePixels[i + 2]
				/ numOfImage;
	}

}

void Images::online(Image* image) {

	int color;
	double angle,hfsqrt;

	unsigned char* pixels = image->getPixels();
//	list<Image*>::iterator it;

	//double tmp[3];
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
			hfsqrt = gaussianHsqrtPixels[i*3]*hsqrt;
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

		/* TODO 更新 */
		//list<Image*>::iterator it = images.begin();
		//unsigned char* oldtmp = (*it)->getPixels();
		/* 古いのから上書きしてガウス平均を生成しなおす？ */
		//gaussianAveragePixels[i] = ( gaussianAveragePixels[i] * numOfImage +   ) / numOfImage;
	}

	test(image);

}

void Images::test(Image* image) {
	FILE *fp;

	if ((fp = fopen("result1.ppm", "w")) == NULL) {
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

