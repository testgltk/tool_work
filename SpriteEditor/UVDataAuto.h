//==============================================================================================
// UVDataAuto �N���X�t�@�C��
// Author : TOMOHIRO KOUNO
// Create : 2015/3/24
//==============================================================================================

//==============================================================================================
// �C���N���[�h�K�[�h
//==============================================================================================
#ifndef _UVDATAAUTO_H_
#define _UVDATAAUTO_H_

//==============================================================================================
// �C���N���[�h
//==============================================================================================
#include "UVData.h"

class CUVDataAuto : public CUVData
{
public:
	CUVDataAuto(void){}
	virtual ~CUVDataAuto(void){}

	virtual void SetDrawPoint(const QPoint& qpoint){ m_DrawPoint = qpoint; }
	virtual void SetUVPoint(const QPoint& qpoint){ m_UVPoint = qpoint; }

protected:
private:

};
#endif