//==============================================================================================
// 3角形描画クラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// インクルードガード
//==============================================================================================
#ifndef _CDRAWTRIANGLE_H_
#define _CDRAWTRIANGLE_H_

//==============================================================================================
// インクルード
//==============================================================================================
#include <QGLWidget>
#include <QBasicTimer>
#include <QString>
#include <stdio.h>

class CUVDataManual;

typedef struct POS3_TAG
{

	float x;
	float y;
	float z;
	POS3_TAG(void) : x(0), y(0), z(0){ }
}POS3;

typedef struct TEXCOORD_TAG
{
	float u;
	float v;
	TEXCOORD_TAG(void) :u(0), v(0){}
}TEXCOORD2;

typedef struct COLOR4_TAG
{
	float r;
	float g;
	float b;
	float a;
	COLOR4_TAG(void) : r(0), g(0), b(0), a(0){}
}COLOR4;

//==============================================================================================
// スプライトクラス
//==============================================================================================
class CDrawTriangle
{
public:

	static const int MAX_VERTEX = 3;

	CDrawTriangle(void)
	:m_nGroupID(0), m_Vertecies{}, m_Texcoords{}, m_Color{}
	, m_UseVertexCount(0)
	{
		SetColor(0.9f, 0.9f, 0.4f, 0.4f);
	}

	~CDrawTriangle(void){}

	void SetVertexCount(int nCount){ m_UseVertexCount = nCount; }

	void AddVertexCount(void)
	{
		if (m_UseVertexCount >= MAX_VERTEX)
		{
			return;
		}
		m_UseVertexCount++;
	}

	void DeleteLastVertexCount(void)
	{
		if (m_UseVertexCount <= 0)
		{
			return;
		}
		m_UseVertexCount--;
	}

	void Draw(void);
	
	void SetVertex(int nIndex, float x, float y, float z)
	{
		m_Vertecies[nIndex].x = x;
		m_Vertecies[nIndex].y = y;
		m_Vertecies[nIndex].z = z;
	}

	void SetTexcoord(int nIndex, float u, float v)
	{
		m_Texcoords[nIndex].u = u;
		m_Texcoords[nIndex].v = v;
	}

	void SetColor(float r, float g, float b,float a)
	{
		m_Color.r = r;
		m_Color.g = g;
		m_Color.b = b;
		m_Color.a = a;
	}

	void SetGroupID(int nID){ m_nGroupID = nID; }


	int GetGroupID(void){ return m_nGroupID; }
	
	int GetUseVertexCount(void){ return m_UseVertexCount; }

	POS3 GetVertex(int nIndex){ return m_Vertecies[nIndex]; }

	void Save(FILE* pFile)
	{
		//描画されてなければスキップ
		if (m_UseVertexCount < 3)
		{
			return;
		}

		fprintf(pFile, "GROUP ID = %d \n",m_nGroupID);

		for (int i = 0; i < 3; i++)
		{
			fprintf(pFile, "V: %f %f %f T:%f %f \n", m_Vertecies[i].x, m_Vertecies[i].y, m_Vertecies[i].z, m_Texcoords[i].u, m_Texcoords[i].v);
		}
	}

protected:

private:
	int		  m_nGroupID;		///> この三角形のグループ認識情報
	POS3      m_Vertecies[3];	///> 1つの三角系の頂点座標情報
	TEXCOORD2 m_Texcoords[3];	///> 1つの三角形のテクスチャ座標情報
	COLOR4	  m_Color;			///> このポリゴンに当てはめる色情報（デフォルト：ホワイト）
	int		  m_UseVertexCount; ///> このポリゴンに対して点を何回打ち込んでるか(0,1,2,3)
};
#endif