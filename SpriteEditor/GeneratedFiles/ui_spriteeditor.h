/********************************************************************************
** Form generated from reading UI file 'spriteeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITEEDITOR_H
#define UI_SPRITEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "draglistwidget.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_SpriteEditorClass
{
public:
    QAction *actionOpenFile;
    QAction *actionSaveOriginalFile;
    QAction *actionLoadOriginalFile;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_ImageList;
    QWidget *dockWidgetContents;
    DragListWidget *listWidget;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    GlWidget *OpenGLWidget;
    QPushButton *pushButton_ClearPoint;

    void setupUi(QMainWindow *SpriteEditorClass)
    {
        if (SpriteEditorClass->objectName().isEmpty())
            SpriteEditorClass->setObjectName(QStringLiteral("SpriteEditorClass"));
        SpriteEditorClass->resize(1078, 794);
        SpriteEditorClass->setAcceptDrops(true);
        actionOpenFile = new QAction(SpriteEditorClass);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        actionSaveOriginalFile = new QAction(SpriteEditorClass);
        actionSaveOriginalFile->setObjectName(QStringLiteral("actionSaveOriginalFile"));
        actionLoadOriginalFile = new QAction(SpriteEditorClass);
        actionLoadOriginalFile->setObjectName(QStringLiteral("actionLoadOriginalFile"));
        centralWidget = new QWidget(SpriteEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SpriteEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SpriteEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1078, 24));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        SpriteEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SpriteEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SpriteEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SpriteEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SpriteEditorClass->setStatusBar(statusBar);
        dockWidget_ImageList = new QDockWidget(SpriteEditorClass);
        dockWidget_ImageList->setObjectName(QStringLiteral("dockWidget_ImageList"));
        dockWidget_ImageList->setMinimumSize(QSize(256, 600));
        dockWidget_ImageList->setAcceptDrops(true);
        dockWidget_ImageList->setStyleSheet(QStringLiteral("background-color: rgb(226, 226, 226);"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        listWidget = new DragListWidget(dockWidgetContents);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 10, 261, 611));
        listWidget->setMinimumSize(QSize(256, 600));
        listWidget->setAcceptDrops(true);
        listWidget->setDragEnabled(true);
        listWidget->setDragDropMode(QAbstractItemView::DragDrop);
        dockWidget_ImageList->setWidget(dockWidgetContents);
        SpriteEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_ImageList);
        dockWidget = new QDockWidget(SpriteEditorClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMinimumSize(QSize(600, 600));
        dockWidget->setStyleSheet(QStringLiteral("background-color: rgb(226, 226, 226);"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        OpenGLWidget = new GlWidget(dockWidgetContents_2);
        OpenGLWidget->setObjectName(QStringLiteral("OpenGLWidget"));
        OpenGLWidget->setGeometry(QRect(0, 0, 650, 650));
        OpenGLWidget->setStyleSheet(QStringLiteral("background-color: rgb(152, 255, 114);"));
        pushButton_ClearPoint = new QPushButton(dockWidgetContents_2);
        pushButton_ClearPoint->setObjectName(QStringLiteral("pushButton_ClearPoint"));
        pushButton_ClearPoint->setGeometry(QRect(20, 670, 75, 23));
        dockWidget->setWidget(dockWidgetContents_2);
        SpriteEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoadOriginalFile);
        menuFile->addAction(actionSaveOriginalFile);
        menuFile->addAction(actionOpenFile);

        retranslateUi(SpriteEditorClass);

        QMetaObject::connectSlotsByName(SpriteEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SpriteEditorClass)
    {
        SpriteEditorClass->setWindowTitle(QApplication::translate("SpriteEditorClass", "SpriteEditor", 0));
        actionOpenFile->setText(QApplication::translate("SpriteEditorClass", "\347\224\273\345\203\217\343\203\225\343\202\241\343\202\244\343\203\253\343\202\222\351\226\213\343\201\217", 0));
        actionSaveOriginalFile->setText(QApplication::translate("SpriteEditorClass", "\343\203\225\343\202\241\343\202\244\343\203\253\343\201\256\344\277\235\345\255\230", 0));
        actionLoadOriginalFile->setText(QApplication::translate("SpriteEditorClass", "\343\203\225\343\202\241\343\202\244\343\203\253\343\201\256\350\252\255\343\201\277\350\276\274\343\201\277", 0));
        menuFile->setTitle(QApplication::translate("SpriteEditorClass", "File", 0));
        dockWidget_ImageList->setWindowTitle(QApplication::translate("SpriteEditorClass", "Image Lists", 0));
        dockWidget->setWindowTitle(QApplication::translate("SpriteEditorClass", "ImageViewer", 0));
        pushButton_ClearPoint->setText(QApplication::translate("SpriteEditorClass", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class SpriteEditorClass: public Ui_SpriteEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITEEDITOR_H
