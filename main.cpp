#include"Practice.h"
#include<QApplication>
int main(int argc, char *argv[]) {
	/*����locale���뷽ʽ*/
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
	QApplication app(argc, argv);
	Practice w;
	w.show();
	return app.exec();
}