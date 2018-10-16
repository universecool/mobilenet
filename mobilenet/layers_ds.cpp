#include "layers_ds.h"

Layers_Ds::Layers_Ds(int nInputNum, int nOutputNum, int nInputWidth, int nStride, const char *pcConvDwWname, const char *pcDwBnMname, const char *pcDwBnVname, const char *pcDwBnFname, const char *pcDwBnBname,
    const char *pcConvSepWname, const char *pcSepBnMname, const char *pcSepBnVname, const char *pcSepBnFname, const char *pcSepBnBname)
{
    m_ConvlayerDw = new ConvLayer(pcConvDwWname, nInputNum, nInputNum, nInputWidth, 3, 1, nStride, nInputNum);
    m_ConvDwBn = new BatchNormalLayer(pcDwBnMname, pcDwBnVname, pcDwBnFname, pcDwBnBname, nInputNum, nInputWidth / nStride);
    m_RelulayerDw = new ReluLayer(m_ConvDwBn->GetOutputSize());

    m_ConvlayerSep = new ConvLayer(pcConvSepWname, nInputNum, nOutputNum, nInputWidth / nStride, 1, 0);
    m_ConvSepBn = new BatchNormalLayer(pcSepBnMname, pcSepBnVname, pcSepBnFname, pcSepBnBname, nOutputNum, nInputWidth / nStride);
    m_RelulayerSep = new ReluLayer(m_ConvSepBn->GetOutputSize());
}

Layers_Ds::~Layers_Ds()
{
    delete m_ConvlayerDw;
    delete m_ConvDwBn;
    delete m_RelulayerDw;
    delete m_ConvlayerSep;
    delete m_ConvSepBn;
    delete m_RelulayerSep;
}

void Layers_Ds::forward(float *pfInput)
{
    m_ConvlayerDw->forward(pfInput);
    m_ConvDwBn->forward(m_ConvlayerDw->GetOutput());
    m_RelulayerDw->forward(m_ConvDwBn->GetOutput());

    m_ConvlayerSep->forward(m_RelulayerDw->GetOutput());
    m_ConvSepBn->forward(m_ConvlayerSep->GetOutput());
    m_RelulayerSep->forward(m_ConvSepBn->GetOutput());
}

float *Layers_Ds::GetOutput()
{
    return m_RelulayerSep->GetOutput();
}