#include "StdAfx.h"
#include "ZxClassifierKNearest.h"

Classify::ZxClassifierKNearest::ZxClassifierKNearest(void):
m_K(10)
{
	m_pData = (void*)(new CvKNearest());
}

Classify::ZxClassifierKNearest::ZxClassifierKNearest(int _K):
m_K(_K)
{
	m_pData = (void*)(new CvKNearest());
}

Classify::ZxClassifierKNearest::~ZxClassifierKNearest(void)
{
	delete (CvKNearest*)m_pData;
}

bool Classify::ZxClassifierKNearest::Set_K(int _intK)
{
	if (_intK >0)
	{
		m_K = _intK;
		return true;
	}
	else
		return false;
}

bool Classify::ZxClassifierKNearest::Learn(ZxData& _matData)
{
	cv::Mat matData(_matData.GetAmount(),_matData.GetDimension(),CV_32FC1,_matData.GetData());
	cv::Mat matResponses(_matData.GetAmount(),1,CV_32FC1,_matData.GetType());
	return ((CvKNearest*)m_pData)->train(matData,matResponses);
}

float Classify::ZxClassifierKNearest::Classify(ZxData& _matData)
{
	cv::Mat matSample(_matData.GetAmount(), _matData.GetDimension(), CV_32F, _matData.GetData());
	if (_matData.GetAmount() == 1)
	{
		return ((CvKNearest*)m_pData)->find_nearest(matSample,10);
	}
	else
	{
		cv::Mat matResult(_matData.GetAmount(),1,CV_32F,_matData.GetType());
		return ((CvKNearest*)m_pData)->find_nearest(matSample,8,&matResult);
	}
}

void Classify::ZxClassifierKNearest::Clear()
{
	((CvKNearest*)m_pData)->clear();
}