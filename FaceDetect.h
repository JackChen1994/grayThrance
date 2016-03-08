// FaceDetect.h: interface for the FaceDetect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECT_H__2A711F63_7B57_4AA4_BFA9_FDB85C816B35__INCLUDED_)
#define AFX_FACEDETECT_H__2A711F63_7B57_4AA4_BFA9_FDB85C816B35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"
#include "math.h"

class FaceDetect : public ImageDib  
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
	
	double** m_pSimArray;//���ƶȾ���

	double Cb_Mean;
	double Cr_Mean;
	double Cov00;
	double Cov01;
	double Cov10;
	double Cov11;
	
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
	FaceDetect();

	//�������Ĺ��캯��
	FaceDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData1,unsigned char *pImgData2);

	//��������
	~FaceDetect();
	
	void CalMedFl(double **s,int w,int h,int n);
	void CalSim();
	/*double Cbmean;
	double Crmean;
	double Cov[2][2];

	int m_nDIBWidth;//ͼ����
	int m_nDIBHeight;//ͼ��߶�
	RGBQUAD** m_pSource;//ԭʼ����
	double** m_pSimArray;//���ƶȾ���
	BYTE** m_pBinArray;//��ֵ����
	bool m_bSimReady;//�Ƿ��������ƶȾ���
	bool m_bBinReady;//�Ƿ�����ֵ������

	CSim();
	CSim(RGBQUAD **source,int w,int h);*/
	
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();

};

#endif // !defined(AFX_FACEDETECT_H__2A711F63_7B57_4AA4_BFA9_FDB85C816B35__INCLUDED_)
