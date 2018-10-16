#ifndef READDATA_H
#define READDATA_H


class ReadData
{
public:
	ReadData(const char *pcMean, int nInputWidth, int nInputHeight, int nInputChannel);
	~ReadData();
	float *ReadInput(const char *pcName);
	void ReadMean(const char *pcMean);

private:
	int m_nInputSize, m_nInputWidth, m_nInputHeight, m_nInputChannel, m_nImageSize;
	float *m_pfInputData, *m_pfMean;

};


#endif