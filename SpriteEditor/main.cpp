
#include <crtdbg.h>
#include "spriteeditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	// ���������[�N���o
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	QApplication a(argc, argv);
	SpriteEditor w;
	w.show();
	return a.exec();
}
