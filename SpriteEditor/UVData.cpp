// UVData クラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/3/24
//==============================================================================================

//==============================================================================================
// インクルード
//==============================================================================================
#include "UVData.h"
#include <QGLWidget>
#include <GL/glu.h>

void CUVData::Draw(void)
{
	// Draw
	glDisable(GL_TEXTURE_2D);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 0);
	glVertex3f(m_DrawPoint.x(), m_DrawPoint.y(), 0);
	glEnd();
}