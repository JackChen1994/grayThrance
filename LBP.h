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
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;
	
	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;
	
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
	
public:
	void CalSim();
	//���������Ĺ��캯��
	LBP();
	
	//�������Ĺ��캯��
	LBP(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	
	//��������
	~LBP();
	
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();
	
	//��ֵ��
	void BinaryImage(int threshold=128);

	//��ת
	void RevImage();

    //���ڱ任
	void ThresholdWindow(int bTop, int bBottom);
	
	//��������
	void LinearStrech(CPoint point1,CPoint point2);
	
private:
	//��ͨ��������������
	void LinearStrechForSnglChannel(unsigned char *pImgDataIn,
		unsigned char *pImgDataOut,int imgWidth,int imgHeight,
		CPoint point1,CPoint point2);

};

#endif // !defined(AFX_LBP_H__2B2828F4_58EC_4C41_A4EF_28C665AC9D79__INCLUDED_)
