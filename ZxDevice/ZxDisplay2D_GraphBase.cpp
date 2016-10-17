#include "StdAfx.h"
#include "ZxDisplay2D_GraphBase.h"


Display2D::ZxDisplay2D_GraphBase::ZxDisplay2D_GraphBase(void)
	:m_Type(ZXDISPLAY2D_GRAPH_UNKNOW)
{
}


Display2D::ZxDisplay2D_GraphBase::~ZxDisplay2D_GraphBase(void)
{
}


int Display2D::ZxDisplay2D_GraphBase::GetType()
{
	return m_Type;
}

