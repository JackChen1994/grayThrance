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
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	
	unsigned char * m_pImgDataIn1;
	unsigned char * m_pImgDataIn2;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;
	int** B;
	int** G;
	int** R;
	
	//double MAXNUM=1e+8			//�������

private:
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;

	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

public:
	void CalSBound(int top,int bottom,int left,int right);
	//���������Ĺ��캯��
	Light();

	//�������Ĺ��캯��
	Light(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData1,unsigned char *pImgData2);

	//��������
	~Light();
	
	void CalSim();

	CSize GetDimensions();
	int CLightMath(int C_b,int C_g,int C_r);
};

#endif // !defined(AFX_LIGHT_H__C1F962E2_0441_443B_A1B0_0FA0AC4D0F58__INCLUDED_)
