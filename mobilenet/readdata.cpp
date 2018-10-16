#include "readdata.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include <cassert>
#include <fstream>

using namespace std;

ReadData::ReadData(const char *pcMean, int nInputWidth, int nInputHeight, int nInputChannel):
			m_nInputWidth(nInputWidth), m_nInputHeight(nInputHeight), m_nInputChannel(nInputChannel)
{
	m_nImageSize = nInputWidth * nInputHeight;
	m_nInputSize = nInputWidth * nInputHeight * nInputChannel;
	m_pfInputData = new float[m_nInputSize];
	m_pfMean = new float[m_nInputSize];
    ReadMean(pcMean);
}

ReadData::~ReadData()
{
	delete[] m_pfInputData;
	delete[] m_pfMean;
}

float *ReadData::ReadInput(const char *pcName)
{
	cout << "Reading Picture: " << pcName << "..." << endl;

	const char *pstrImageName = pcName;


	CvSize czSize;
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;
	czSize.width = m_nInputWidth;
	czSize.height = m_nInputHeight;

	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_LINEAR);

	uchar *pucData = (uchar *)pDstImage->imageData;
	int nStep = pDstImage->widthStep / sizeof(uchar);
	int nChannel = pDstImage->nChannels;
	int nOutputIndex = 0;

	for(int i = 0; i < pDstImage->height; i++)
	{
		for (int j = 0; j < pDstImage->width; j++)
		{
			nOutputIndex = i * m_nInputWidth + j;
			m_pfInputData[nOutputIndex] = (float)pucData[i * nStep + j * nChannel + 0] - m_pfMean[nOutputIndex];
			m_pfInputData[nOutputIndex + m_nImageSize] = (float)pucData[i * nStep + j * nChannel + 1] - m_pfMean[nOutputIndex + m_nImageSize];
			m_pfInputData[nOutputIndex + 2 * m_nImageSize] = (float)pucData[i * nStep + j * nChannel + 2] - m_pfMean[nOutputIndex + 2 * m_nImageSize];
		}
	}
	cout << "Reading Picture Done..." << endl;

	return m_pfInputData;
}

void ReadData::ReadMean(const char *pcMean)
{
	int nMsize, nMreadsize;
	FILE *pM;
    pM = fopen(pcMean, "rb");

	assert(pM != NULL);

	nMsize = m_nInputSize;

	nMreadsize = fread(m_pfMean, sizeof(float), nMsize, pM);

	fclose(pM);
}