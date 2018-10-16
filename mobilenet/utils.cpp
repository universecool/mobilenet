#include "utils.h"
#include "Network.h"
#include <string>
#include <fstream>

float Accuracy_1(float *pfPred, int *pnLab, int nclass)
{
    float flag = 0.0;
    for (int i = 0; i < nclass; i++)
    {
        //cout << pfPred[i] << ':' << pnLab[i] << endl;
        if (pfPred[i] >=0.5 && pnLab[i] == 1)
            flag = 1.0;
    }
    return flag;
}

float Accuracy_all(float *pfPred, int *pnLab, int nclass)
{
    float flag = 0.0, nSum = 0.0;
    int *pnPred = new int[nclass];
    for (int i = 0; i < nclass; i++)
    {
        pnPred[i] = 0;
        if (pfPred[i] >=0.5)
            pnPred[i] = 1;

        if (pnPred[i] == pnLab[i])
            nSum += 1;
    }

    if (nSum == 12.0)
        flag = 1.0;

    delete[] pnPred;
    return flag;
}

void test(const char *pcTestListFile, const char *pcTestLabelsFile, const char *pcTestImageSet)
{
    Network network;

    ifstream file(pcTestListFile);   //name list of test images
    ifstream lab(pcTestLabelsFile);  //label list of test image
    string filename;
    const char *file_name;
    string line, label;
    string filepath = pcTestImageSet;  //paht of image data

    int nNum = 3618, nClass = 12;
    float *pfPredict;
    int nLl[12];

    float fAccuracy_1 = 0.0;
    float fAccuracy_all = 0.0;

    int i = 0;

    if (file && lab)
    {
        while (getline(file, line) && getline(lab, label))
        {
            filename = filepath + line;
            file_name = filename.c_str();
            pfPredict = network.Forward(file_name);
            for (int j = 0; j < 12; j++)
                nLl[j] = label[2 * j] - '0'; 
            fAccuracy_1 += Accuracy_1(pfPredict, nLl, nClass);

            fAccuracy_all += Accuracy_all(pfPredict, nLl, nClass);
            i += 1;

        }
    }
    else
    {
        cout << "no such file" << endl;
    }

    cout << "i:" << i << endl;

    float fAccurSum_1 = fAccuracy_1 / i;
    float fAccurSum_all = fAccuracy_all / i;

    cout << "accuracy_1:" << fAccurSum_1 << endl;
    cout << "accuracy_all:" << fAccurSum_all << endl;

    system("pause");
	
    // You can use following codes to test only one image
	//input an image
    /*
    network.Forward(".\\data\\0.jpg");
    network.Forward(".\\data\\1.jpg");
    system("pause");
    */
}