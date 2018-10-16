#include "Network.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

Network::Network()
{

	cout << "Initializing Network..." << endl;

	m_Readdata = new ReadData("..\\wbdata\\means", 224, 224, 3);

    m_Layers_bn = new Layers_Bn(3, 32, 224, 2, "..\\wbdata\\conv1.weights", "..\\wbdata\\conv1_bn.mean", "..\\wbdata\\conv1_bn.variance", "..\\wbdata\\conv1_bn.filler",
        "..\\wbdata\\conv1_bn.bias_filler");

    m_Layers_ds2_1 = new Layers_Ds(32, 64, 112, 1, "..\\wbdata\\conv2_1_dw.weights", "..\\wbdata\\conv2_1_bn_dw.mean", "..\\wbdata\\conv2_1_bn_dw.variance", "..\\wbdata\\conv2_1_bn_dw.filler",
        "..\\wbdata\\conv2_1_bn_dw.bias_filler", "..\\wbdata\\conv2_1_sep.weights", "..\\wbdata\\conv2_1_bn_sep.mean", "..\\wbdata\\conv2_1_bn_sep.variance", "..\\wbdata\\conv2_1_bn_sep.filler",
        "..\\wbdata\\conv2_1_bn_sep.bias_filler");

    m_Layers_ds2_2 = new Layers_Ds(64, 128, 112, 2, "..\\wbdata\\conv2_2_dw.weights", "..\\wbdata\\conv2_2_bn_dw.mean", "..\\wbdata\\conv2_2_bn_dw.variance", "..\\wbdata\\conv2_2_bn_dw.filler",
        "..\\wbdata\\conv2_2_bn_dw.bias_filler", "..\\wbdata\\conv2_2_sep.weights", "..\\wbdata\\conv2_2_bn_sep.mean", "..\\wbdata\\conv2_2_bn_sep.variance", "..\\wbdata\\conv2_2_bn_sep.filler",
        "..\\wbdata\\conv2_2_bn_sep.bias_filler");

    m_Layers_ds3_1 = new Layers_Ds(128, 128, 56, 1, "..\\wbdata\\conv3_1_dw.weights", "..\\wbdata\\conv3_1_bn_dw.mean", "..\\wbdata\\conv3_1_bn_dw.variance", "..\\wbdata\\conv3_1_bn_dw.filler",
        "..\\wbdata\\conv3_1_bn_dw.bias_filler", "..\\wbdata\\conv3_1_sep.weights", "..\\wbdata\\conv3_1_bn_sep.mean", "..\\wbdata\\conv3_1_bn_sep.variance", "..\\wbdata\\conv3_1_bn_sep.filler",
        "..\\wbdata\\conv3_1_bn_sep.bias_filler");

    m_Layers_ds3_2 = new Layers_Ds(128, 256, 56, 2, "..\\wbdata\\conv3_2_dw.weights", "..\\wbdata\\conv3_2_bn_dw.mean", "..\\wbdata\\conv3_2_bn_dw.variance", "..\\wbdata\\conv3_2_bn_dw.filler",
        "..\\wbdata\\conv3_2_bn_dw.bias_filler", "..\\wbdata\\conv3_2_sep.weights", "..\\wbdata\\conv3_2_bn_sep.mean", "..\\wbdata\\conv3_2_bn_sep.variance", "..\\wbdata\\conv3_2_bn_sep.filler",
        "..\\wbdata\\conv3_2_bn_sep.bias_filler");

    m_Layers_ds4_1 = new Layers_Ds(256, 256, 28, 1, "..\\wbdata\\conv4_1_dw.weights", "..\\wbdata\\conv4_1_bn_dw.mean", "..\\wbdata\\conv4_1_bn_dw.variance", "..\\wbdata\\conv4_1_bn_dw.filler",
        "..\\wbdata\\conv4_1_bn_dw.bias_filler", "..\\wbdata\\conv4_1_sep.weights", "..\\wbdata\\conv4_1_bn_sep.mean", "..\\wbdata\\conv4_1_bn_sep.variance", "..\\wbdata\\conv4_1_bn_sep.filler",
        "..\\wbdata\\conv4_1_bn_sep.bias_filler");

    m_Layers_ds4_2 = new Layers_Ds(256, 512, 28, 2, "..\\wbdata\\conv4_2_dw.weights", "..\\wbdata\\conv4_2_bn_dw.mean", "..\\wbdata\\conv4_2_bn_dw.variance", "..\\wbdata\\conv4_2_bn_dw.filler",
        "..\\wbdata\\conv4_2_bn_dw.bias_filler", "..\\wbdata\\conv4_2_sep.weights", "..\\wbdata\\conv4_2_bn_sep.mean", "..\\wbdata\\conv4_2_bn_sep.variance", "..\\wbdata\\conv4_2_bn_sep.filler",
        "..\\wbdata\\conv4_2_bn_sep.bias_filler");

    m_Layers_ds5_1 = new Layers_Ds(512, 512, 14, 1, "..\\wbdata\\conv5_1_dw.weights", "..\\wbdata\\conv5_1_bn_dw.mean", "..\\wbdata\\conv5_1_bn_dw.variance", "..\\wbdata\\conv5_1_bn_dw.filler",
        "..\\wbdata\\conv5_1_bn_dw.bias_filler", "..\\wbdata\\conv5_1_sep.weights", "..\\wbdata\\conv5_1_bn_sep.mean", "..\\wbdata\\conv5_1_bn_sep.variance", "..\\wbdata\\conv5_1_bn_sep.filler",
        "..\\wbdata\\conv5_1_bn_sep.bias_filler");

    m_Layers_ds5_2 = new Layers_Ds(512, 512, 14, 1, "..\\wbdata\\conv5_2_dw.weights", "..\\wbdata\\conv5_2_bn_dw.mean", "..\\wbdata\\conv5_2_bn_dw.variance", "..\\wbdata\\conv5_2_bn_dw.filler",
        "..\\wbdata\\conv5_2_bn_dw.bias_filler", "..\\wbdata\\conv5_2_sep.weights", "..\\wbdata\\conv5_2_bn_sep.mean", "..\\wbdata\\conv5_2_bn_sep.variance", "..\\wbdata\\conv5_2_bn_sep.filler",
        "..\\wbdata\\conv5_2_bn_sep.bias_filler");

    m_Layers_ds5_3 = new Layers_Ds(512, 512, 14, 1, "..\\wbdata\\conv5_3_dw.weights", "..\\wbdata\\conv5_3_bn_dw.mean", "..\\wbdata\\conv5_3_bn_dw.variance", "..\\wbdata\\conv5_3_bn_dw.filler",
        "..\\wbdata\\conv5_3_bn_dw.bias_filler", "..\\wbdata\\conv5_3_sep.weights", "..\\wbdata\\conv5_3_bn_sep.mean", "..\\wbdata\\conv5_3_bn_sep.variance", "..\\wbdata\\conv5_3_bn_sep.filler",
        "..\\wbdata\\conv5_3_bn_sep.bias_filler");

    m_Layers_ds5_4 = new Layers_Ds(512, 512, 14, 1, "..\\wbdata\\conv5_4_dw.weights", "..\\wbdata\\conv5_4_bn_dw.mean", "..\\wbdata\\conv5_4_bn_dw.variance", "..\\wbdata\\conv5_4_bn_dw.filler",
        "..\\wbdata\\conv5_4_bn_dw.bias_filler", "..\\wbdata\\conv5_4_sep.weights", "..\\wbdata\\conv5_4_bn_sep.mean", "..\\wbdata\\conv5_4_bn_sep.variance", "..\\wbdata\\conv5_4_bn_sep.filler",
        "..\\wbdata\\conv5_4_bn_sep.bias_filler");

    m_Layers_ds5_5 = new Layers_Ds(512, 512, 14, 1, "..\\wbdata\\conv5_5_dw.weights", "..\\wbdata\\conv5_5_bn_dw.mean", "..\\wbdata\\conv5_5_bn_dw.variance", "..\\wbdata\\conv5_5_bn_dw.filler",
        "..\\wbdata\\conv5_5_bn_dw.bias_filler", "..\\wbdata\\conv5_5_sep.weights", "..\\wbdata\\conv5_5_bn_sep.mean", "..\\wbdata\\conv5_5_bn_sep.variance", "..\\wbdata\\conv5_5_bn_sep.filler",
        "..\\wbdata\\conv5_5_bn_sep.bias_filler");

    m_Layers_ds5_6 = new Layers_Ds(512, 1024, 14, 2, "..\\wbdata\\conv5_6_dw.weights", "..\\wbdata\\conv5_6_bn_dw.mean", "..\\wbdata\\conv5_6_bn_dw.variance", "..\\wbdata\\conv5_6_bn_dw.filler",
        "..\\wbdata\\conv5_6_bn_dw.bias_filler", "..\\wbdata\\conv5_6_sep.weights", "..\\wbdata\\conv5_6_bn_sep.mean", "..\\wbdata\\conv5_6_bn_sep.variance", "..\\wbdata\\conv5_6_bn_sep.filler",
        "..\\wbdata\\conv5_6_bn_sep.bias_filler");

    m_Layers_ds6 = new Layers_Ds(1024, 1024, 7, 1, "..\\wbdata\\conv6_dw.weights", "..\\wbdata\\conv6_bn_dw.mean", "..\\wbdata\\conv6_bn_dw.variance", "..\\wbdata\\conv6_bn_dw.filler",
        "..\\wbdata\\conv6_bn_dw.bias_filler", "..\\wbdata\\conv6_sep.weights", "..\\wbdata\\conv6_bn_sep.mean", "..\\wbdata\\conv6_bn_sep.variance", "..\\wbdata\\conv6_bn_sep.filler",
        "..\\wbdata\\conv6_bn_sep.bias_filler");

    m_Poollayer6 = new GlobalPoolLayer(1024, 7);

    //m_Convlayer7 = new ConvLayer("..\\wbdata\\fc7.weights", 1024, 12, 1, 1, 0, 1, 1, "..\\wbdata\\fc7.biases");
    m_Fclayer7 = new FcLayer("..\\wbdata\\fc7.weights", "..\\wbdata\\fc7.biases", 1024, 12);

    m_Sigmoidlayer8 = new SigmoidLayer(12);

	
	m_vcClass.push_back("室内");
	m_vcClass.push_back("人像");
	m_vcClass.push_back("LDR");
	m_vcClass.push_back("绿植");
	m_vcClass.push_back("商场");
	m_vcClass.push_back("沙滩");
	m_vcClass.push_back("逆光");
	m_vcClass.push_back("日落");
	m_vcClass.push_back("蓝天");
	m_vcClass.push_back("雪景");
	m_vcClass.push_back("夜景");
	m_vcClass.push_back("文本");

	cout << "Initializing Done..." << endl;
	cout << endl;

}


