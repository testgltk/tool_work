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

CSprite::CSprite(void) :m_X(0.0f), m_Y(0.0f), m_Width(1.0f), m_Height(1.0f), m_TexturePath(""), m_TextureData(0), m_UseUVCount(0)
{
	m_pUVDatas = new CUVDataManual[MAX_UV_POINT];
}

CSprite::~CSprite(void)
{
	glDeleteTextures(1, &m_TextureData);

	delete[] m_pUVDatas;
	m_pUVDatas = 0;

}

//==============================================================================================
// 描画処理
//==============================================================================================
void CSprite::Draw(void)
{
	DrawOwnSprite();
	DrawAllUVPoints();
}

void CSprite::DrawOwnSprite(void)
{
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

void CSprite::DrawAllUVPoints(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);

	for (int i = 0; i < m_UseUVCount; i++)
	{
		m_pUVDatas[i].Draw();
	}
}

void CSprite::SetTextureAndPath(const QString path, GLuint& data)
{
	m_TexturePath = path;
	glDeleteTextures(1, &m_TextureData);
	m_TextureData = data;
}

void CSprite::Save(FILE* pFile)
{
	fprintf(pFile, "TexturePath:%s", m_TexturePath.toLocal8Bit().data());
	fprintf(pFile, "UV   Counts:%d", m_UseUVCount);

	for (int i = 0; i < m_UseUVCount; i++)
	{
		fprintf(pFile, "UV %d %f %f", i, (float)m_pUVDatas[i].GetUV().x(), (float)m_pUVDatas[i].GetUV().y());
	}
}

void CSprite::AddUV(const QPoint qpoint)
{
	if (m_UseUVCount >= MAX_UV_POINT)
	{
		return;
	}
	m_pUVDatas[m_UseUVCount].SetDrawPoint(qpoint);
	m_pUVDatas[m_UseUVCount].SetUVPoint(qpoint);
	m_UseUVCount++;
}

void CSprite::DeleteLastUV(void)
{
	if (m_UseUVCount <= 0)
	{
		return;
	}
	m_UseUVCount--;
}