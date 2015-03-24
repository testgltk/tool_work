#include "spriteeditor.h"
#include <QGraphicsView>
#include <QImage>
#include <QRect>
#include <QWidget>
#include <QFileDialog>
#include <QMessagebox>
#include <QGraphicsPixmapItem>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
///#include<q
//#include  <Qtgui/QAction>
SpriteEditor::SpriteEditor(QWidget *parent):QMainWindow(parent)
{
	ui.setupUi(this);

	//QObject::connect(this, QAction::triggered,on_actionOpenFile_triggered);

}

SpriteEditor::~SpriteEditor()
{

}


void SpriteEditor::on_actionOpenFile_triggered(void)
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());
	if (!fileName.isEmpty())
	{
		QImage image(fileName);
		if (image.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}

		char* lpPath = fileName.toLocal8Bit().data();

		printf("Before: %s\n", lpPath);

		PathStripPathA(fileName.toLocal8Bit().data());
		
		QString FileNamePathStrip = lpPath;
		ui.listWidget->addItem(fileName);
		ui.OpenGLWidget->AddTextureFile(fileName);

	#if 0
			QGraphicsScene scene;
			//QGraphicsPixmapItem item(QPixmap::fromImage(image)); ///OK
			QPixmap pixmap;
			pixmap.load(fileName);
			//(QPixmap::fromImage(image));
			scene.addPixmap(pixmap);
			//ui.label_2->setPixmap(pixmap);
			//scene.addItem(&item);
			//ui.graphicsView->setScene(&scene);
			//ui.graphicsView->show();
	#endif
	}
}

void SpriteEditor::on_actionSaveOriginalFile_clicked(void)
{

}

void SpriteEditor::on_listWidget_currentRowChanged(int)
{
	ui.OpenGLWidget->SetTextureIndex(ui.listWidget->currentRow());
}

void SpriteEditor::on_pushButton_ClearPoint_clicked(void)
{
	ui.OpenGLWidget->AllClearPoint();
}