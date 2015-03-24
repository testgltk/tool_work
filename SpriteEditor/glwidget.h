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
	void initializeGL();        //  OpenGL ������
	void resizeGL(int, int);    //  �E�B�W�b�g���T�C�Y���̃n���h��
	void paintGL();             //  �`�揈��
	void timerEvent(QTimerEvent *e);
	void mousePressEvent(QMouseEvent *e);//�}�E�X�����N���b�N������Ă΂��
	//void mouseDoubleClickEvent(QMouseEvent * event);
private:
	GLfloat angle;
	GLuint texture;
	QBasicTimer *timer;


	CSprite* m_pSprites;  ///> �����`��p�|���S�����N���X�z��
	GLuint* textures;	  ///> �o�^�p�e�N�X�`�����z��
	QPoint* m_QPoints;	  ///> �|�C���g�`��p�z��
	int m_textureNum;	  ///> �o�^�e�N�X�`����
	int m_DispTextureNum; ///> �\���e�N�X�`���ԍ�


	int m_UsePointCount; ///> ���_�g�p��
};

#endif // GLWIDGET_H
