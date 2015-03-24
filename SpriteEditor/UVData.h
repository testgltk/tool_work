//==============================================================================================
// UVData クラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// インクルードガード
//==============================================================================================
#ifndef _UVDATA_H_
#define _UVDATA_H_

//==============================================================================================
// インクルード
//==============================================================================================
#include <QPoint>

class CUVData
{
public:
	CUVData(void){}
	virtual ~CUVData(void){}

	virtual void SetDrawPoint(void){}
	virtual void SetUVPoint(void){}
	virtual void Draw(void);
	QPoint& GetUV(void){ return m_UVPoint; }

protected:
	QPoint m_DrawPoint;	///> 描画座標系でのポイント
	QPoint m_UVPoint;	///> 描画座標系に対応するUV値
private:

};
#endif