#ifndef DRAGLISTWIDGET_H
#define DRAGLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QApplication>
class DragListWidget : public QListWidget
{
	Q_OBJECT

public:
	DragListWidget(QWidget *parent);
	~DragListWidget();
protected:
	void mousePressEvent(QMouseEvent *e);//�}�E�X�����N���b�N������Ă΂��
	void mouseMoveEvent(QMouseEvent *e);//�}�E�X�J�[�\�����ړ�������Ă΂��
	void dragEnterEvent(QDragEnterEvent *e);//�h���b�O���ꂽ���̂�������Ă΂��
	void dragMoveEvent(QDragMoveEvent *e);//�h���b�O���h���b�v�����삳��Ă���ԌĂ΂��
	void dropEvent(QDropEvent *e);//�h���b�v�̓���

private:
	void startDrag();//�����̃E�B�W�b�g�Ńh���b�O���J�n�����ꍇ
	QPoint startPos;//�}�E�X�̈ʒu
};

#endif // DRAGLISTWIDGET_H
