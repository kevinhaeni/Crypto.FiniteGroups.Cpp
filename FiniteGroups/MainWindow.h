#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QCheckBox>
#include <QWheelEvent>
#include <FiniteGroup.h>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::ModuloClass ui;
	QGraphicsScene *scene;
	void wheelEvent(QWheelEvent * event);
	bool eventFilter(QObject *ob, QEvent *e);
	void resizeEvent(QResizeEvent *);
	void drawGrid(FiniteGroup* g, int xoffset, int yoffset);


	QPushButton *btnDraw;
	QPushButton *btnDrawSubgroups;

	QSpinBox *sbInput;
	QComboBox *cbOperation;
	QCheckBox *cbSubGroups;

	long maxX = 0;
	long maxY = 0;


public slots:
	void btnDraw_Clicked();
};

#endif // MAINWINDOW_H
