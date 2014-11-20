#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>

#include "Image.h"

using namespace std;

/* 正規化
 * コンストラクタで画像の読み込み
 * */

Image::Image() {
	// cout << "Image::Image( char * filename) start" << endl;
/*

	IplImage *tmp_img = cvLoadImage(filename,CV_LOAD_IMAGE_ANYCOLOR);
	sprintf(fileName, "/home/user/img/temp.ppm");
	cvSaveImage(fileName,tmp_img);
	cvReleaseImage(&tmp_img);

	iPixels = NULL;
	FILE * fp;
	//header = new char[MAX_STR];
	char chrImageSize[MAX_STR];
	char chrMaxLuminance[MAX_STR];

	if ((fp = fopen(fileName, "r")) == NULL) {
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}

	fgets(header, MAX_STR, fp); // header
	skip(fp);

	fgets(chrImageSize, MAX_STR, fp); // width height
	skip(fp);

	fgets(chrMaxLuminance, MAX_STR, fp); // maxLuminance
	sscanf(chrImageSize, "%d %d", &width, &height);
	sscanf(chrMaxLuminance, "%d", &maxLuminance);

	 caution: pixel needs to delete
	 終わりまで画像情報を読み込む
	unsigned char *tmp = new unsigned char[3 * width * height];
	fread(tmp, sizeof(char), 3 * width * height, fp);
	this->pixels = tmp;
	fclose(fp);

	//normalize();
	//grayscaling();
	test(header, width, height, maxLuminance);
	//cout << "Image::Image( char *filename) exit" << endl;


*/

}


Image::Image(char *fileName) {
	// cout << "Image::Image( char * filename) start" << endl;
	//cout << fileName << endl;
	IplImage *tmp_img = cvLoadImage(fileName,CV_LOAD_IMAGE_ANYCOLOR);
	sprintf(fileName, "/home/user/img/temp.ppm");
	cvSaveImage(fileName,tmp_img);
	cvReleaseImage(&tmp_img);

	iPixels = NULL;
	FILE * fp;
	//header = new char[MAX_STR];
	char chrImageSize[MAX_STR];
	char chrMaxLuminance[MAX_STR];

	if ((fp = fopen(fileName, "r")) == NULL) {
		printf("file open error\n");
		exit(EXIT_FAILURE);cout << "Image::Image( char *filename) exit" << endl;
	}

	fgets(header, MAX_STR, fp); // header
	skip(fp);

	fgets(chrImageSize, MAX_STR, fp); // width height
	skip(fp);

	fgets(chrMaxLuminance, MAX_STR, fp); // maxLuminance
	sscanf(chrImageSize, "%d %d", &width, &height);
	sscanf(chrMaxLuminance, "%d", &maxLuminance);

	//caution: pixel needs to delete
	//終わりまで画像情報を読み込む
	unsigned char *tmp = new unsigned char[3 * width * height];
	fread(tmp, sizeof(char), 3 * width * height, fp);
	this->pixels = tmp;
	//cout << "AAA" << endl;
	//this->pixels = (unsigned char *)tmp_img->imageData;
	//cout << "BBB" << endl;
	fclose(fp);

	//normalize();
	//grayscaling();
	test(header, width, height, maxLuminance);
	//cout << "CCC" << endl;
	//cout << "Image::Image( char *filename) exit" << endl;
}

/* コンストラクタ
 * 0で初期化されたものが生成される
 * */
Image::Image(int widthL, int heightL,int flag) {

	//cout << "Image::Image( in widthL, int heightL) start" << endl;
if(flag==0){
	iPixels = new int[3 * widthL * heightL];
	pixels = 0;
	//header = NULL;
	fill_n(iPixels, 3 * widthL * heightL, 0);
}

if(flag==1){
	dPixels = new double[widthL * heightL];
	pixels = 0;
	//header = NULL;
	fill_n(dPixels, 3 * widthL * heightL, 0.0);
}
	
	//cout << "Image::Image( int widthL, int heightL) exit" << endl;
}


/* デストラクタ */
Image::~Image() {

	//cout << "Image::~Image() start" << endl;
	delete[] (pixels);
	pixels = NULL;
	delete[] (iPixels);
	iPixels = NULL;
	//delete[] (header);
	//header = NULL;

	//cout << "Image::~Image() end" << endl;

}



void Image::skip(FILE * fp) {
	char chLine[MAX_STR];
	fpos_t current;
	while (!feof(fp)) {
		//現在のストリーム位置の保存
		fgetpos(fp, &current);
		// １行取得
		fgets(chLine, MAX_STR, fp);
		// コメント行でなければ，ストリーム位置を戻してリターン
		if (chLine[0] != '#') {
			fsetpos(fp, &current);
			return;
		}
	}
}

/* getter */
unsigned char *Image::getPixels() {
	return this->pixels;
}

int *Image::getiPixels() {
	return this->iPixels;
}

double *Image::getdPixels() {
	return this->dPixels;
}

/* 正規化 */
void Image::normalize() {
	double total = 0;
	double red, green, blue;
	for (int i = 0; i < this->width * this->height * 3; i += 3) {
		total = pixels[i] + pixels[i + 1] + pixels[i + 2];
		red = this->pixels[i] / total;
		green = this->pixels[i + 1] / total;
		blue = 1.0 - red - green;
		if ((red > 0.27 && red < 0.39) && (green > 0.27 && green < 0.39)) {
			if (total < 25) {
				red = 0;
				green = 0;
				blue = 0;
			}
		}

		this->pixels[i] = (unsigned char) (red * 1024);
		this->pixels[i + 1] = (unsigned char) (green * 1024);
		this->pixels[i + 2] = (unsigned char) (blue * 1024);

	}
}

void Image::grayscaling() {

	
}

char *Image::getHeader() {
	return header;
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

int Image::getMaxLuminance() {
	return maxLuminance;
}

/* デバック用の画像出力 */
void Image::test(char *header, int width, int height, int maxLuminance) {

	FILE * fp;

	if ((fp = fopen("Image_test.ppm", "w")) == NULL) {
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "%s\n", header);
	fprintf(fp, "%d %d\n", width, height);
	fprintf(fp, "%d\n", maxLuminance);

	unsigned char *tmp = getPixels();
	fwrite(tmp, sizeof(char), 3 * width * height, fp);

	fclose(fp);
}
