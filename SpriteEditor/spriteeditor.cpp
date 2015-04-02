#include "spriteeditor.h"
#include <QGraphicsView>
#include <QImage>
#include <Qrgb>
#include <QRect>
#include <QWidget>
#include <QFileDialog>
#include <QMessagebox>
#include <QGraphicsPixmapItem>
#include <QColorDialog>
#include <QColor>
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

void SpriteEditor::AutoGeneratePointOfFile(const QString& fileName)
{
	QImage qimage;
	qimage.load(fileName);

	int qimage_w = qimage.width();
	int qimage_h = qimage.height();

	//get First pixel value
	QColor FirstColor(qimage.pixel(0, 0));

	int pixelCount = 0;

	bool getDiffStart = false;


	for (int nCntY = 0; nCntY < qimage_h; nCntY++)
	{
		for (int nCntX = 0; nCntX < qimage_w; nCntX++)
		{
			if (nCntX == 0 && nCntY == 0)
			{
				nCntX++;
			}

			QColor clrCurrent(qimage.pixel(nCntX, nCntY));

			if (!getDiffStart)
			{
				//初期ピクセル参照値と現在カラーがことなるなら操作フラグを有効
				if (FirstColor != clrCurrent)
				{
					pixelCount++;
					getDiffStart = true;
					//ui.OpenGLWidget->AddPointF(QPointF((float)(float)nCntX / (float)qimage_w, nCntY));
					ui.OpenGLWidget->AddPointF(QPointF(nCntX, nCntY));
				}
			}
			else
			{
				//操作フラグ有効時に現在参照ピクセル値と初期ピクセルが一致するなら操作フラグを無効
				//ここでもピクセル打ち込み処理を実行
				//有効なときに1つ手前と違う
				if (FirstColor == clrCurrent)
				{
					pixelCount++;
					getDiffStart = false;
					ui.OpenGLWidget->AddPointF(QPointF(nCntX, nCntY));


				}
			}

			if (FirstColor != clrCurrent)
			{
				//pixelCount++;
			}

			float a = clrCurrent.alphaF();
			float r = clrCurrent.redF();
			float g = clrCurrent.greenF();
			float b = clrCurrent.blueF();
		}
	}

	pixelCount = pixelCount;
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

		AutoGeneratePointOfFile(fileName);
	}
}

void SpriteEditor::on_actionSaveOriginalFile_triggered(void)
{
	QString saveText = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("SpriteFile(*.sprite)"));
	if (!saveText.isEmpty())
	{
		//Save
		ui.OpenGLWidget->SaveSprite(saveText.toLocal8Bit().data());
	}
}

void SpriteEditor::on_listWidget_currentRowChanged(int)
{
	ui.OpenGLWidget->SetTextureIndex(ui.listWidget->currentRow());
}

void SpriteEditor::on_pushButton_ClearPoint_clicked(void)
{
	ui.OpenGLWidget->AllClearPoint();
}

void SpriteEditor::on_actionSavePolygonData_triggered(void)
{
	QString saveText = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("PolygonFile(*.polygon)"));
	if (!saveText.isEmpty())
	{
		//Save
		ui.OpenGLWidget->SavePolygon(saveText.toLocal8Bit().data());
	}
}

void SpriteEditor::on_pushButton_selectColor_clicked(void)
{
	QColor color = QColorDialog::getColor( Qt::yellow, this );

	ui.OpenGLWidget->SetNowSelectPolygonColor(ui.spinBox_selectPolygonID->value(), color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void SpriteEditor::on_spinBox_selectGroupID_valueChanged(int)
{
	ui.OpenGLWidget->SetNowSelectPolygonGroupID(ui.spinBox_selectPolygonID->value(), ui.spinBox_selectGroupID->value());
}