#include"Practice.h"
Practice::Practice(QWidget *parent) :QWidget(parent) {
	ui.setupUi(this);
	iniUI();
	QObject::connect(ui.actFix, SIGNAL(toggled(bool)), this, SLOT(onActFixToggled(bool)));
}
Practice::~Practice() {
	QMessageBox::information(this, "Test", "executing destructor:~Practice()", QMessageBox::Ok);
}

void Practice::iniUI() {
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setPalette(QPalette(Qt::black));
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
	this->addAction(ui.actFix);
	this->addAction(ui.actQuit);
	setAutoFillBackground(true);
}

void Practice::onActFixToggled(bool rotate) {
	startRotate = rotate;
}
void Practice::paintEvent(QPaintEvent *event) {
	int w = width(), h = height();
	QPainter painter(this);
	painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
	/*5分之1弧度*/
	double angle = 2 * PI / 5;
	double radius = w / 6.0;
	/*显示器上Y轴朝下
	圆心坐标为0，0*/
	QPoint points[5] = {
		QPoint(radius,0),
		QPoint(radius * std::cos(angle),-radius * std::sin(angle)),
		QPoint(radius * std::cos(angle * 2),-radius * std::sin(angle * 2)),
		QPoint(radius * std::cos(angle * 3),-radius * std::sin(angle * 3)),
		QPoint(radius * std::cos(angle * 4),-radius * std::sin(angle * 4)),
	};
	QFont font;
	font.setPointSize(12);
	font.setBold(true);
	painter.setFont(font);

	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::yellow);
	pen.setStyle(Qt::SolidLine);
	painter.setPen(pen);

	QBrush brush;
	brush.setColor(Qt::red);
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);

	QPainterPath path;
	path.moveTo(points[0]);
	path.lineTo(points[2]);
	path.lineTo(points[4]);
	path.lineTo(points[1]);
	path.lineTo(points[3]);
	path.closeSubpath();
	path.addText(points[0], font, "1 >");
	for (int i = 1; i < 5; ++i)
		path.addText(points[i], font, QString("%1").arg(i + 1));
	painter.save();
	painter.translate(200, 200);
	/*偏移之后的圆心坐标*/
	QPoint centerPos(200, 200);
	double cursorAngle = std::atan2((lastPos - centerPos).y(), (lastPos - centerPos).x());
	if(startRotate)
		painter.rotate(cursorAngle * (180 / PI));
	painter.drawPath(path);
	painter.restore();

	painter.save();
	painter.translate(400, 400);
	centerPos = QPoint(400, 400);
	cursorAngle = std::atan2((lastPos - centerPos).y(), (lastPos - centerPos).x());
	if (startRotate)
		painter.rotate(cursorAngle * (180 / PI));
	painter.drawPath(path);
	painter.restore();

	painter.save();
	painter.translate(600, 130);
	centerPos = QPoint(600, 130);
	cursorAngle = std::atan2((lastPos - centerPos).y(), (lastPos - centerPos).x());
	if (startRotate)
		painter.rotate(cursorAngle * (180 / PI));
	painter.drawPath(path);
	painter.restore();

	pen.setColor(Qt::red);
	painter.setPen(pen);
	QFontMetrics fontMT(font);
	painter.drawText(0,fontMT.height() , QString("coordinate:%1 %2").arg(lastPos.x(),4).arg(lastPos.y(),4));
}
void Practice::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		moving = true;
		lastRelPos = event->globalPos() - this->pos();
	}
	return QWidget::mousePressEvent(event);
}
void Practice::mouseMoveEvent(QMouseEvent *event) {
	QPoint newWindowPos = event->globalPos() - lastRelPos;
	if (moving && (event->buttons() & Qt::LeftButton) && (newWindowPos - this->pos()).manhattanLength() >= QApplication::startDragDistance()) {
		this->move(newWindowPos);
		lastRelPos = event->globalPos() - newWindowPos;
	}
	lastPos = event->pos();
	update();
	return QWidget::mouseMoveEvent(event);
}
void Practice::mouseReleaseEvent(QMouseEvent *event) {
	moving = false;
	return QWidget::mouseReleaseEvent(event);
}