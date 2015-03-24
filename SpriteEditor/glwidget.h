#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QBasicTimer>
#include <QMouseEvent>
class CSprite;

class GlWidget : public QGLWidget
{
	Q_OBJECT

public:
	static const float MOUSE_OFFSET_X;
	static const float MOUSE_OFFSET_Y;
	static const int TEXUTER_ARRAY_MAX = 1000;
	static const float ADDPOINT_LIMIT_X_LEFT;
	static const float ADDPOINT_LIMIT_X_RIGHT;
	static const float ADDPOINT_LIMIT_Y_UP;
	static const float ADDPOINT_LIMIT_Y_DOWN;
	GlWidget(QWidget *parent);
	~GlWidget();
	void AddTextureNum(int nNum);
	void AddTextureFile(QString fileName);
	int GetTextuerNum(void);
	void SetTextureIndex(int nIndex);

	void AddPoint(const QPoint qpoint);
	void DeleteLastPoint(void);
	void AllClearPoint(void);

	void SaveSprite(const char* const FileName);
	void SavePolygon(const char* const FileName);


	void SetNowSelectPolygonColor(int nIndex,float r, float g, float b, float a);
	void SetNowSelectPolygonGroupID(int nIndex, int nGroupID);
protected:
	void initializeGL();        //  OpenGL 初期化
	void resizeGL(int, int);    //  ウィジットリサイズ時のハンドラ
	void paintGL();             //  描画処理
	void timerEvent(QTimerEvent *e);
	void mousePressEvent(QMouseEvent *e);//マウス左をクリックしたら呼ばれる
	//void mouseDoubleClickEvent(QMouseEvent * event);
private:
	GLfloat angle;
	GLuint texture;
	QBasicTimer *timer;


	CSprite* m_pSprites;  ///> 複数描画用ポリゴン情報クラス配列
	GLuint* textures;	  ///> 登録用テクスチャ情報配列
	QPoint* m_QPoints;	  ///> ポイント描画用配列
	int m_textureNum;	  ///> 登録テクスチャ数
	int m_DispTextureNum; ///> 表示テクスチャ番号


	int m_UsePointCount; ///> 得点使用数
};

#endif // GLWIDGET_H
