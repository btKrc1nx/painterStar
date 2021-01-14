#pragma once
#include"preCompile.h"
#include"ui_Practice.h"
#include<QtWidgets/QMainWindow>
#define PI (4*atan(1))
class Practice :public QWidget {
	Q_OBJECT
public:
	Practice(QWidget *parent = nullptr);
	~Practice();
private:
	void iniUI();
	Ui::Practice ui;
	QPoint lastPos;
	QPoint lastRelPos;
	bool moving = false;
	bool startRotate = true;
private slots:
	void onActFixToggled(bool rotate);
protected:
	void paintEvent(QPaintEvent *event)override;
	void mousePressEvent(QMouseEvent *event)override;
	void mouseMoveEvent(QMouseEvent *event)override;
	void mouseReleaseEvent(QMouseEvent *event)override;
};