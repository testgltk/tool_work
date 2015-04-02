//==============================================================================================
// ２Dスプライトクラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// インクルード
//==============================================================================================
#include "Sprite.h"
#include <QGLWidget>
#include <GL/glu.h>
#include "glwidget.h"
#include "UVDataManual.h"
#include "DrawTriangle.h"

CSprite::CSprite(void) :
m_X(0.0f),
m_Y(0.0f),
m_PolygonWidth(1.0f),
m_PolygonHeight(1.0f),
m_TexturePath(""),
m_TextureData(0),
m_UseUVCount(0),
m_TextureWidth(1.0f),
m_TextureHeight(1.0f),
m_UseTriangleCount(0)
{
	m_pUVDatas = new CUVDataManual[MAX_UV_POINT];

	m_pDrawTriangles = new CDrawTriangle[MAX_USE_TRIANGLES];
}

CSprite::~CSprite(void)
{
	glDeleteTextures(1, &m_TextureData);

	delete[] m_pUVDatas;
	m_pUVDatas = 0;

	delete[] m_pDrawTriangles;
	m_pDrawTriangles = 0;
}

//==============================================================================================
// 描画処理
//==============================================================================================
void CSprite::Draw(void)
{
	DrawOwnSprite();
	DrawAllUVPoints();
}

//==============================================================================================
// test描画処理
//==============================================================================================
void CSprite::DrawTest(void)
{
	// 座標系の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(1, 1, 1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0);

	glColor3f(1, 1, 1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, 0.5, 0);

	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, 0.5, 0);

	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, 0);
	glEnd();
}


//==============================================================================================
// テクスチャポリゴン描画
//==============================================================================================
void CSprite::DrawOwnSprite(void)
{
	// 座標系の設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glEnable(GL_TEXTURE_2D);



	glBindTexture(GL_TEXTURE_2D, m_TextureData);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, 0.5, 0);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, 0.5, 0);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

//==============================================================================================
// ポリゴンに付随するポイントの全描画
//==============================================================================================
void CSprite::DrawAllUVPoints(void)
{
	// 座標系の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);

	for (int i = 0; i < m_UseUVCount; i++)
	{
		m_pUVDatas[i].Draw();
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureData);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	for (int i = 0; i < m_UseTriangleCount; i++)
	{
		glDisable(GL_TEXTURE_2D);
		m_pDrawTriangles[i].Draw();
	}
	glDisable(GL_TEXTURE_2D);
}

//==============================================================================================
// ポリゴンに付随するテクスチャデータとパス設定
//==============================================================================================
void CSprite::SetTextureAndPath(const QString path, GLuint& data)
{
	m_TexturePath = path;
	glDeleteTextures(1, &m_TextureData);
	m_TextureData = data;
}

//==============================================================================================
// スプライト情報の保存
//==============================================================================================
void CSprite::Save(FILE* pFile)
{
	fprintf(pFile, "TexturePath:%s\n", m_TexturePath.toLocal8Bit().data());
	fprintf(pFile, "UV   Counts:%d\n", m_UseUVCount);

	for (int i = 0; i < m_UseUVCount; i++)
	{
		fprintf(pFile, "UV %d %f %f\n", i, (float)m_pUVDatas[i].GetUV().x(), (float)m_pUVDatas[i].GetUV().y());
	}
}

//==============================================================================================
// ポリゴン情報の保存
//==============================================================================================
void CSprite::SavePolygon(FILE* pFile)
{
	fprintf(pFile, "TexturePath:%s\n", m_TexturePath.toLocal8Bit().data());
	fprintf(pFile, "Triangle   Counts:%d\n", m_UseTriangleCount);

	for (int i = 0; i < m_UseTriangleCount; i++)
	{
		m_pDrawTriangles[i].Save(pFile);
	}
}

