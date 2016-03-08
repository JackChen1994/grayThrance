// Light.cpp: implementation of the Light class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo1.h"
#include "Light.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Light::Light()
{
    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}
Light::Light(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
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
	
	
}
Light::~Light()
{

}
CSize Light::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void Light::CalSim()
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

	//��ֵ����,ÿ����λ��Ϊ24����
	m_nBitCountOut=24;

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
	int i,j,k,j1,j2,flag,b=0,g=0,r=0,maxb=0,maxg=0,maxr=0,n;
	char c_t1[4];
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			*(m_pImgDataOut+i*lineByteOut+j)=255;
		}
	}

	

	B = new int*[m_imgHeight];
	G = new int*[m_imgHeight];
	R = new int*[m_imgHeight];
	for(i=0;i<m_imgHeight;i++)
	{
		B[i] = new int[m_imgWidth];
		G[i] = new int[m_imgWidth];
		R[i] = new int[m_imgWidth];
	}

	for(i=0;i<m_imgHeight;i++)
		for (j=0;j<m_imgWidth;j++)
		{
				B[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn);
				G[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+1);
				R[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+2);
		}
    
    for(i=0;i<m_imgHeight;i++)
		for (j=0;j<m_imgWidth;j++)
		{	
			if(B[i][j]>maxb)
				maxb=B[i][j];
			if(G[i][j]>maxg)
				maxg=G[i][j];
			if(R[i][j]>maxr)
				maxr=R[i][j];
		}
		n=CLightMath(maxb,maxg,maxr);
		while(n<100)
		{
			maxb--;
			maxg--;
			maxr--;
			n=CLightMath(maxb,maxg,maxr);
		}

	    	for(i=0;i<m_imgHeight;i++)
				for (j=0;j<m_imgWidth;j++)
				{
					if(B[i][j]/maxb>1)
						B[i][j]=255;
					else
						B[i][j]=255*B[i][j]/maxb;
					if(G[i][j]/maxg>1)
						G[i][j]=255;
					else
						G[i][j]=255*G[i][j]/maxg;
					if(R[i][j]/maxr>1)
						R[i][j]=255;
					else
						R[i][j]=255*R[i][j]/maxr;
				}

	    	for(i=0;i<m_imgHeight;i++)
				for (j=0;j<m_imgWidth;j++)
				{
					*(m_pImgDataOut+i*lineByteOut+j*3)=B[i][j];
					*(m_pImgDataOut+i*lineByteOut+j*3+1)=G[i][j];
					*(m_pImgDataOut+i*lineByteOut+j*3+2)=R[i][j];
				}
}
void Light::CalSBound(int top,int bottom,int left,int right)
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
int Light::CLightMath(int C_b,int C_g,int C_r)
{
	

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
	m_nBitCountOut=24;

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
	int i,j,k,flag,b=0,g=0,r=0,n;
	char c_t1[4];

	

	B = new int*[m_imgHeight];
	G = new int*[m_imgHeight];
	R = new int*[m_imgHeight];
	for(i=0;i<m_imgHeight;i++)
	{
		B[i] = new int[m_imgWidth];
		G[i] = new int[m_imgWidth];
		R[i] = new int[m_imgWidth];
	}

	for(i=0;i<m_imgHeight;i++)
		for (j=0;j<m_imgWidth;j++)
		{
				B[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn);
				G[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+1);
				R[i][j]=(int)*(m_pImgDataIn1+i*lineByteIn+j*pixelByteIn+2);
		}
	for(i=0;i<m_imgHeight;i++)
		for (j=0;j<m_imgWidth;j++)
		{
			if(B[i][j]==C_b)
				b++;
			if(G[i][j]==C_g)
				g++;
			if(R[i][j]==C_r)
				r++;
		}
		n=b+g+r;
		return n;

}