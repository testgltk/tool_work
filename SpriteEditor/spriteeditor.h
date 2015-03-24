#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_spriteeditor.h"

class SpriteEditor : public QMainWindow
{
Q_OBJECT

public:
	SpriteEditor(QWidget *parent = 0);
	~SpriteEditor();
	Ui::SpriteEditorClass ui;
private:
	
private slots:
void on_actionOpenFile_triggered(void);
void on_actionSaveOriginalFile_triggered(void);
void on_listWidget_currentRowChanged(int);
void on_pushButton_ClearPoint_clicked(void);
void on_actionSavePolygonData_triggered(void);
void on_pushButton_selectColor_clicked(void);
void on_spinBox_selectGroupID_valueChanged(int);
};

#endif // SPRITEEDITOR_H
