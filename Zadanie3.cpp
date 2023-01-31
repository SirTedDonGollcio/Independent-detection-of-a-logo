#include <opencv2/opencv.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>


const double PI = 3.141592653589793238463;

using namespace cv;
using namespace std;

float* histCalc(cv::Mat& I) {
	CV_Assert(I.depth() != sizeof(uchar));
	static float tab[8];
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
	tab[6] = 0;
	tab[7] = 0;
	switch (I.channels()) {
	case 3:
		cv::Mat_<cv::Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
		{
			for (int j = 0; j < I.cols; ++j) {
				if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 >= 0 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 32)
				{
					//std::cout << "1";
					tab[0] += 1;
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 32 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 64) {
					tab[1] += 1;
					//std::cout << "2";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 64 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 96) {
					tab[2] += 1;
					//std::cout << "3";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 96 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 128) {
					tab[3] += 1;
					//std::cout << "4";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 128 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 160) {
					tab[4] += 1;
					//std::cout << "5";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 160 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 192) {
					tab[5] += 1;
					//std::cout << "6";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 192 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 224) {
					tab[6] += 1;
					//std::cout << "7";
				}
				else if (((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 > 224 && ((_I(i, j)[2] + _I(i, j)[1] + _I(i, j)[0])) / 3 <= 255) {
					tab[7] += 1;
					//std::cout << "8";
				}
			}
		}
		break;
	}
	return tab;
}

int S(cv::Mat img_def)
{
	//CV_Assert(img.depth() != sizeof(uchar));
	cv::Mat_<cv::Vec3b> img = img_def;
	int sum_of_ObjectPixels = 0;
	//std::cout << img.rows << " " << img.cols << std::endl;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			//img(i, j) = 100;
			//std::cout << img.at<int>(i, j) << " ";
			//cout << i << " " << j << endl;
			if (img(i,j)[0] < 250)
			{
				sum_of_ObjectPixels++;
				//img(i, j)[0] = 100;
			}
		}
	}
	return sum_of_ObjectPixels;
}

int S_1d(cv::Mat img_def)
{
	//CV_Assert(img.depth() != sizeof(uchar));
	int sum_of_ObjectPixels = 0;
	//std::cout << img.rows << " " << img.cols << std::endl;
	for (int i = 0; i < img_def.rows; i++)
	{
		for (int j = 0; j < img_def.cols; j++)
		{
			//img(i, j) = 100;
			//std::cout << img.at<int>(i, j) << " ";
			//cout << i << " " << j << endl;
			if ((int)img_def.at<uchar>(i, j) < 250)
			{
				sum_of_ObjectPixels++;
				//img(i, j)[0] = 100;
			}
		}
	}
	return sum_of_ObjectPixels;
}

int L(cv::Mat img_def)
{
	//CV_Assert(img_def.depth() != sizeof(uchar));
	cv::Mat_<cv::Vec3b> img = img_def;
	int sum_of_ObjectPixels = 0;
	//std::cout << img.rows << " " << img.cols << std::endl;
	for (int i = 0; i < img.rows-1; i++)
	{
		for (int j = 0; j < img.cols-1; j++)
		{

			//cout << i << " " << j << endl;
			if ((img(i, j)[0] == 0 ) && (
				(img(i, j + 1)[0] > 0)	||
				(img(i, j - 1)[0] > 0) ||
				(img(i+1, j + 1)[0] > 0) ||
				(img(i-1, j + 1)[0] > 0) ||
				(img(i+1, j)[0] > 0) ||
				(img(i-1, j)[0] > 0) ||
				(img(i+1, j-1)[0] > 0) ||
				(img(i-1, j-1)[0] > 0)
				))
			{
				sum_of_ObjectPixels++;

			}
		}
	}
	return sum_of_ObjectPixels;
}

int L_1d(cv::Mat img)
{
	//CV_Assert(img_def.depth() != sizeof(uchar));
	int sum_of_ObjectPixels = 0;
	//std::cout << img.rows << " " << img.cols << std::endl;
	for (int i = 0; i < img.rows - 1; i++)
	{
		for (int j = 0; j < img.cols - 1; j++)
		{

			//cout << i << " " << j << endl;
			if (((int)img.at<uchar>(i, j) == 0) && (
				((int)img.at<uchar>(i, j + 1) > 0) ||
				((int)img.at<uchar>(i, j - 1) > 0) ||
				((int)img.at<uchar>(i + 1, j + 1) > 0) ||
				((int)img.at<uchar>(i - 1, j + 1) > 0) ||
				((int)img.at<uchar>(i + 1, j) > 0) ||
				((int)img.at<uchar>(i - 1, j) > 0) ||
				((int)img.at<uchar>(i + 1, j - 1) > 0) ||
				((int)img.at<uchar>(i - 1, j - 1) > 0)
				))
			{
				sum_of_ObjectPixels++;

			}
		}
	}
	return sum_of_ObjectPixels;
}

