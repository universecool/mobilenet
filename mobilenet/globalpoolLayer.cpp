#include "globalpoolLayer.h"
#include <iostream>


GlobalPoolLayer::GlobalPoolLayer(int nOutputNum, int nInputWidth):
                        m_nOutputNum(nOutputNum), m_nInputWidth(nInputWidth), m_nPoolWidth(nInputWidth)
{
    m_nOutputWidth = 1;
    m_nOutputSize = m_nOutputWidth *m_nOutputWidth;
    m_nInputSize = m_nInputWidth * m_nInputWidth;
    
    m_pfOutput = new float [m_nOutputNum * m_nOutputSize];
}

GlobalPoolLayer::~GlobalPoolLayer()
{
    delete[] m_pfOutput;
}

void GlobalPoolLayer::forward(float *pfInput)
{
    for (int nOutmapIndex = 0; nOutmapIndex < m_nOutputNum; nOutmapIndex++)
    {
        int nInputIndexStart, nInputIndex, nOutputIndex;
        nOutputIndex = nOutmapIndex * m_nOutputSize;
        nInputIndexStart = nOutmapIndex * m_nInputSize;
        float fSum = 0;
        for (int m = 0; m < m_nPoolWidth; m++)
        {
            for (int n = 0; n<m_nPoolWidth; n++)
            {
                nInputIndex = nInputIndexStart + m * m_nInputWidth + n;
                fSum += pfInput[nInputIndex];
            }
        }

        m_pfOutput[nOutputIndex] = fSum / m_nInputSize;
    }    
}

float *GlobalPoolLayer::GetOutput()
{
    return m_pfOutput;
}