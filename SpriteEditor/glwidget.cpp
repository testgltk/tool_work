#include "glwidget.h"
#include <GL/glu.h>
#include <QMimeData>
#include <QDrag>
#include "Sprite.h"

const float GlWidget::MOUSE_OFFSET_X = +0.0f;
const float GlWidget::MOUSE_OFFSET_Y = +0.0f;

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

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	timer->start(16, this);
}


void GlWidget::resizeGL(int width, int height)
{
	//  ビューポートの指定
	glViewport(0, 0, width, height);
}

void GlWidget::paintGL()
{
#if 0
	///glClear(GL_COLOR_BUFFER_BIT);   //  カラーバッファをクリア

	//qglColor(Qt::black);            //  描画色指定
	///qglColor(Qt::blue);            //  描画色指定
	///glBegin(GL_LINES);              //  線分（GL_LINES）描画開始

	//glEnd();                        //  線分（GL_LINES）描画終了

	//test textrue
	//モデル・ビュー・マトリックス設定
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	//カメラ設定
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	{ // 平面表示

		//材質設定
		//GLfloat color[] = { 0.8, 0.2, 0.2, 1.0 };
		GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

		glRotatef(angle, 0.0, 1.0, 0.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(2.0, 0.0); glVertex3f(-1.0, 0.0, -1.0);
		glTexCoord2f(2.0, 2.0); glVertex3f(-1.0, 0.0, 1.0);
		glTexCoord2f(0.0, 2.0); glVertex3f(1.0, 0.0, 1.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 0.0, -1.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
}
	glPopMatrix();

	angle = (angle>360.0) ? angle - 360.0 : angle + 1;
	//endtest
#endif

#if 0
	glMatrixMode(GL_PROJECTION);  //  射影行列
	glLoadIdentity();               //  変換行列を初期化
	gluPerspective(30.0,            //  視野角

	(double)width() / (double)height(),     //  アスペクト比
	1.0, 100.0);    //  視野範囲（近距離・遠距離）
	gluLookAt(3.0, 4.0, 5.0,      //  視点位置
	0.0, 0.0, 0.0,      //  目標位置
	0.0, 1.0, 0.0);     //  上方向

	glMatrixMode(GL_MODELVIEW);   //  モデルビュー行列
	glLoadIdentity();               //  変換行列を初期化
	qglColor(Qt::black);            //  描画色指定
	glBegin(GL_LINES);              //  線分（GL_LINES）描画開始
	glVertex3d(0.0, 0.0, 0.0);      //  線分座標指定
	glVertex3d(0.0, 1.0, 0.0);

	glEnd();                        //  線分（GL_LINES）描画終了
	glFlush();                      //  OpenGL の命令をフラッシュ
#endif

#if 0
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, -0.5, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0.5, 0);
	glEnd();
#endif

	glClear(GL_COLOR_BUFFER_BIT);

	// 座標系の設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindTexture(GL_TEXTURE_2D,textures[m_DispTextureNum]);

#if 1
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
#endif
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	//DrawLine
	// 座標系の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(00.0, 600.0, 00.0, 660.0);
	gluOrtho2D(0.0, 650.0, 650.0,0);

	//glBegin(GL_LINES);
	//glColor3f(1, 1, 1);
	//glVertex3f(0, 0, 0);
	//glColor3f(1, 1, 1);
	//glVertex3f(1, 0, 0);
	//glEnd();
	glPointSize(3.0);
	glBegin(GL_POINTS);
	
	for (int i = 0; i < m_UsePointCount; i++)
	{
		glColor3f(1, 1, 0);
		glVertex3f(m_QPoints[i].x() + MOUSE_OFFSET_X, m_QPoints[i].y() + MOUSE_OFFSET_Y, 0);
	}
	glEnd();
}

void GlWidget::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);
	updateGL();
}

void GlWidget::AddTextureFile(QString fileName)
{
	textures[m_textureNum] = bindTexture(QImage(fileName));
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
	}
}



void GlWidget::AddPoint(const QPoint qpoint)
{
	if (m_UsePointCount >= TEXUTER_ARRAY_MAX)
	{
		return;
	}

	m_QPoints[m_UsePointCount] = qpoint;
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
	m_UsePointCount = 0;
}