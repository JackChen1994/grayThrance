// LBP.h: interface for the LBP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBP_H__2B2828F4_58EC_4C41_A4EF_28C665AC9D79__INCLUDED_)
#define AFX_LBP_H__2B2828F4_58EC_4C41_A4EF_28C665AC9D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class LBP : public ImageDib  
{
public:
	//输出图像每像素位数
	int m_nBitCountOut;
	
	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;
	
	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;

	//输出图像的宽，像素为单位
	int m_imgWidthOut;
	
	//输出图像的高，像素为单位
	int m_imgHeightOut;
	
	//输出图像颜色表长度
	int m_nColorTableLengthOut;
	
public:
	void CalSim();
	//不带参数的构造函数
	LBP();
	
	//带参数的构造函数
	LBP(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	
	//析构函数
	~LBP();
	
	//以像素为单位返回输出图像的宽和高
	CSize GetDimensions();
	
	//二值化
	void BinaryImage(int threshold=128);

	//反转
	void RevImage();

    //窗口变换
	void ThresholdWindow(int bTop, int bBottom);
	
	//线性拉伸
	void LinearStrech(CPoint point1,CPoint point2);
	
private:
	//单通道数据线性拉伸
	void LinearStrechForSnglChannel(unsigned char *pImgDataIn,
		unsigned char *pImgDataOut,int imgWidth,int imgHeight,
		CPoint point1,CPoint point2);

};

#endif // !defined(AFX_LBP_H__2B2828F4_58EC_4C41_A4EF_28C665AC9D79__INCLUDED_)
