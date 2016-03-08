// FaceDetect.cpp: implementation of the FaceDetect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "FaceDetect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FaceDetect::FaceDetect()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

FaceDetect::FaceDetect(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData1,unsigned char *pImgData2):
ImageDib(size, nBitCount, lpColorTable, pImgData1)
{

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0

	m_pImgDataIn1=pImgData1;//m_pImgData;
	m_pImgDataIn2=pImgData2;
	
	Cb_Mean=117.4361;
	Cr_Mean=156.5599;
	Cov00=160.1301;
	Cov01=12.1430;
	Cov10=12.1430;
	Cov11=299.4574;
}

FaceDetect::~FaceDetect()
{

}

CSize FaceDetect::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}

void FaceDetect::CalMedFl(double **s, int w, int h, int n)
{
	
	int i,j;
	double **temp;
	temp = new double*[h+2*(int)(n/2)];
	for(i=0;i<h+2*(int)(n/2);i++)
		temp[i] = new double[w+2*(int)(n/2)];
	for(i=0;i<w+2*(int)(n/2);i++)
		for(j=0;j<h+2*(int)(n/2);j++)
			temp[j][i] = 0.0;
		
		for(i=0;i<h;i++)
			for(j=0;j<w;j++)
				temp[i+(int)(n/2)][j+(int)(n/2)]=s[i][j];
			for(i=0;i<h;i++)
				for(j=0;j<w;j++)
				{
					s[i][j]=0.0;
					for(int r=0;r<n;r++)
						for(int c=0;c<n;c++)
							s[i][j]+=temp[i+r][j+c];
						s[i][j]/=n*n;
				}
				if(temp!=NULL)
				{
					for(i=0;i<h+2;i++)
						if(temp[i]!=NULL)
							delete temp[i];
						delete temp;
				}
				
}

void FaceDetect::CalSim()
{
	//���Ҷ�ͼ��,�򷵻�
	if(m_nBitCount==8) return;

	//�ͷžɵ����ͼ�����ݼ���ɫ������
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//��ֵ����,ÿ����λ��Ϊ8����
	m_nBitCountOut=8;

	//��ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������,���ɻҶ�ͼ�����ɫ��
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//����ͼ��ÿ�����ֽ���,��ɫͼ��Ϊ3�ֽ�/����
	int pixelByteIn=3;
	
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//���ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//�������ͼ��λͼ���ݻ�����
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//ѭ������,ͼ�������
	int i,j,k,j1,j2,flag;
	char c_t1[4];

	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			*(m_pImgDataOut+i*lineByteOut+j)=255;
		}
	}

	m_pSimArray = new double*[m_imgHeight];
	for(i=0;i<m_imgHeight;i++)
		m_pSimArray[i] = new double[m_imgWidth];

	for(i=0;i<m_imgHeight;i++)
		for (j=0;j<m_imgWidth;j++){
			for(k=0;k<3;k++){
				c_t1[k]=*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+k);
			}
			
			int C_b=(int)c_t1[0]&255;
			int C_g=(int)c_t1[1]&255;
			int C_r=(int)c_t1[2]&255;

			double Cb=(128-37.797*C_r/255-74.203*C_g/255+112*C_b/255);
			double Cr=(128+112*C_r/255-93.786*C_g/255-18.214*C_b/255);
			
			double tt =(Cb-Cb_Mean)*((Cb-Cb_Mean)*Cov11-(Cr-Cr_Mean)*Cov10)+(Cr-Cr_Mean)*(-(Cb-Cb_Mean)*Cov01+(Cr-Cr_Mean)*Cov00);
			tt =(-0.5*tt)/(Cov00*Cov11-Cov01*Cov10);
			m_pSimArray[i][j]=exp(tt);
		}
		CalMedFl(m_pSimArray,m_imgWidth, m_imgHeight,9);
		
		double max=0.0;

		for(i=0;i<m_imgHeight;i++)
			for (j=0;j<m_imgWidth;j++){
				if(m_pSimArray[i][j]>max)
					max=m_pSimArray[i][j];
		}
		for( i=0;i<m_imgHeight;i++)
			for (j=0;j<m_imgWidth;j++){
				m_pSimArray[i][j]= m_pSimArray[i][j]/max;
		}

		for(i=0;i<m_imgHeight;i++)
			for(j=0;j<m_imgWidth;j++){
				*(m_pImgDataOut+i*lineByteOut+j)=(int)(m_pSimArray[i][j]*255);
		}
}

