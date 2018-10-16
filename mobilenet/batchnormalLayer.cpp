#define _CRT_SECURE_NO_WARNINGS

#include "batchnormalLayer.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath> //vs不需要这个，g++需要这个

using namespace std;

BatchNormalLayer::BatchNormalLayer(const char *pcMname, const char *pcVname, const char *pcFname, const char *pcBname, int nInputNum, int nInputWidth) :
    m_nInputNum(nInputNum), m_nInputWidth(nInputWidth)
{
    m_nInputSize = m_nInputWidth * m_nInputWidth;
    m_pfOutput = new float[m_nInputNum * m_nInputSize];
    m_pfMean = new float[m_nInputNum];
    m_pfVar = new float[m_nInputNum];
    m_pfFiller = new float[m_nInputNum];
    m_pfBias = new float[m_nInputNum];
    ReadParam(pcMname, pcVname, pcFname, pcBname);
}

BatchNormalLayer::~BatchNormalLayer()
{
    delete[] m_pfOutput;
    delete[] m_pfMean;
    delete[] m_pfVar;
    delete[] m_pfFiller;
    delete[] m_pfBias;
}

void BatchNormalLayer::forward(float *pfInput) 
{
    for (int i = 0; i < m_nInputNum; i++)
    {
        for (int j = 0; j < m_nInputSize; j++)
        {
            int nOutputIndex = i * m_nInputSize + j;

            m_pfOutput[nOutputIndex] = m_pfFiller[i] * ((pfInput[nOutputIndex] - m_pfMean[i])
                / sqrt(m_pfVar[i] + 1e-5)) + m_pfBias[i];
        }
    }
}

void BatchNormalLayer::ReadParam(const char *pcMname, const char *pcVname, const char *pcFname, const char *pcBname)
{
    int nMsize, nVsize, nFsize, nBsize, nMreadsize, nVreadsize, nFreadsize, nBreadsize;
    FILE *pM, *pV, *pF, *pB;
    pM = fopen(pcMname, "rb");
    pV = fopen(pcVname, "rb");
    pF = fopen(pcFname, "rb");
    pB = fopen(pcBname, "rb");

    assert((pM != NULL) && (pV != NULL) && (pF != NULL) && (pB != NULL));

    nMsize = m_nInputNum;
    nVsize = m_nInputNum;
    nFsize = m_nInputNum;
    nBsize = m_nInputNum;

    nMreadsize = fread(m_pfMean, sizeof(float), nMsize, pM);
    assert(nMreadsize <= nMsize);

    fclose(pM);
    cout << "mean: " << nMreadsize << ", ";

    nVreadsize = fread(m_pfVar, sizeof(float), nVsize, pV);
    assert(nVreadsize <= nVsize);

    cout << "variance: " << nVreadsize << ", ";

    nFreadsize = fread(m_pfFiller, sizeof(float), nFsize, pF);
    assert(nFreadsize <= nFsize);

    cout << "filler: " << nFreadsize << ", ";

    nBreadsize = fread(m_pfBias, sizeof(float), nBsize, pB);
    assert(nBreadsize <= nBsize);

    cout << "bias_filler: " << nBreadsize << endl;

}

float *BatchNormalLayer::GetOutput()
{
    return m_pfOutput;
}

int BatchNormalLayer::GetOutputSize()
{
    return m_nInputNum * m_nInputSize;
}