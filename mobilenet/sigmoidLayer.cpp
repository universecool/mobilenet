#define _CRT_SECURE_NO_WARNINGS

#include "sigmoidLayer.h"
#include <cmath>

SigmoidLayer::SigmoidLayer(int nInputSize) : m_nInputSize(nInputSize)
{
    m_pfOutput = new float[m_nInputSize];
}

SigmoidLayer::~SigmoidLayer()
{
    delete[] m_pfOutput;
}

void SigmoidLayer::forward(float *pfInput)
{
    for (int i = 0; i < m_nInputSize; i++)
    {
        m_pfOutput[i] = 1 / (1 + exp(-pfInput[i]));
    }
}

float *SigmoidLayer::GetOutput()
{
    return m_pfOutput;
}