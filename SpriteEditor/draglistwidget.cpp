#include "draglistwidget.h"
#include <QMimeData>
#include <QDrag>



DragListWidget::DragListWidget(QWidget *parent) :
QListWidget(parent)//�R���X�g���N�^
{
	//�h���b�O���h���b�v���󂯕t����
	//true�ŋ��B
	setAcceptDrops(true);
}

DragListWidget::~DragListWidget()
{

}


void DragListWidget::mousePressEvent(QMouseEvent *e)
{
	//�}�E�X���{�^�����N���b�N������
	if (e->button() == Qt::LeftButton)
	{
		//���̃}�E�X�̈ʒu��ۑ�
		startPos = e->pos();
	}

	//�f�t�H���g�̓����
	QListWidget::mousePressEvent(e);
}

void DragListWidget::mouseMoveEvent(QMouseEvent *e)
{
	////�}�E�X���{�^�����N���b�N���Ȃ�
	if (e->buttons() & Qt::LeftButton)
	{
		//�ۑ����Ă����}�E�X�̈ʒu�ƌ��݂̃}�E�X�̈ʒu�̍������߂�
		//manhattanLength�͐�Βl�����߂����
		int distance = (e->pos() - startPos).manhattanLength();

		//��ŋ��߂������ƃA�v���Őݒ肵�Ă���h���b�O���h���b�v���J�n���鍷��
		//���ׁA����ȏ�Ȃ�h���b�O���J�n����B
		//�Ȃ�startDragDistance()�̓f�t�H���g�ł�4���Ԃ�
		//�ύX��setStartDragDistance(int)
		if (distance >= QApplication::startDragDistance())
		{
			startDrag();
		}

		QListWidget::mouseMoveEvent(e);
	}
}

void DragListWidget::startDrag()
{
	//���ݑI�𒆂̃A�C�e��
	QListWidgetItem *item = currentItem();

	if (item)
	{
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text());

		//�h���b�O���̃A�C�R���̃Z�b�g
		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap("//home//ubuntu001//icon.png"));

		//�h���b�O�����̊J�n�B
		//start�̓h���b�N���h���b�v���I���܂ŏ������Ԃ�Ȃ�
		if (drag->start(Qt::MoveAction) == Qt::MoveAction)
			delete item;
	}
}

void DragListWidget::dragEnterEvent(QDragEnterEvent *e)
{
	DragListWidget *source =
		qobject_cast<DragListWidget *>(e->source());

	//�����ӊO����̃h���b�N���h���b�v�Ȃ�
	if (source && source != this)
	{
		e->setDropAction(Qt::MoveAction);
		e->accept();


		
	}
}

void DragListWidget::dragMoveEvent(QDragMoveEvent *e)
{
	DragListWidget *source =
		qobject_cast<DragListWidget *>(e->source());

	//�����ӊO����̃h���b�N���h���b�v�Ȃ�
	if (source && source != this)
	{
		e->setDropAction(Qt::MoveAction);
		e->accept();
	}
}

void DragListWidget::dropEvent(QDropEvent *e)
{
	DragListWidget *source =
		qobject_cast<DragListWidget *>(e->source());

	//�����ӊO����̃h���b�N���h���b�v�Ȃ�
	if (source && source != this)
	{
		//�����̃A�C�e���փh���b�v���ꂽ���̂�ǉ�
		addItem(e->mimeData()->text());
		e->setDropAction(Qt::MoveAction);
		e->accept();

		
	}
	addItem("addtest");
}