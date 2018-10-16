#ifndef UTILS_H
#define UTILS_H

float Accuracy_1(float *pfPred, int *pnLab, int nclass);
float Accuracy_all(float *pfPred, int *pnLab, int nclass);
void test(const char *pcTestListName, const char *pcTestLabelsName, const char *pcTestImageSet);

#endif
