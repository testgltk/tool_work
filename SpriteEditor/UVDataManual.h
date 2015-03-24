// UVDataManual �N���X�t�@�C��
// Author : TOMOHIRO KOUNO
// Create : 2015/3/24
//==============================================================================================

//==============================================================================================
// �C���N���[�h�K�[�h
//==============================================================================================
#ifndef _UVDATAMANUAL_H_
#define _UVDATAMANUAL_H_

//==============================================================================================
// �C���N���[�h
//==============================================================================================
#include "UVData.h"

class CUVDataManual : public CUVData
{
public:
	CUVDataManual(void){}
	virtual ~CUVDataManual(void){}

	virtual void SetDrawPoint(const QPoint qpoint){ m_DrawPoint = qpoint; }
	virtual void SetUVPoint(const QPoint qpoint){ m_UVPoint = qpoint; }
	virtual void Draw(void);
protected:

private:

};
#endif