float W3(int S, int L)
{
	float result;

	result = L / (2 * (sqrt(S*PI))) - 1;

	return result;
}

float M(int whichM, cv::Mat img_def, float m_00_s)
{
	cv::Mat_<cv::Vec3b> img = img_def;
	float m_10_x = 0;
	float m_01_y = 0;
	float m_11_xy = 0;
	float m_20_x2 = 0;
	float m_02_y2 = 0;
	float m_12_xy2 = 0;
	float m_21_x2y = 0;

	for (float i = 0; i < img.rows; i++)
	{
		for (float j = 0; j < img.cols; j++)
		{

			if ((img(i, j)[0] == 0) || (img(i, j)[1] == 0) || (img(i, j)[2] == 0))
			{
				m_10_x = m_10_x + j;
				m_01_y = m_01_y + i;
				m_11_xy = m_11_xy + i * j;

				m_20_x2 = m_20_x2 + pow(j, 2);
				m_02_y2 = m_02_y2 + pow(i, 2);
				m_12_xy2 = m_12_xy2 + pow(j, 2)*i;
				m_21_x2y = m_21_x2y + pow(i, 2)*j;
				//img(i, j)[0] = 100;
			}
		}
	}

	float result;

	if (whichM == 1)
	{
		result = ((m_20_x2 - (pow(m_10_x, 2) / m_00_s)) + (m_02_y2 - pow(m_01_y,2)/ m_00_s)) / pow(m_00_s, 2);
	}
	else
	{
		result =( (m_20_x2 - (pow(m_10_x, 2) / m_00_s))* (m_02_y2 - pow(m_01_y, 2) / m_00_s) - pow((m_11_xy - (m_10_x*m_01_y / m_00_s)),2) ) / pow(m_00_s, 4);
	}
	return result;
}

float M_1d(int whichM, cv::Mat img, float m_00_s)
{
	float m_10_x = 0;
	float m_01_y = 0;
	float m_11_xy = 0;
	float m_20_x2 = 0;
	float m_02_y2 = 0;
	float m_12_xy2 = 0;
	float m_21_x2y = 0;

	for (float i = 0; i < img.rows; i++)
	{
		for (float j = 0; j < img.cols; j++)
		{

			if ((int)img.at<uchar>(i, j) == 0)
			{
				m_10_x = m_10_x + j;
				m_01_y = m_01_y + i;
				m_11_xy = m_11_xy + i * j;

				m_20_x2 = m_20_x2 + pow(j, 2);
				m_02_y2 = m_02_y2 + pow(i, 2);
				m_12_xy2 = m_12_xy2 + pow(j, 2) * i;
				m_21_x2y = m_21_x2y + pow(i, 2) * j;
				//img(i, j)[0] = 100;
			}
		}
	}

	float result;

	if (whichM == 1)
	{
		result = ((m_20_x2 - (pow(m_10_x, 2) / m_00_s)) + (m_02_y2 - pow(m_01_y, 2) / m_00_s)) / pow(m_00_s, 2);
	}
	else
	{
		result = ((m_20_x2 - (pow(m_10_x, 2) / m_00_s)) * (m_02_y2 - pow(m_01_y, 2) / m_00_s) - pow((m_11_xy - (m_10_x * m_01_y / m_00_s)), 2)) / pow(m_00_s, 4);
	}
	return result;
}

