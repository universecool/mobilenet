#define _CRT_SECURE_NO_WARNINGS

#include "fcLayer.h"
#include <cmath>
#include <cstring> 
//#include <ctime>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

//FcLayer::FcLayer(const char *pcWname, const char *pcBname, int nInputSize, int nOutputSize, int nRelubool): 
                    //m_pcWname(pcWname), m_pcBname(pcBname), m_nInputSize(nInputSize), m_nOutputSize(nOutputSize), m_nRelubool(nRelubool)
FcLayer::FcLayer(const char *pcWname, const char *pcBname, int nInputSize, int nOutputSize) :
    m_nInputSize(nInputSize), m_nOutputSize(nOutputSize)
    //m_pcWname(pcWname), m_pcBname(pcBname), m_nInputSize(nInputSize), m_nOutputSize(nOutputSize)
{
    m_nWeightSize = m_nInputSize * m_nOutputSize;
    m_pfWeight = new float[m_nWeightSize];
    m_pfBias = new float[m_nOutputSize];
    m_pfOutput = new float[m_nOutputSize];
	ReadFcWb(pcWname, pcBname);
}

FcLayer::~FcLayer()
{
    delete[] m_pfOutput;
    delete[] m_pfWeight;
    delete[] m_pfBias;
}

void FcLayer::forward(float *pfInput)
{
    for(int i = 0; i < m_nOutputSize; i++)
    {
        float fSum = 0.0;
        int weight_index;
        for(int j = 0; j < m_nInputSize; j++)
        {
            weight_index = i * m_nInputSize + j;
            fSum += m_pfWeight[weight_index] * pfInput[j];
        }
        fSum += m_pfBias[i];

        /*
		if (m_nRelubool == 1)
			{
				m_pfOutput[i] = fSum > 0 ? fSum : 0;
				//cout << m_pcWname << endl;
			}
		else
			{
				m_pfOutput[i] = 1 / (1 + exp(-fSum));
				//cout << m_pcWname << endl;
			}
        */
        m_pfOutput[i] = fSum;
    }
}

void FcLayer::ReadFcWb(const char *pcWname, const char *pcBname)
{
    int nWsize, nBsize, nWreadsize, nBreadsize;
    FILE *pW, *pB;
    pW = fopen(pcWname, "rb");
    pB = fopen(pcBname, "rb");

    assert((pW != NULL) && (pB != NULL));

    nWsize = m_nWeightSize;
    nBsize = m_nOutputSize;

    nWreadsize = fread(m_pfWeight, sizeof(float), nWsize, pW);
	assert(nWreadsize <= nWsize);

    fclose(pW);
    cout << "w: " << nWreadsize << ", ";

    nBreadsize = fread(m_pfBias, sizeof(float), nBsize, pB);
    fclose(pB);
    assert(nBreadsize <= nBsize);
    cout << "b: " << nBreadsize << endl;
}

float *FcLayer::GetOutput()
{
    return m_pfOutput;

}

int FcLayer::GetOutputSize()
{
	return m_nOutputSize;
}