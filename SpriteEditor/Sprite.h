//==============================================================================================
// ２Dスプライトクラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// インクルードガード
//==============================================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_

//==============================================================================================
// インクルード
//==============================================================================================
#include <QGLWidget>
#include <QBasicTimer>
#include <QString>
#include <stdio.h>

class CUVDataManual;

//==============================================================================================
// スプライトクラス
//==============================================================================================
class CSprite
{
public:
	static const int MAX_UV_POINT = 256;

	CSprite(void);
	virtual ~CSprite(void);
	void SetX(float fX){ m_X = fX; }
	void SetY(float fY){ m_Y = fY; }
	float GetX(void){ return m_X; }
	float GetY(void){ return m_Y; }
	float SetWidth(float fW){ m_Width = fW; }
	float SetHeight(float fH){ m_Height = fH; }
	float GetWidth(void){ return m_Width; }
	float GetHeight(void){ return m_Height; }
	void AddUV(const QPoint qpoint);
	void DeleteLastUV(void);

	void Draw(void);

	void SetTextureAndPath(const QString path, GLuint& data);
	QString GetTexturePath(void){ return m_TexturePath; }

	void Save(FILE* pFile);

protected:
	void DrawOwnSprite(void);
	void DrawAllUVPoints(void);

private:
	float m_X;
	float m_Y;
	float m_Width;
	float m_Height;
	int   m_UseUVCount;
	QString m_TexturePath;
	GLuint m_TextureData;
	CUVDataManual* m_pUVDatas;
};
#endif