float angle_of_arrow(cv::Mat img_def, float m_00_s)
{
	cv::Mat_<cv::Vec3b> img = img_def;
	float m_10_x = 0;
	float m_01_y = 0;

	for (float i = 0; i < img.rows; i++)
	{
		for (float j = 0; j < img.cols; j++)
		{

			if ((img(i, j)[0] == 0) || (img(i, j)[1] == 0) || (img(i, j)[2] == 0))
			{
				m_10_x = m_10_x + j;
				m_01_y = m_01_y + i;
				//img(i, j)[0] = 100;
			}
		}
	}

	float center_point_x = img_def.cols / 2;
	float center_point_y = img_def.rows / 2;
	float center_of_gravity_x = m_10_x / m_00_s;
	float center_of_gravity_y = m_01_y / m_00_s;

	/*Point pt1 = Point(int(center_point_x), int(center_point_y));
	Point pt2 = Point(int(center_of_gravity_x), int(center_of_gravity_y));
	
	circle(img_def, pt1, 1, Scalar(0, 255, 0), 8, 8, 0);
	circle(img_def, pt2, 1, Scalar(255, 0, 0), 8, 8, 0);*/

	//cout << "\nPunkt srodkowy obrazka to: " << center_point_x << " " << center_point_y << " a srodek ciezkosci to: " << center_of_gravity_x << " " << center_of_gravity_y << endl;
	//float tg_kata = abs(center_point_y - center_of_gravity_y) / abs(center_of_gravity_x - center_point_x) ;

	return abs((atan2(center_point_x - center_of_gravity_x,center_point_y - center_of_gravity_y) * 180 / PI) - 90);
}

void colorOneSector(Mat picture, int coordX, int coordY, int iterownik)
{
	picture.at<uchar>(coordX, coordY) = 50;

	if (iterownik < 500)
	{
		if ((int)picture.at<uchar>(coordX, coordY + 1) > 200)
		{
			colorOneSector(picture, coordX, coordY + 1, iterownik+1);
		}
		else if ((int)picture.at<uchar>(coordX, coordY - 1) > 200)
		{
			colorOneSector(picture, coordX, coordY - 1, iterownik + 1);
		}
		else if ((int)picture.at<uchar>(coordX + 1, coordY) > 200)
		{
			colorOneSector(picture, coordX + 1, coordY, iterownik + 1);
		}
		else if ((int)picture.at<uchar>(coordX - 1, coordY) > 200)
		{
			colorOneSector(picture, coordX - 1, coordY, iterownik + 1);
		}
	}
}

