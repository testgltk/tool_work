#include "DrawTriangle.h"
#include <QGLWidget>
#include <GL/glu.h>

void CDrawTriangle::Draw(void)
{
	//かけなければスキップ
	if (m_UseVertexCount < 3)
	{
		return;
	}

	//座標系を設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);
	glBegin(GL_TRIANGLES);

	//描画
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[0].u, -m_Texcoords[0].v);
	glVertex3f(m_Vertecies[0].x, m_Vertecies[0].y, m_Vertecies[0].z);
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[1].u, -m_Texcoords[1].v);
	glVertex3f(m_Vertecies[1].x, m_Vertecies[1].y, m_Vertecies[1].z);
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[2].u, -m_Texcoords[2].v);
	glVertex3f(m_Vertecies[2].x, m_Vertecies[2].y, m_Vertecies[2].z);

	glEnd();
}