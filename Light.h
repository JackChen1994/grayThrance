// Light.h: interface for the Light class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__C1F962E2_0441_443B_A1B0_0FA0AC4D0F58__INCLUDED_)
#define AFX_LIGHT_H__C1F962E2_0441_443B_A1B0_0FA0AC4D0F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class Light : public ImageDib  
{
public:
	//输出图像每像素位数
	int m_nBitCountOut;

	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;
	
	unsigned char * m_pImgDataIn1;
	unsigned char * m_pImgDataIn2;

	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;
	int** B;
	int** G;
	int** R;
	
	//double MAXNUM=1e+8			//最大整数

private:
	//输出图像的宽，像素为单位
	int m_imgWidthOut;

	//输出图像的高，像素为单位
	int m_imgHeightOut;

	//输出图像颜色表长度
	int m_nColorTableLengthOut;

public:
	void CalSBound(int top,int bottom,int left,int right);
	//不带参数的构造函数
	Light();

	//带参数的构造函数
	Light(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData1,unsigned char *pImgData2);

	//析构函数
	~Light();
	
	void CalSim();

	CSize GetDimensions();
	int CLightMath(int C_b,int C_g,int C_r);
};

#endif // !defined(AFX_LIGHT_H__C1F962E2_0441_443B_A1B0_0FA0AC4D0F58__INCLUDED_)