bool isWhiteNextToThatGray(Mat p, int x, int y)
{
	int result;
	if((int)p.at<uchar>(x, y+1) == 255)
	{
		return 1;
	}
	else if ((int)p.at<uchar>(x, y - 1) == 255)
	{
		return 1;
	}
	else if ((int)p.at<uchar>(x - 1, y) == 255)
	{
		return 1;
	}
	else if ((int)p.at<uchar>(x + 1, y) == 255)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void tryToPaintOneSector(Mat picture)
{
	int stillWhiteNextToGray = 0, itertempik = 0;
	while (stillWhiteNextToGray < 1)
	{
		stillWhiteNextToGray = 0;
		for (int i = picture.rows - 2; i > 2; i--)
		{
			for (int j = picture.cols - 2; j > 2; j--)
			{
				if ((int)picture.at<uchar>(i, j) == 255 && (int)picture.at<uchar>(i, j + 1) == 50)
				{
					picture.at<uchar>(i, j) = 50;
					if (isWhiteNextToThatGray(picture, i, j))
					{
						stillWhiteNextToGray++;
					}
				}
				else if ((int)picture.at<uchar>(i, j) == 255 && (int)picture.at<uchar>(i, j - 1) == 50)
				{
					picture.at<uchar>(i, j) = 50;
					if (isWhiteNextToThatGray(picture, i, j))
					{
						stillWhiteNextToGray++;
					}
				}
				else if ((int)picture.at<uchar>(i, j) == 255 && (int)picture.at<uchar>(i - 1, j) == 50)
				{
					picture.at<uchar>(i, j) = 50;
					if (isWhiteNextToThatGray(picture, i, j))
					{
						stillWhiteNextToGray++;
					}
				}
				else if ((int)picture.at<uchar>(i, j) == 255 && (int)picture.at<uchar>(i - 1, j) == 50)
				{
					picture.at<uchar>(i, j) = 50;
					if (isWhiteNextToThatGray(picture, i, j))
					{
						stillWhiteNextToGray++;
					}
				}

			}
		}
		itertempik++;
		if (itertempik > 150)
		{
			stillWhiteNextToGray++;
		}
	}
}

void paintOneToSector(Mat p)
{
	int iHaventPainted = 0;
	while(iHaventPainted == 0)
	{
		iHaventPainted = 1;
		for (int i = p.rows - 2; i > 2 ; i--)
		{
			for (int j = p.cols - 2; j >2 ; j--)
			{
				if ((int)p.at<uchar>(i, j) == 255 && (int)p.at<uchar>(i, j + 1) == 50)
				{
					p.at<uchar>(i, j) = 50;
					iHaventPainted = 0;
				}
				else if ((int)p.at<uchar>(i, j) == 255 && (int)p.at<uchar>(i, j - 1) == 50)
				{
					p.at<uchar>(i, j) = 50;
					iHaventPainted = 0;
				}
				else if ((int)p.at<uchar>(i, j) == 255 && (int)p.at<uchar>(i - 1, j) == 50)
				{
					p.at<uchar>(i, j) = 50;
					iHaventPainted = 0;
				}
				else if ((int)p.at<uchar>(i, j) == 255 && (int)p.at<uchar>(i - 1, j) == 50)
				{
					p.at<uchar>(i, j) = 50;
					iHaventPainted = 0;
				}
			}
		}
	}
}


void startPaintingOneSector(Mat p)
{
	int tempI = p.rows-1, tempJ = p.cols-1, stoppenmeier = 0;
	while (stoppenmeier < 1)
	{
		if (tempJ > 1)
		{
			if ((int)p.at<uchar>(tempI, tempJ) == 255)
			{
				p.at<uchar>(tempI, tempJ) = 50;
				stoppenmeier++;
			}
			tempJ--;
		}
		else
		{
			tempI--;
			tempJ = p.cols-1;
		}
	}
}


bool searchForTheFirstToSeen(Mat p, vector<Point>* seenPoints)
{
	for (int i = 1; i < p.rows - 1; i++)
	{
		for (int j = 1; j < p.cols - 1; j++)
		{
			if ((int)p.at<uchar>(i, j) == 255)
			{
				int isSeen = 0;
				for (int k = 0; k < seenPoints->size(); k++)
				{
					if ((*seenPoints)[k] == Point(i, j))
					{
						isSeen++;
					}
				}
				if (isSeen == 0)
				{
					seenPoints->push_back(Point(i, j));
					///std::cout << "Znalazlem punkt: " << i << " " << j << endl;
					return true;

				}
			}
		}
	}
	std::cout << "Nothing found";
	return false;
}

vector<Point> addEveryPointOfTheNeighbor(Mat p, vector<Point>* seenPoints)
{
	vector<Point> pointsOfOneSector;

	bool didSmtHappenInThisLoop = true;
	int limiter = 0;

	while (didSmtHappenInThisLoop && limiter < 50)
	{
		didSmtHappenInThisLoop = false;
		limiter++;
		for (int i = 1; i < p.rows - 1; i++)
		{
			//cout << "Ehh" << i << endl;
			for (int j = 1; j < p.cols - 1; j++)
			{
				//cout << i << " " << j << endl; //TUTAJ MSASZ PATRZEC TERAZ

				if ((int)p.at<uchar>(i, j) == 255)
				{
					int isSeen = 0;
					for (int k = 0; k < seenPoints->size(); k++)
					{
						if ((*seenPoints)[k] == Point(i, j))
						{
							isSeen++;
						}
					}
					if (isSeen == 0)
					{
						int isSeenNeighor = 0;
						for (int k = 0; k < seenPoints->size(); k++)
						{
							if ((*seenPoints)[k] == Point(i + 1, j) || (*seenPoints)[k] == Point(i - 1, j) || (*seenPoints)[k] == Point(i, j - 1) || (*seenPoints)[k] == Point(i, j + 1))
							{
								isSeenNeighor++;
							}
						}
						if (isSeenNeighor != 0)
						{
							pointsOfOneSector.push_back(Point(i, j));
							seenPoints->push_back(Point(i, j));
							didSmtHappenInThisLoop = true;
							///std::cout << "Znalazlem Sasiada: " << i << " " << j << endl;
							limiter = 0;
						}
					}

				}
			}
		}
	}
	//cout << "SkonyczlemSzukac\n";
	return pointsOfOneSector;
}

void paintWithVector(Mat p, vector<Point> v)
{
	for (int i = 1; i < p.rows - 1; i++)
	{
		for (int j = 1; j < p.cols - 1; j++)
		{
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k] == Point(i, j))
				{
					p.at<uchar>(i, j) = 50;
					//std::cout << "Pomalowalem punkt: " << i << " " << j << endl;
				}
			}
		}
	}
	std::cout << "Congratulation!" << endl;
	Mat imS_diff;
	cv::resize(p, imS_diff, Size(270, 360));
	cv::imshow("Fragment that's been discovered", imS_diff);
	cv::waitKey(-1);
}

