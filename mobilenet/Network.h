#ifndef NETWORK_H
#define NETWORK_H

#include "readdata.h"
#include "convLayer.h"
#include "globalpoolLayer.h"
#include "batchnormalLayer.h"
#include "reluLayer.h"
#include "fcLayer.h"
#include "sigmoidLayer.h"
#include "layers_bn.h"
#include "layers_ds.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Network
{
public:
    Network();
    ~Network();

    float *Forward(const char *pcName);
    

private:
    float *m_pfOutput;
    float m_dAccuracy;
    int m_nPrediction;
    vector <const char *> m_vcClass;
    const char *m_cClass[10];
    ReadData *m_Readdata;

    Layers_Bn *m_Layers_bn;
    Layers_Ds *m_Layers_ds1, *m_Layers_ds2_1, *m_Layers_ds2_2, *m_Layers_ds3_1, *m_Layers_ds3_2, *m_Layers_ds4_1, *m_Layers_ds4_2,
        *m_Layers_ds5_1, *m_Layers_ds5_2, *m_Layers_ds5_3, *m_Layers_ds5_4, *m_Layers_ds5_5, *m_Layers_ds5_6, *m_Layers_ds6;

    ConvLayer *m_Convlayer7;

    FcLayer *m_Fclayer7;

    GlobalPoolLayer *m_Poollayer6;

    SigmoidLayer *m_Sigmoidlayer8;
};


#endif