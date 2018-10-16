#ifndef SIGMOIDLAYER_H
#define SIGMOIDLAYER_H

class SigmoidLayer
{
public:
    SigmoidLayer(int nInputSize);
    ~SigmoidLayer();
    void forward(float *pfInput);
    float *GetOutput();

private:
    int m_nInputSize;
    float *m_pfOutput;
};

#endif