bool isObjectAnEtiqeuete(vector<Point> v, Mat p, int* coordsToC)
{
	int minCoordX=750, maxCoordX=0, minCoordY=1000, maxCoordY=0;

	Point ul = Point(1000,1000), ur = Point(0, 1000), dl = Point(1000, 0), dr = Point(0, 0);

	int max_ul = 0, max_ur = 0, max_dl = 0, max_dr = 0;

	for (int k = 0; k < v.size(); k++)
	{
		if (v[k].y < minCoordY)
		{
			minCoordY = v[k].y;
		}

		if (v[k].y > maxCoordY)
		{
			maxCoordY = v[k].y;
		}


		if (v[k].x < minCoordX)
		{
			minCoordX = v[k].x;
		}
		if (v[k].x > maxCoordX)
		{
			maxCoordX = v[k].x;
		}

		if ((p.rows - v[k].y) + (p.cols - v[k].x) >= max_ul)
		{
			max_ul = (p.rows - v[k].y) + (p.cols - v[k].x);
			ul = v[k];
		}
		if ((p.rows - v[k].y) + v[k].x >= max_ur)
		{
			max_ur = (p.rows - v[k].y) + v[k].x;
			ur = v[k];
		}
		if (v[k].y + (p.cols - v[k].x) >= max_dl)
		{
			max_dl = v[k].y + (p.cols - v[k].x);
			dl = v[k];
		}
		if (v[k].y + v[k].x >= max_dr)
		{
			max_dr = v[k].y + v[k].x;
			dr = v[k];
		}
	}

	std::cout << "Points of the rectangle (maybe): " << ul << " " << ur << " " << dl << " " << dr << endl;


	float side1y = pow((float)ur.y - (float)ul.y, 2);
	float side1x = pow((float)ur.x - (float)ul.x, 2);
	float side1 = sqrt(side1y + side1x);

	float side2y = pow((float)dr.y - (float)dl.y, 2);
	float side2x = pow((float)dr.x - (float)dl.x, 2);
	float side2 = sqrt(side2y + side2x);

	float side3y = pow((float)ur.y - (float)dr.y, 2);
	float side3x = pow((float)ur.x - (float)dr.x, 2);
	float side3 = sqrt(side3y + side3x);

	float side4y = pow((float)ul.y - (float)dl.y, 2);
	float side4x = pow((float)ul.x - (float)dl.x, 2);
	float side4 = sqrt(side4y + side4x);

	float side12 = (side1 + side2) / 2;
	float side34 = (side3 + side4) / 2;

	float longerSide, shorterSide;

	if (side12 > side34)
	{
		longerSide = side12;
		shorterSide = side34;
	}
	else
	{
		longerSide = side34;
		shorterSide = side12;
	}

	std::cout << "Coords of this object is: " << minCoordX << " " << minCoordY << " " << maxCoordX << " " << maxCoordY << endl;

	std::cout << "Longer side: " << longerSide << ", and shorter side: " << shorterSide << endl;

	float xToy = longerSide / shorterSide;

	std::cout << "The fraction of x to y of this object is: " << xToy << endl;

	Mat p2 = p(Range(minCoordX, maxCoordX), Range(minCoordY, maxCoordY));// , imS_diff;
	//cv::resize(p2, imS_diff, Size(270, 360));
	//cv::imshow("thatsCropped", p2);
	//cv::waitKey(-1);

	//float s_temp = longerSide * shorterSide, l_temp = longerSide*2 + shorterSide*2;
	//int s = s_temp, l = l_temp;

	Mat blackS(p.cols, p.rows, CV_8UC3, cv::Scalar(255, 255, 255));
	Point vertices[4] = { Point(ul.y,ul.x),Point(ur.y,ur.x),Point(dr.y,dr.x),Point(dl.y,dl.x) };
	fillConvexPoly(blackS,vertices,4, Scalar(0, 0, 0));
	//cv::imshow("black new object", blackS);
	//cv::waitKey(-1);

	float s = S(blackS), l = L(blackS);
	float w3 = W3(s, l);
	float m1 = M(1, blackS, s);
	float m7 = M(7, blackS, s);

	std::cout << "Factors are : w3: " << w3 << ", m1: " << m1 << ", m7: " << m7 << endl;

	bool bool_front = (xToy > 2 && xToy < 2.25);
	bool bool_back = (xToy > 3 && xToy < 3.1);

	bool boolw3_front = (w3 > 0.2 && w3 < 0.6);
	bool boolw3_back = (w3 > 0.29 && w3 < 0.35);

	bool boolm1_front = (m1 > 0.21 && m1 < 0.22);
	bool boolm1_back = (m1 > 0.27 && m1 < 0.28);

	bool boolm7_front = (m7 > 0.0069 && m7 < 0.0071);
	bool boolm7_back = (m7 > 0.0068 && m7 < 0.0071);

	if ((bool_front && boolw3_front && boolm1_front && boolm7_front) || (bool_back && boolw3_back && boolm1_back && boolm7_back))
	{
		coordsToC[0] = minCoordX;
		coordsToC[1] = maxCoordX;
		coordsToC[2] = minCoordY;
		coordsToC[3] = maxCoordY;

		std::cout << "Yes, it is etiquete!!!" << endl;
		return true;
	}
	else
	{
		std::cout << "Unfortunetly, it is not..." << endl;
		return false;
	}
}

