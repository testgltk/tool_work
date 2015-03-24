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
void on_listWidget_currentRowChanged(int);
void on_pushButton_ClearPoint_clicked(void);
};

#endif // SPRITEEDITOR_H
