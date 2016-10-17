#include "StdAfx.h"
#include "ZxClassifierNormalBayes.h"

Classify::ZxClassifierNormalBayes::ZxClassifierNormalBayes(void)
{
	m_pData = (void*)(new CvNormalBayesClassifier());
}


Classify::ZxClassifierNormalBayes::~ZxClassifierNormalBayes(void)
{
	delete (CvNormalBayesClassifier*)m_pData;
}

bool Classify::ZxClassifierNormalBayes::Learn(ZxData& _matData)
{
	cv::Mat matData(_matData.GetAmount(),_matData.GetDimension(),CV_32FC1,_matData.GetData());
	cv::Mat matResponses(_matData.GetAmount(),1,CV_32FC1,_matData.GetType());
	return ((CvNormalBayesClassifier*)m_pData)->train(matData,matResponses);
}

float Classify::ZxClassifierNormalBayes::Classify(ZxData& _matData)
{
	cv::Mat matSample(_matData.GetAmount(), _matData.GetDimension(), CV_32F, _matData.GetData());
	if (_matData.GetAmount() == 1)
	{
		return ((CvNormalBayesClassifier*)m_pData)->predict(matSample);
	}
	else
	{
		cv::Mat matResult(_matData.GetAmount(),1,CV_32F,_matData.GetType());
		return ((CvNormalBayesClassifier*)m_pData)->predict(matSample,&matResult);
	}
}

void Classify::ZxClassifierNormalBayes::Clear()
{
	((CvNormalBayesClassifier*)m_pData)->clear();
}