#ifndef LAYERS_DS_H
#define LAYERS_DS_H

#include "readdata.h"
#include "convLayer.h"
#include "globalpoolLayer.h"
#include "batchnormalLayer.h"
#include "reluLayer.h"
#include "sigmoidLayer.h"
#include <vector>
#include <iostream>
#include <string>

class Layers_Ds
{
public:
    Layers_Ds::Layers_Ds(int nInputNum, int nOutputNum, int nInputWidth, int nStride, const char *pcConvDwWname, const char *pcDwBnMname, const char *pcDwBnVname, const char *pcDwBnFname, const char *pcDwBnBname,
        const char *pcConvSepWname, const char *pcSepBnMname, const char *pcSepBnVname, const char *pcSepBnFname, const char *pcSepBnBname);
    ~Layers_Ds();
    void forward(float *pfInput);
    float *GetOutput();

private:
    float *m_nOutput;
    ConvLayer *m_ConvlayerDw, *m_ConvlayerSep;
    BatchNormalLayer *m_ConvDwBn, *m_ConvSepBn;
    ReluLayer *m_RelulayerDw, *m_RelulayerSep;
    //LinearQuantLayer *m_Linearquantlayer1, *m_Linearquantlayer2, *m_Linearquantlayer3, *m_Linearquantlayer4,
};


#endif