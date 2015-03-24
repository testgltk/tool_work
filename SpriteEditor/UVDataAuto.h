//==============================================================================================
// UVDataAuto クラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/24
//==============================================================================================

//==============================================================================================
// インクルードガード
//==============================================================================================
#ifndef _UVDATAAUTO_H_
#define _UVDATAAUTO_H_

//==============================================================================================
// インクルード
//==============================================================================================
#include "UVData.h"

class CUVDataAuto : public CUVData
{
public:
	CUVDataAuto(void){}
	virtual ~CUVDataAuto(void){}

	virtual void SetDrawPoint(const QPointF& qpoint){ m_DrawPoint = qpoint; }
	virtual void SetUVPoint(const QPointF& qpoint){ m_UVPoint = qpoint; }

protected:
private:

};
#endif