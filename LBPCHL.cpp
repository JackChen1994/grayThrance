#include "stdio.h"
#include "stdafx.h"
#include "demo1.h"
#include "LBP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LBP::LBP()
{
    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}
LBP::LBP(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		 unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}
LBP::~LBP()
{
//�ͷ����ͼ��λͼ���ݻ�����
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//�ͷ����ͼ����ɫ��
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}

void LBP::CalSim()
{
    if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}		
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
		
	//���ͼ���ÿ����λ������ɫ����		
	m_nBitCountOut=m_nBitCount;		
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
				
	//�������ͼ����ɫ����������������ͼ����ɫ���������ͼ����ɫ����		
	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];		
	memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
				
	//���ͼ��Ŀ��,������ͼ�����		
	m_imgWidthOut=m_imgWidth;	
	m_imgHeightOut=m_imgHeight;
		
				
	//ͼ��ÿ��������ռ�ֽ���������ͼ�������ͼ��ÿ��������ռ�ֽ������	
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
			
	//�������ͼ��λͼ���ݻ�����	
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
			
	//ѭ��������ͼ�������	
	int i,j,k,D1,sum,ave;
	int s_3_3[9];
	double D;

	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			*(m_pImgDataOut+i*lineByte+j)=0;
		}
	}


	for(i=1;i<m_imgHeight-1;i++){
		for(j=1;j<m_imgWidth-1;j++){
			s_3_3[0]=*(m_pImgData+(i-1)*lineByte+(j-1));
			s_3_3[1]=*(m_pImgData+(i-1)*lineByte+j);
			s_3_3[2]=*(m_pImgData+(i-1)*lineByte+j+1);

			s_3_3[3]=*(m_pImgData+i*lineByte+(j+1));
			s_3_3[4]=*(m_pImgData+(i+1)*lineByte+(j+1));
			s_3_3[5]=*(m_pImgData+(i+1)*lineByte+j);

			s_3_3[6]=*(m_pImgData+(i+1)*lineByte+(j-1));
			s_3_3[7]=*(m_pImgData+i*lineByte+(j-1));
			s_3_3[8]=*(m_pImgData+i*lineByte+j);

			sum=0;

			for(k=0;k<9;k++)								//��ֵ
				sum=s_3_3[k]+sum;
			ave=sum/9;

			D1=0;

			for(k=0;k<9;k++)								//����
				D1=D1+pow(s_3_3[k]-ave,2);
			D=sqrt(D1/9);

			for(k=0;k<8;k++)
				if(abs(s_3_3[k]-ave)>D)
					*(m_pImgDataOut+i*lineByte+j)+=pow(2,7-k);
		}
	}
}