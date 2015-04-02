//==============================================================================================
// �QD�X�v���C�g�N���X�t�@�C��
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// �C���N���[�h
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
// �`�揈��
//==============================================================================================
void CSprite::Draw(void)
{
	DrawOwnSprite();
	DrawAllUVPoints();
}

//==============================================================================================
// test�`�揈��
//==============================================================================================
void CSprite::DrawTest(void)
{
	// ���W�n�̐ݒ�
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
// �e�N�X�`���|���S���`��
//==============================================================================================
void CSprite::DrawOwnSprite(void)
{
	// ���W�n�̐ݒ�
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
// �|���S���ɕt������|�C���g�̑S�`��
//==============================================================================================
void CSprite::DrawAllUVPoints(void)
{
	// ���W�n�̐ݒ�
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
// �|���S���ɕt������e�N�X�`���f�[�^�ƃp�X�ݒ�
//==============================================================================================
void CSprite::SetTextureAndPath(const QString path, GLuint& data)
{
	m_TexturePath = path;
	glDeleteTextures(1, &m_TextureData);
	m_TextureData = data;
}

//==============================================================================================
// �X�v���C�g���̕ۑ�
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
// �|���S�����̕ۑ�
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
// UV�_���̒ǉ�
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
	// 3�p�`������Ȃ��Ȃ炻��ɒǉ����Ă�
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() <= 2)
	{
		m_pDrawTriangles[m_UseTriangleCount].SetVertex(nowUseTriIndex, qpoint.x(), qpoint.y(), 0);
		m_pDrawTriangles[m_UseTriangleCount].SetTexcoord(nowUseTriIndex, RateX, RateY);
		m_pDrawTriangles[m_UseTriangleCount].AddVertexCount();
	}
	
	//�ǉ���ɎO�p�`������������V���ɎO�p�`�|���S���f�[�^��p��
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
	// 3�p�`������Ȃ��Ȃ炻��ɒǉ����Ă�
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() <= 2)
	{
		m_pDrawTriangles[m_UseTriangleCount].SetVertex(nowUseTriIndex, qpointf.x(), qpointf.y(), 0);
		m_pDrawTriangles[m_UseTriangleCount].SetTexcoord(nowUseTriIndex, RateX, RateY);
		m_pDrawTriangles[m_UseTriangleCount].AddVertexCount();
	}

	//�ǉ���ɎO�p�`������������V���ɎO�p�`�|���S���f�[�^��p��
	if (m_pDrawTriangles[m_UseTriangleCount].GetUseVertexCount() >= 3)
	{
		m_UseTriangleCount++;
	}
}

//==============================================================================================
// UV�_���̒ǉ�
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