Network::~Network()
{
	delete m_Readdata;
    delete m_Layers_bn;
    delete m_Layers_ds1;
    delete m_Layers_ds2_1;
    delete m_Layers_ds2_2;
    delete m_Layers_ds3_1;
    delete m_Layers_ds3_2;
    delete m_Layers_ds4_1;
    delete m_Layers_ds4_2;
    delete m_Layers_ds5_1;
    delete m_Layers_ds5_2;
    delete m_Layers_ds5_3;
    delete m_Layers_ds5_4;
    delete m_Layers_ds5_5;
    delete m_Layers_ds5_6;
    delete m_Layers_ds6;
    delete m_Poollayer6;
    //delete m_Convlayer7;
    delete m_Fclayer7;
    delete m_Sigmoidlayer8;
}


float *Network::Forward(const char *pcName)
{

    m_Layers_bn->forward(m_Readdata->ReadInput(pcName));

    m_Layers_ds2_1->forward(m_Layers_bn->GetOutput());
    m_Layers_ds2_2->forward(m_Layers_ds2_1->GetOutput());
    
    m_Layers_ds3_1->forward(m_Layers_ds2_2->GetOutput());
    m_Layers_ds3_2->forward(m_Layers_ds3_1->GetOutput());

    m_Layers_ds4_1->forward(m_Layers_ds3_2->GetOutput());
    m_Layers_ds4_2->forward(m_Layers_ds4_1->GetOutput());

    m_Layers_ds5_1->forward(m_Layers_ds4_2->GetOutput());
    m_Layers_ds5_2->forward(m_Layers_ds5_1->GetOutput());
    m_Layers_ds5_3->forward(m_Layers_ds5_2->GetOutput());
    m_Layers_ds5_4->forward(m_Layers_ds5_3->GetOutput());
    m_Layers_ds5_5->forward(m_Layers_ds5_4->GetOutput());
    m_Layers_ds5_6->forward(m_Layers_ds5_5->GetOutput());

    m_Layers_ds6->forward(m_Layers_ds5_6->GetOutput());

    m_Poollayer6->forward(m_Layers_ds6->GetOutput());

    //m_Convlayer7->forward(m_Poollayer6->GetOutput());
    m_Fclayer7->forward(m_Poollayer6->GetOutput());

    //m_Sigmoidlayer8->forward(m_Convlayer7->GetOutput());
    m_Sigmoidlayer8->forward(m_Fclayer7->GetOutput());

    float *pfOutput = m_Sigmoidlayer8->GetOutput();
	vector <int> argmax;
	vector <float> Max;

    //int nOutputSize = m_Convlayer7->GetOutputSize();
    int nOutputSize = m_Fclayer7->GetOutputSize();
	for (int i = 0; i<nOutputSize; i++)
	{

		if (pfOutput[i] > 0.5)
		{
			argmax.push_back(i);
			Max.push_back(pfOutput[i]);
		}
	}
	cout << endl;
	for (int i = 0; i < argmax.size(); i++)
	{
		cout << Max[i] << ": " << argmax[i] << ": " << m_vcClass[argmax[i]] << endl;
	}
	cout << endl;
    
    return pfOutput;
}