bool isObjectALetter(vector<Point> v, Mat p)
{
	int minCoordX = 750, maxCoordX = 0, minCoordY = 1000, maxCoordY = 0;

	for (int k = 0; k < v.size(); k++)
	{
		if (v[k].y < minCoordY)
		{
			minCoordY = v[k].y;
		}

		if (v[k].y > maxCoordY)
		{
			maxCoordY = v[k].y;
		}

		if (v[k].x < minCoordX)
		{
			minCoordX = v[k].x;
		}
		if (v[k].x > maxCoordX)
		{
			maxCoordX = v[k].x;
		}
	}

	std::cout << "Coords of this letter(?) is: " << minCoordX << " " << minCoordY << " " << maxCoordX << " " << maxCoordY << endl;


	Mat p2 = p(Range(minCoordX-1, maxCoordX+1), Range(minCoordY-1, maxCoordY+1)).clone();

	/*Mat imS_diff;
	cv::resize(p2, imS_diff, Size(270, 360));
	cv::imshow("Ejo", imS_diff);
	cv::waitKey(-1);*/

	float s = S_1d(p2), l = L_1d(p2);
	float w3 = W3(s, l);
	float m1 = M_1d(1, p2, s);
	float m7 = M_1d(7, p2, s);

	std::cout << "Factors of letter is : w3: " << w3 << ", m1: " << m1 << ", m7: " << m7 << endl;

	return true;
	/*bool bool_front = (xToy > 2 && xToy < 2.25);
	bool bool_back = (xToy > 3 && xToy < 3.1);

	bool boolw3_front = (w3 > 0.2 && w3 < 0.6);
	bool boolw3_back = (w3 > 0.29 && w3 < 0.35);

	bool boolm1_front = (m1 > 0.21 && m1 < 0.22);
	bool boolm1_back = (m1 > 0.27 && m1 < 0.28);

	bool boolm7_front = (m7 > 0.0069 && m7 < 0.0071);
	bool boolm7_back = (m7 > 0.0068 && m7 < 0.0071);

	if ((bool_front && boolw3_front && boolm1_front && boolm7_front) || (bool_back && boolw3_back && boolm1_back && boolm7_back))
	{
		std::cout << "Tak to litera!!!" << endl;
		return true;
	}
	else
	{
		std::cout << "Co? Jakto nie..." << endl;
		return false;
	}*/
}

void paintLetter(Mat p, vector<Point> v)
{
	for (int i = 1; i < p.rows - 1; i++)
	{
		for (int j = 1; j < p.cols - 1; j++)
		{
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k] == Point(i, j))
				{
					p.at<uchar>(i, j) = 50;
					//std::cout << "Pomalowalem punkt: " << i << " " << j << endl;
				}
			}
		}
	}
	std::cout << "Congratulation - letter is ready to show" << endl;
	//Mat imS_diff;
	//cv::resize(p, imS_diff, Size(270, 360));

	cv::imshow("Fragment that's been discovered 2", p);
	cv::waitKey(-1);
}

