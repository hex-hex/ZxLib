#include "StdAfx.h"
#include "ZxClassifierSVM.h"


Classify::ZxClassifierSVM::ZxClassifierSVM(void)
{
	m_pData = (void*)(new CvSVM());
}


Classify::ZxClassifierSVM::~ZxClassifierSVM(void)
{
	delete (CvSVM*)m_pData;
}

bool Classify::ZxClassifierSVM::Learn(ZxData& _matData)
{
	cv::Mat matData(_matData.GetAmount(),_matData.GetDimension(),CV_32FC1,_matData.GetData());
	cv::Mat matResponses(_matData.GetAmount(),1,CV_32FC1,_matData.GetType());
	return ((CvSVM*)m_pData)->train_auto(matData,matResponses,cv::Mat(),cv::Mat(),CvSVMParams());
}

float Classify::ZxClassifierSVM::Classify(ZxData& _matData)
{
	cv::Mat matSample(_matData.GetAmount(), _matData.GetDimension(), CV_32F, _matData.GetData());
	if (_matData.GetAmount() == 1)
	{
		return ((CvSVM*)m_pData)->predict(matSample);
	}
	else
	{
		cv::Mat matResult(_matData.GetAmount(),1,CV_32F,_matData.GetType());
		((CvSVM*)m_pData)->predict(matSample,matResult);
		return FLT_MAX;
	}
}

void Classify::ZxClassifierSVM::Clear()
{
	((CvSVM*)m_pData)->clear();
}