//==============================================================================================
// UV点情報の追加
//==============================================================================================
void CSprite::AddUV(const QPoint qpoint)
{
	if (m_UseUVCount >= MAX_UV_POINT)
	{
		return;
	}
	m_pUVDatas[m_UseUVCount].SetDrawPoint(qpoint);

	
	QPointF uvSetPoint;
	float RateX = ((float)qpoint.x() - GlWidget::ADDPOINT_LIMIT_X_LEFT) / (float)(GlWidget::ADDPOINT_LIMIT_X_RIGHT - GlWidget::ADDPOINT_LIMIT_X_LEFT);
	float RateY = ((float)qpoint.y() - GlWidget::ADDPOINT_LIMIT_Y_UP  ) / (float)(GlWidget::ADDPOINT_LIMIT_Y_DOWN  - GlWidget::ADDPOINT_LIMIT_Y_UP);
	uvSetPoint.setX(RateX);
	uvSetPoint.setY(RateY);
	//m_pUVDatas[m_UseUVCount].SetUVPoint(qpoint);
	m_pUVDatas[m_UseUVCount].SetUVPoint(uvSetPoint);
	m_UseUVCount++;

	//////////////////
	/// TRIANGLE DATA
	//////////////////
	int nowUseTriIndex = m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount();
	// 3角形が足りないならそれに追加してく
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() <= 2)
	{
		m_pDrawTriangles[m_UseTriangleCount].SetVertex(nowUseTriIndex, qpoint.x(), qpoint.y(), 0);
		m_pDrawTriangles[m_UseTriangleCount].SetTexcoord(nowUseTriIndex, RateX, RateY);
		m_pDrawTriangles[m_UseTriangleCount].AddVertexCount();
	}
	
	//追加後に三角形が成立したら新たに三角形ポリゴンデータを用意
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() >= 3)
	{
		m_UseTriangleCount++;
	}
}

void CSprite::AddUVF(const QPointF qpointf)
{
	if (m_UseUVCount >= MAX_UV_POINT)
	{
		return;
	}
	m_pUVDatas[m_UseUVCount].SetDrawPoint(qpointf);


	QPointF uvSetPoint;
	float RateX = ((float)qpointf.x() - GlWidget::ADDPOINT_LIMIT_X_LEFT) / (float)(GlWidget::ADDPOINT_LIMIT_X_RIGHT - GlWidget::ADDPOINT_LIMIT_X_LEFT);
	float RateY = ((float)qpointf.y() - GlWidget::ADDPOINT_LIMIT_Y_UP) / (float)(GlWidget::ADDPOINT_LIMIT_Y_DOWN - GlWidget::ADDPOINT_LIMIT_Y_UP);
	uvSetPoint.setX(RateX);
	uvSetPoint.setY(RateY);
	//m_pUVDatas[m_UseUVCount].SetUVPoint(qpoint);
	m_pUVDatas[m_UseUVCount].SetUVPoint(uvSetPoint);
	m_UseUVCount++;

	//////////////////
	/// TRIANGLE DATA
	//////////////////
	int nowUseTriIndex = m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount();
	// 3角形が足りないならそれに追加してく
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() <= 2)
	{
		m_pDrawTriangles[m_UseTriangleCount].SetVertex(nowUseTriIndex, qpointf.x(), qpointf.y(), 0);
		m_pDrawTriangles[m_UseTriangleCount].SetTexcoord(nowUseTriIndex, RateX, RateY);
		m_pDrawTriangles[m_UseTriangleCount].AddVertexCount();
	}

	//追加後に三角形が成立したら新たに三角形ポリゴンデータを用意
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() >= 3)
	{
		m_UseTriangleCount++;
	}
}

//==============================================================================================
// UV点情報の追加
//==============================================================================================
void CSprite::DeleteLastUV(void)
{
	if (m_UseUVCount <= 0)
	{
		return;
	}
	m_UseUVCount--;
}

void CSprite::AllClearUV(void)
{
	m_UseUVCount = 0;
}

void CSprite::SetNowSelectPolygonColor(int nIndex,float r, float g, float b, float a)
{
	m_pDrawTriangles[nIndex].SetColor(r, g, b, a);
}

void CSprite::SetNowSelectPolygonGroupID(int nIndex, int nGroupID)
{
	m_pDrawTriangles[nIndex].SetGroupID(nGroupID);
}