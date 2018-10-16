#ifndef RELULAYER_H
#define RELULAYER_H

class ReluLayer
{
public:
    ReluLayer(int nInputSize);
    ~ReluLayer();
    void forward(float *pfInput);
    float *GetOutput();

private:
    int m_nInputSize;
    float *m_pfOutput;
};

#endif