void FaceDetect::CalSBound(int top,int bottom,int left,int right)
{

	//���Ҷ�ͼ��,�򷵻�
	if(m_nBitCount==8) return;

	//�ͷžɵ����ͼ�����ݼ���ɫ������
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//��ֵ����,ÿ����λ��Ϊ8����
	m_nBitCountOut=8;

	//��ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������,���ɻҶ�ͼ�����ɫ��
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//����ͼ��ÿ�����ֽ���,��ɫͼ��Ϊ3�ֽ�/����
	int pixelByteIn=3;
	
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//���ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//�������ͼ��λͼ���ݻ�����
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];


	//ѭ������,ͼ�������
	int i,j,k,l,j1,j2,flag;
		
	double **result;					 
	result = new double*[m_imgHeight];
	for(l=0 ; l<m_imgHeight; l++){
		result[l] = new double[m_imgWidth];
		for(j=0; j<m_imgWidth; j++)
			result[l][j] = *(m_pImgDataIn1+l*lineByteIn+j*pixelByteIn+2);
	}
	
	for(i=0; i<m_imgHeight; i++)
		for(j=0; j<m_imgWidth; j++){
			double r,g,temp;
			temp = *(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn)+
				*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+1)+
				*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+2);
			r = (double)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+2)/temp;
			g = (double)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+1)/temp;
			if(g<0.398 && g > 0.246 && r<0.664 && r>0.233 && r>g && g>=0.5*(1-r)){
				*(m_pImgDataOut+i*lineByteOut+j)=255;
			}
			else	*(m_pImgDataOut+i*lineByteOut+j)=0;
	}
		
	for(i=top+2; i<bottom-2; i++)
		for(j=left+2; j<right-2; j++){
			result[i][j] =  
				(0-2.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-2)*lineByteOut+j-2)) + 
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-2)*lineByteOut+j-1)) + 
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-2)*lineByteOut+j)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-2)*lineByteOut+j+1)) +
				(0-2.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-2)*lineByteOut+j+2)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-1)*lineByteOut+j-2)) + 
				(8.0/24.0)  *((unsigned char)*(m_pImgDataOut+(i-1)*lineByteOut+j)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i-1)*lineByteOut+j+2)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+i*lineByteOut+j-2)) + 
				(8.0/24.0)  *((unsigned char)*(m_pImgDataOut+i*lineByteOut+j-1)) + 
				(1.0)       *((unsigned char)*(m_pImgDataOut+i*lineByteOut+j)) +
				(8.0/24.0)  *((unsigned char)*(m_pImgDataOut+i*lineByteOut+j+1)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+i*lineByteOut+j+2)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+1)*lineByteOut+j-2)) + 
				(8.0/24.0)  *((unsigned char)*(m_pImgDataOut+(i+1)*lineByteOut+j)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+1)*lineByteOut+j+2)) +
				(0-2.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+2)*lineByteOut+j-2)) + 
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+2)*lineByteOut+j-1)) + 
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+2)*lineByteOut+j)) +
				(0-4.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+2)*lineByteOut+j+1)) +
				(0-2.0/24.0)*((unsigned char)*(m_pImgDataOut+(i+2)*lineByteOut+j+2));
	}
			
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			*(m_pImgDataOut+i*lineByteOut+j)=255;
		}
	}

	for(i=top+1; i<bottom-1; i++)
		for(j=left+1; j<right-1; j++){
			int positive = 0;   
			int negtive  = 0;
			for(int m=-1;m<=1;m++)
				for(int n=-1;n<=1;n++)
					if(m!=0 || n!=0){
						if(result[i+m][j+n]<-5)negtive++;
						if(result[i+m][j+n]>=5)positive++;
					}
					if(positive>2 && negtive>2){
						*(m_pImgDataOut+i*lineByteOut+j) = 0;
					}
	}
				
	if(result!=NULL){
		for (int i=0 ;i<m_imgHeight;i++)
			if(result[i]!=NULL) delete result[i];
			delete result;
	}
	

}