void paintLetter_3channel(Mat p, vector<Point> v)
{
	cv::Mat_<cv::Vec3b> img = p;
	for (int i = 1; i < p.rows - 1; i++)
	{
		for (int j = 1; j < p.cols - 1; j++)
		{
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k] == Point(i, j))
				{
					img(i, j)[1] = 255;
					img(i, j)[0] = 0;
					img(i, j)[2] = 0;
					//std::cout << "Pomalowalem punkt: " << i << " " << j << endl;
				}
			}
		}
	}
	std::cout << "Congratulation - letter is ready to show" << endl;
	//Mat imS_diff;
	//cv::resize(p, imS_diff, Size(270, 360));

	cv::imshow("Visualization of detection", img);
	cv::waitKey(-1);
}


int main(int, char *[]) {
	
	std::cout << "Start ..." << std::endl;

	vector<cv::String> fn;
	glob("lomza/*.jpg", fn, false);

	vector<Mat> images;
	size_t count = fn.size(); //number of png files in images folder
	
	//for (size_t i = 0; i < count; i++)
	//	images.push_back(imread(fn[i]));

	for (int imgIter = 0; imgIter < fn.size(); imgIter++)
	{
		images.push_back(imread(fn[imgIter]));
		Mat image = images[imgIter];

		Mat imageS;
		cv::resize(image, imageS, Size(300, 400));

		Mat redChannel, blueChannel, greenChannel;
		vector<Mat> channels(3);
		split(imageS, channels);
		blueChannel = channels[0].clone();
		greenChannel = channels[1].clone();
		redChannel = channels[2].clone();

		//Mat treshedR, treshedG, treshedB;
		//threshold(redChannel, treshedR, 140, 255, THRESH_BINARY);//THRESH_TOZERO);
		//threshold(greenChannel, treshedG, 75, 255, THRESH_BINARY);//THRESH_TOZERO);
		//threshold(blueChannel, treshedB, 120, 255, THRESH_BINARY);//THRESH_TOZERO);

		Mat diffM;// , diffM2;
		absdiff(redChannel, greenChannel, diffM);


		//absdiff(diffM, blueChannel, diffM);
		Mat treshedDiff;
		threshold(diffM, treshedDiff, 80, 255, THRESH_BINARY);//THRESH_TOZERO);


		/*
		for (int i = 0; i < treshedDiff.rows; i++)
		{
			for (int j = 0; j < treshedDiff.cols; j++)
			{
				if ((int)treshedDiff.at<uchar>(i, j) == 255)
				{
					//treshedDiff.at<uchar>(i, j) = 50;
					break;
					break;
				}
			}
		}*/

		//for (int i = 0; i < 10; i++)
		//{
		//	startPaintingOneSector(treshedDiff);
		//	//checkThisShit(treshedDiff);
		//	paintOneToSector(treshedDiff);
		//	//tryToPaintOneSector(treshedDiff);
		//}
		//checkThisShit(treshedDiff);

		Mat erodedDiff;
		Mat kernelErosion = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
		erode(treshedDiff, erodedDiff, kernelErosion);


		Mat dilatatedDiff;
		Mat kernelDilatate = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));
		dilate(erodedDiff, dilatatedDiff, kernelDilatate);

		/*Mat cropi = images[0](Range(489, 557), Range(500, 672));
		Mat cropi2 = images[0](Range(500 - 20, 557 + 20), Range(489 - 20, 672 + 20));
		//Mat imimimi;
		//cv::resize(cropi, imimimi, Size(270, 360));
		cv::imshow("imimimi", cropi);
		cv::imshow("imimimi3", cropi2);*/

		//cv::imshow("imimimi2", dilatatedDiff);
		//cv::waitKey(-1);


		/*Mat bajojajo;
		cv::resize(dilatatedDiff, bajojajo, Size(270, 360));
		cv::imshow("bajojajo", bajojajo);
		cv::waitKey(-1);*/

		vector<Point> seenPixels;

		treshedDiff = dilatatedDiff.clone();
		bool canYouFindNewSector = true;
		int itermeier = 1;

		while (canYouFindNewSector)
		{
			std::cout << "------------------\nIteration nr " << itermeier++ << endl;
			canYouFindNewSector = searchForTheFirstToSeen(treshedDiff, &seenPixels);

			if (canYouFindNewSector)
			{
				vector<Point> objectApparently = addEveryPointOfTheNeighbor(treshedDiff, &seenPixels);

				int coordsToClip[4];
				int* pointerToCoords = coordsToClip;

				bool isIt = isObjectAnEtiqeuete(objectApparently, treshedDiff, pointerToCoords);

				if (isIt)
				{
					Mat etiq = imageS(Range(coordsToClip[0], coordsToClip[1]), Range(coordsToClip[2], coordsToClip[3]));

					split(etiq, channels);
					blueChannel = channels[0].clone();

					Mat treshedDiff_etiq, treshedDiff_etiqInv;
					threshold(blueChannel, treshedDiff_etiq, 150, 255, THRESH_BINARY);
					threshold(blueChannel, treshedDiff_etiqInv, 150, 255, THRESH_BINARY_INV);

					/*Mat ero_treshedDiff_etiq, ero_treshedDiff_etiqInv;
					kernelErosion = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
					erode(treshedDiff_etiq, ero_treshedDiff_etiq, kernelErosion);
					erode(treshedDiff_etiqInv, ero_treshedDiff_etiqInv, kernelErosion);
					dilate(ero_treshedDiff_etiq, treshedDiff_etiq, kernelErosion);
					dilate(ero_treshedDiff_etiqInv, treshedDiff_etiqInv, kernelErosion);
					//treshedDiff_etiq = ero_treshedDiff_etiq.clone();
					//treshedDiff_etiqInv = ero_treshedDiff_etiqInv.clone();
					cv::imshow("HejMamEtykiete123", treshedDiff_etiq);
					cv::waitKey(-1);*/

					vector<Point> seenPixels_etiq;
					bool canYouFindNewSector_etiq = true;
					while (canYouFindNewSector_etiq)
					{
						canYouFindNewSector_etiq = searchForTheFirstToSeen(treshedDiff_etiq, &seenPixels_etiq);
						if (canYouFindNewSector_etiq)
						{
							vector<Point> objectApparently_letter = addEveryPointOfTheNeighbor(treshedDiff_etiq, &seenPixels_etiq);
							if (objectApparently_letter.size() > 10)
							{
								float s = S_1d(treshedDiff_etiqInv), l = L_1d(treshedDiff_etiqInv);
								float w3 = W3(s, l);
								float m1 = M_1d(1, treshedDiff_etiqInv, s);
								float m7 = M_1d(7, treshedDiff_etiqInv, s);

								std::cout << "Factors of ALL letters are : w3: " << w3 << ", m1: " << m1 << ", m7: " << m7 << endl;

								bool bool_w3 = (w3 > 3.6 && w3 < 4.6);
								bool bool_m1 = (m1 > 0.37 && m1 < 0.55);
								bool boolw3_m7 = (m7 > 0.014 && m7 < 0.023);

								if (bool_w3 && bool_m1 && boolw3_m7)
								{
									cout << "WOW THE LOGO HAS BEEN FOUND!!!" << endl;
									vector<Point> objectApparently_letter_normlized = objectApparently_letter;
									for (int ii = 0; ii < objectApparently_letter_normlized.size(); ii++)
									{
										objectApparently_letter_normlized[ii] = Point(objectApparently_letter[ii].x + coordsToClip[0], objectApparently_letter[ii].y + coordsToClip[2]);
									}
									paintLetter_3channel(imageS, objectApparently_letter_normlized);
								}
								/*
								bool isItLetter = isObjectALetter(objectApparently_letter, treshedDiff_etiqInv);

								if (isItLetter)
								{
									paintLetter(treshedDiff_etiq, objectApparently_letter);
								}*/
							}
							else
							{
								cout << "TOO LOW!!";
							}
						}
					}

					cv::imshow("I have an etiquete", treshedDiff_etiq);
					cv::waitKey(-1);
				}

				//cout << "Teraz maluje zobaczone!" << endl;
				//paintWithVector(treshedDiff, seenPixels);
				// 
				//cout << "Teraz maluje z obiektu znalezionego!" << endl;
				//paintWithVector(treshedDiff, objectApparently);
			}

			std::cout << endl;
		}


		Mat imS_diff;
		cv::resize(treshedDiff, imS_diff, Size(270, 360));
		cv::imshow("Differented channel", imS_diff);
		cv::waitKey(-1);
	}
	

    return 0;
}
