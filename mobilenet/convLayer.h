#ifndef CONVLAYER_H
#define CONVLAYER_H
#include <string>

class ConvLayer
{
public:
    ConvLayer(const char *pcWname, int nInputNum, int nOutputNum, int nInputWidth, int nKernelWidth, int nPad, int nStride=1, int nGroup=1, const char *pcBname = NULL);
    ~ConvLayer();
    void forward(float *pfInput);
    float *GetOutput();
    void ReadConvWb(const char *pcWname, const char *pcBname);
	void Addpad(float *pfInput);
    int GetOutputSize();
    
private:
    int m_nInputNum, m_nOutputNum, m_nInputWidth, m_nKernelWidth, m_nPad, m_nStride, m_nGroup, m_nInputGroupNum, m_nOutputGroupNum;
    float *m_pfInputPad, *m_pfOutput;
	float *m_pfWeight;
    float *m_pfBias;
    const char *m_pcBname;
    int m_nInputPadWidth, m_nOutputWidth;
    int m_nKernelSize, m_nInputSize, m_nInputPadSize, m_nOutputSize;
};

#endif