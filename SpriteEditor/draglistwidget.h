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
	void mousePressEvent(QMouseEvent *e);//マウス左をクリックしたら呼ばれる
	void mouseMoveEvent(QMouseEvent *e);//マウスカーソルを移動したら呼ばれる
	void dragEnterEvent(QDragEnterEvent *e);//ドラッグされたものが来たら呼ばれる
	void dragMoveEvent(QDragMoveEvent *e);//ドラッグ＆ドロップが操作されている間呼ばれる
	void dropEvent(QDropEvent *e);//ドロップの動作

private:
	void startDrag();//自分のウィジットでドラッグを開始した場合
	QPoint startPos;//マウスの位置
};

#endif // DRAGLISTWIDGET_H
