#ifndef BATCHNORMAL_H
#define BATCHNORMAL_H

class BatchNormalLayer
{
public:
    BatchNormalLayer(const char *pcMname, const char *pcVname, const char *pcFname, const char *pcBname, int nInputNum, int nInputWidth);
    ~BatchNormalLayer();
    void forward(float *pfInput);
    float *GetOutput();
    int GetOutputSize();
    void ReadParam(const char *pcMname, const char *pcVname, const char *pcFname, const char *pcBname);

private:
    float m_fScale;
    int m_nInputNum, m_nInputWidth, m_nInputSize;
    float *m_pfMean, *m_pfVar, *m_pfFiller, *m_pfBias, *m_pfOutput;

};

#endif
