#define _CRT_SECURE_NO_WARNINGS

#include "convLayer.h"
#include <fstream>
#include <cassert>
#include <iostream>

using namespace std;

ConvLayer::ConvLayer(const char *pcWname, int nInputNum, int nOutputNum, int nInputWidth, int nKernelWidth, int nPad, int nStride, int nGroup, const char *pcBname) :
    m_nInputNum(nInputNum), m_nOutputNum(nOutputNum), m_nInputWidth(nInputWidth),
    m_nKernelWidth(nKernelWidth), m_nPad(nPad), m_nStride(nStride), m_nGroup(nGroup), m_pcBname(pcBname)
{
    m_nKernelSize = m_nKernelWidth * m_nKernelWidth;
    m_nInputSize = m_nInputWidth * m_nInputWidth;
    m_nInputPadWidth = m_nInputWidth + 2 * m_nPad;
    m_nInputPadSize = m_nInputPadWidth * m_nInputPadWidth;
    m_nOutputWidth = int((m_nInputPadWidth - m_nKernelWidth) / m_nStride + 1);
    m_nOutputSize = m_nOutputWidth * m_nOutputWidth;
    
	m_pfInputPad = new float[m_nInputNum * m_nInputPadWidth * m_nInputPadWidth];

    m_nInputGroupNum = m_nInputNum / m_nGroup;
    m_nOutputGroupNum = m_nOutputNum / m_nGroup;

    m_pfWeight = new float[m_nOutputNum * m_nInputGroupNum * m_nKernelSize];

    if (m_pcBname != NULL)
        m_pfBias = new float[m_nOutputNum];
    m_pfOutput = new float[m_nOutputNum * m_nOutputSize];

	ReadConvWb(pcWname, pcBname);
}

ConvLayer::~ConvLayer()
{
    delete[] m_pfOutput;
    if (m_pcBname != NULL)
        delete[] m_pfBias;
    delete[] m_pfWeight;
	delete[] m_pfInputPad;
}

void ConvLayer::forward(float *pfInput)
{
    Addpad(pfInput);

    for (int g = 0; g < m_nGroup; g++)
    {
        for (int nOutmapIndex = 0; nOutmapIndex < m_nOutputGroupNum; nOutmapIndex++)
        {
            for (int i = 0; i < m_nOutputWidth; i++)
            {
                for (int j = 0; j < m_nOutputWidth; j++)
                {
                    float fSum = 0;
                    int nInputIndex, nOutputIndex, nKernelIndex, nInputIndexStart, nKernelStart;
                    nOutputIndex = g * m_nInputGroupNum * m_nOutputSize + nOutmapIndex * m_nOutputSize + i * m_nOutputWidth + j;
                    for (int k = 0; k < m_nInputGroupNum; k++)
                    {
                        nInputIndexStart = g * m_nInputGroupNum * m_nInputPadSize + k * m_nInputPadSize + (i * m_nStride) * m_nInputPadWidth + (j * m_nStride);
                        nKernelStart = g * m_nOutputGroupNum * m_nKernelSize + nOutmapIndex * m_nInputGroupNum * m_nKernelSize + k * m_nKernelSize;
                        for (int m = 0; m < m_nKernelWidth; m++)
                        {
                            for (int n = 0; n < m_nKernelWidth; n++)
                            {
                                nKernelIndex = nKernelStart + m * m_nKernelWidth + n;
                                nInputIndex = nInputIndexStart + m * m_nInputPadWidth + n;
                                fSum += m_pfInputPad[nInputIndex] * m_pfWeight[nKernelIndex];
                            }
                        }
                    }
                    if (m_pcBname != NULL)
                        fSum += m_pfBias[nOutmapIndex];

                    m_pfOutput[nOutputIndex] = fSum;
                }
            }
        }              
    }
}

void ConvLayer::ReadConvWb(const char *pcWname, const char *pcBname)
{
    int nWsize, nBsize, nWreadsize, nBreadsize;
    FILE *pW, *pB;
    pW = fopen(pcWname, "rb");
    
    assert(pW != NULL);

    nWsize = m_nOutputNum * m_nInputGroupNum * m_nKernelSize;
	nWreadsize = fread(m_pfWeight, sizeof(float), nWsize, pW);
    fclose(pW);
    cout << "w: " << nWreadsize << endl;


    if (pcBname != NULL)
    {
        pB = fopen(pcBname, "rb");
        assert(pB != NULL);
        nBsize = m_nOutputNum;

        nBreadsize = fread(m_pfBias, sizeof(float), nBsize, pB);
        fclose(pB);
        assert(nBreadsize <= nBsize);
        cout << "b: " << nBreadsize << endl;
    }
}

float *ConvLayer::GetOutput()
{
    return m_pfOutput;
}

void ConvLayer::Addpad(float *pfInput)
{
	for (int m = 0; m < m_nInputNum; m++)
	{
		for (int i = 0; i < m_nInputPadWidth; i++)
		{
			for (int j = 0; j < m_nInputPadWidth; j++)
			{
                if ((i < m_nPad) || (i >= m_nInputPadWidth - m_nPad))
                {
                    m_pfInputPad[m * m_nInputPadSize + i * m_nInputPadWidth + j] = 0;
                }
                else if ((j < m_nPad) || (j >= m_nInputPadWidth - m_nPad))
                {
                    m_pfInputPad[m * m_nInputPadSize + i * m_nInputPadWidth + j] = 0;
                }
                else
                {
                    m_pfInputPad[m * m_nInputPadSize + i * m_nInputPadWidth + j] = pfInput[m * m_nInputSize + (i - m_nPad) * m_nInputWidth + (j - m_nPad)];
                }
			}
		}
	}
}

int ConvLayer::GetOutputSize()
{
    return m_nOutputNum * m_nOutputSize;
}