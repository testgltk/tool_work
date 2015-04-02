#include "glwidget.h"
#include <GL/glu.h>
#include <QMimeData>
#include <QDrag>
#include "Sprite.h"
#include <stdio.h>

const float GlWidget::MOUSE_OFFSET_X = +0.0f;
const float GlWidget::MOUSE_OFFSET_Y = +0.0f;
const float GlWidget::ADDPOINT_LIMIT_X_LEFT  = 162;
const float GlWidget::ADDPOINT_LIMIT_X_RIGHT = 486;
const float GlWidget::ADDPOINT_LIMIT_Y_UP    = 162;
const float GlWidget::ADDPOINT_LIMIT_Y_DOWN  = 486;

GlWidget::GlWidget(QWidget *parent)
	: QGLWidget(parent)
	, timer(new QBasicTimer)
	, m_pSprites(nullptr)
{
	texture = 0;
	m_textureNum = 0;
	m_DispTextureNum = 0;
	m_UsePointCount = 0;
	textures = new GLuint[TEXUTER_ARRAY_MAX];
	m_pSprites = new CSprite[TEXUTER_ARRAY_MAX];

	m_QPoints = new QPoint[TEXUTER_ARRAY_MAX];
	
}

GlWidget::~GlWidget()
{
	glDeleteTextures(1, &texture);
	delete timer;
	timer = 0;

	delete[] textures;
	textures = 0;

	delete[] m_pSprites;
	m_pSprites = 0;

	delete[] m_QPoints;
	m_QPoints = 0;
	glDisable(GL_BLEND);
}

void GlWidget::initializeGL()
{
	//qglClearColor(Qt::lightGray);  // 背景色指定
	qglClearColor(Qt::black);  // 背景色指定
	//カリング：表面のみ表示
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

#if 0
	//光源有効
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//光源の設定
	GLfloat light_position[] = { -50.0, 50.0, 50.0, 1.0 };
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
#endif

	//テクスチャ 初期化
	texture = bindTexture(QImage("testRect.png"));
	
	timer->start(16, this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


}


void GlWidget::resizeGL(int width, int height)
{
	//  ビューポートの指定
	glViewport(0, 0, width, height);
}

void GlWidget::paintGL()
{
	qglColor(Qt::black);            //  描画色指定
	glClear(GL_COLOR_BUFFER_BIT);

	//選択されてるポリゴンを1枚描画 (内部で設定されたUVも描画)
	m_pSprites[m_DispTextureNum].Draw();
}

void GlWidget::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);
	updateGL();
}

void GlWidget::AddTextureFile(QString fileName)
{
	QImage qimage(fileName);
	float Width = (float)qimage.width();
	float height = (float)qimage.height();

	textures[m_textureNum] = bindTexture(qimage);
	m_pSprites[m_textureNum].SetTextureAndPath(fileName, textures[m_textureNum]);
	m_pSprites[m_textureNum].SetTextureWidth(Width);
	m_pSprites[m_textureNum].SetTextureHeight(height);
	m_textureNum++;
}

void GlWidget::AddTextureNum(int nNum)
{
	m_textureNum += nNum;
}

int GlWidget::GetTextuerNum(void)
{
	return m_textureNum;
}

void GlWidget::SetTextureIndex(int nIndex)
{
	m_DispTextureNum = nIndex;
	glBindTexture(GL_TEXTURE_2D, textures[m_DispTextureNum]);
}

//マウス左をクリックしたら呼ばれる
void GlWidget::mousePressEvent(QMouseEvent *e)
{
	//マウス左ボタンをクリックしたら　点を追加
	if (e->button() == Qt::LeftButton)
	{
		AddPoint(e->pos());
	}

	//マウス右ボタンをクリックしたら　最後の点を削除
	else if (e->button() == Qt::RightButton)
	{
		DeleteLastPoint();
		m_pSprites[m_DispTextureNum].DeleteLastUV();
	}
}

void GlWidget::AddPoint(const QPoint qpoint)
{
	if (m_UsePointCount >= TEXUTER_ARRAY_MAX)
	{
		return;
	}

	//点を追加できる位置か計算
	float x = qpoint.x();
	float y = qpoint.y();

	//範囲外ならスキップ X
	if (x < ADDPOINT_LIMIT_X_LEFT || ADDPOINT_LIMIT_X_RIGHT< x)
	{
		return;
	}
	//範囲外ならスキップ Y
	if (y < ADDPOINT_LIMIT_Y_UP || ADDPOINT_LIMIT_Y_DOWN< y)
	{
		return;
	}

	m_pSprites[m_DispTextureNum].AddUV(qpoint);

	m_QPoints[m_UsePointCount] = qpoint;
	m_UsePointCount++;
	
}

void GlWidget::AddPointF(const QPointF qpointf)
{
	if (m_UsePointCount >= TEXUTER_ARRAY_MAX)
	{
		return;
	}

	//点を追加できる位置か計算
	float x = qpointf.x();
	float y = qpointf.y();

	//範囲外ならスキップ X
	if (x < ADDPOINT_LIMIT_X_LEFT || ADDPOINT_LIMIT_X_RIGHT< x)
	{
		return;
	}
	//範囲外ならスキップ Y
	if (y < ADDPOINT_LIMIT_Y_UP || ADDPOINT_LIMIT_Y_DOWN< y)
	{
		return;
	}

	m_pSprites[m_DispTextureNum].AddUVF(qpointf);

	//m_QPoints[m_UsePointCount] = (QPoint)(qpointf);
	m_UsePointCount++;
}

void GlWidget::DeleteLastPoint(void)
{
	if (m_UsePointCount <= 0)
	{
		return;
	}

	m_UsePointCount--;
}

void GlWidget::AllClearPoint(void)
{
	m_pSprites[m_DispTextureNum].AllClearUV();
	m_UsePointCount = 0;
}

void GlWidget::SaveSprite(const char* const FileName)
{
	FILE* pFile = NULL;
	pFile = fopen(FileName, "w");
	
	m_pSprites[m_DispTextureNum].Save(pFile);

	fclose(pFile);
}

void GlWidget::SavePolygon(const char* const FileName)
{
	FILE* pFile = NULL;
	pFile = fopen(FileName, "w");
	
	m_pSprites[m_DispTextureNum].SavePolygon(pFile);

	fclose(pFile);
}

void GlWidget::SetNowSelectPolygonColor(int nIndex, float r, float g, float b, float a)
{
	m_pSprites[m_DispTextureNum].SetNowSelectPolygonColor(nIndex,r, g, b, a);
}

void GlWidget::SetNowSelectPolygonGroupID(int nIndex, int nGroupID)
{
	m_pSprites[m_DispTextureNum].SetNowSelectPolygonGroupID(nIndex, nGroupID);
}