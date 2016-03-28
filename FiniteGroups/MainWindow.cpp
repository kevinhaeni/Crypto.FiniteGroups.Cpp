#include "MainWindow.h"
#include <FiniteGroup.h>
#include <MathUtils.h>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.btnDraw, SIGNAL(clicked()), this, SLOT(btnDraw_Clicked()));

	scene = new QGraphicsScene(this);

	ui.graphicsView->setScene(scene);
	ui.graphicsView->viewport()->installEventFilter(this);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing);
	ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	
	ui.graphicsView->scale(qreal(1.0), qreal(1.0));
	ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	QString s = "Addition";
	QString s2 = "Multiplication";
	QString s3 = "Exponentiation";

	ui.cbOperation->addItem(s);
	ui.cbOperation->addItem(s2);
	ui.cbOperation->addItem(s3);
}


MainWindow::~MainWindow()
{

}

bool MainWindow::eventFilter(QObject *ob, QEvent *e)
{
	if (ob == ui.graphicsView->viewport() && e->type() == QEvent::Wheel) {
		//return true;
	}
	return false;
}

void  MainWindow::wheelEvent(QWheelEvent * event)
{
	ui.graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	// Scale the view / do the zoom
	double scaleFactor = 1.15;
	if (event->delta() > 0) {
		// Zoom in
		ui.graphicsView->scale(scaleFactor, scaleFactor);

	}
	else {
		// Zooming out
		ui.graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
	}


	//ui->graphicsView->setTransform(QTransform(h11, h12, h21, h22, 0, 0));
}

void MainWindow::drawGrid(FiniteGroup* g, int global_xOffset, int global_yOffset){

	// setup QGraphicScene objects
	QBrush whiteBrush(Qt::white);
	QBrush grayBrush(QColor(222,222,222));
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(1);

	const int RECTSIZE = 80;
	const int TEXTMARGIN = 20;
	const int TITLEMARGIN = 80;
	
	QGraphicsTextItem* title = scene->addText(QString::fromStdWString(L"ℤ"));
	title->setFont(QFont("Arial", 20));
	title->setPos(TEXTMARGIN + 5, TEXTMARGIN + 5 + global_yOffset);
	QGraphicsTextItem* modulo = scene->addText(QString::fromStdString(std::to_string(g->getModulo())));
	modulo->setFont(QFont("Arial", 10));
	modulo->setPos(TEXTMARGIN + 20, TEXTMARGIN + 22 + global_yOffset);
	QGraphicsTextItem* order = scene->addText(QString::fromStdString('|' + std::to_string(g->getOrder()) + '|'));
	order->setFont(QFont("Arial", 12));
	order->setPos(TEXTMARGIN + 10, TEXTMARGIN + 40 + global_yOffset);
	
	// draw y-axis titles (group elements)
	int counter = 0;
	for (Element element : g->getElements()){
		QString strText;
		if (element.isGenerator())
			strText = QString::fromStdString(std::to_string(element.getSymbol()));
		else
			strText = QString::fromStdString(std::to_string(element.getSymbol()));
		QGraphicsTextItem* text = scene->addText(strText);
		if (element.isGenerator()){
			text->setDefaultTextColor(QColor(255, 0, 0));		// red font for generators
		}
		text->setFont(QFont("Arial", 20));
		text->setPos(TEXTMARGIN, counter++ * RECTSIZE + RECTSIZE + TEXTMARGIN + global_yOffset);

		QGraphicsTextItem* order = scene->addText(QString::fromStdString("ord(" + std::to_string(element.getOrder()) + ')'));
		order->setFont(QFont("Arial", 12));
		order->setPos(TEXTMARGIN + 5, (counter-1) * RECTSIZE + RECTSIZE + TEXTMARGIN + 35 + global_yOffset);
	}


	if (g->getOperator() == FiniteGroup::EXPONENTIATION){
		
		const int MAX_EXPONENT = 20;

		// draw x-axis titles (exponents)
		for (int i = 1; i <= MAX_EXPONENT; i++){
			QGraphicsTextItem* text = scene->addText(QString::fromStdString(std::to_string(i)));
			text->setFont(QFont("Arial", 20));
			text->setPos(i * RECTSIZE + TEXTMARGIN, TEXTMARGIN + global_yOffset);
		}

		// do calculations
		unsigned int **matrix = new unsigned int*[g->getOrder()];
		for (int i = 0; i < g->getOrder(); ++i){
			matrix[i] = new unsigned int[MAX_EXPONENT];		// initialize 2 dimensional array
		}


		for (int i = 0; i < g->getElements().size(); i++){
			for (unsigned int exp = 1; exp <= MAX_EXPONENT; exp++){
				unsigned int base = g->getElement(i).getSymbol();
				unsigned int result = MathUtils::modpow(base, exp, g->getModulo());
				matrix[i][exp-1] = result;
			}
		}


		// draw matrix
		int i = 0;
		for (Element element: g->getElements()){
			for (int j = 0; j < MAX_EXPONENT; j++){
				QBrush bgColor;

				if (matrix[i][j] == g->getInverseElement())
					bgColor = grayBrush;
				else
					bgColor = whiteBrush;

				auto rectangle = scene->addRect(j*RECTSIZE + TITLEMARGIN, i * RECTSIZE + TITLEMARGIN + global_yOffset, RECTSIZE, RECTSIZE, outlinePen, bgColor);

				if (maxX < j*RECTSIZE + TITLEMARGIN + global_xOffset)
					maxX = j*RECTSIZE + TITLEMARGIN + RECTSIZE + global_xOffset;

				if (maxY < i*RECTSIZE + TITLEMARGIN + global_yOffset)
					maxY = i*RECTSIZE + TITLEMARGIN + global_yOffset;

				QGraphicsTextItem* text = scene->addText(QString::fromStdString(std::to_string(matrix[i][j])));
				text->setFont(QFont("Arial", 20));				
				text->setPos(j * RECTSIZE + TEXTMARGIN + TITLEMARGIN, i * RECTSIZE + TEXTMARGIN + TITLEMARGIN + global_yOffset);
			}
			i++;
		}

	}
	else{
		// pre-calculate operation matrix
		unsigned int **matrix = new unsigned int*[g->getOrder()];
		for (int i = 0; i < g->getOrder(); ++i)
			matrix[i] = new unsigned int[g->getOrder()];		// initialize 2 dimensional array


		for (int i = 0; i < g->getOrder(); i++){
			for (int j = 0; j < g->getOrder(); j++){
				if (g->getOperator() == FiniteGroup::ADDITION)
				{
					matrix[i][j] = (g->getElement(i).getSymbol() + g->getElement(j).getSymbol()) % g->getModulo();
				}
				else{
					matrix[i][j] = (g->getElement(i).getSymbol() * g->getElement(j).getSymbol()) % g->getModulo();
				}
			
			}
		}

		// Draw title row/col
		for (int i = 0; i < g->getOrder(); i++){
			
			QGraphicsTextItem* text = scene->addText(QString::fromStdString(std::to_string(g->getElement(i).getSymbol())));
			text->setFont(QFont("Arial", 20));
			text->setPos(TEXTMARGIN + RECTSIZE*i + RECTSIZE, TEXTMARGIN + global_yOffset);
		}
		// draw matrix
		for (int i = 0; i < g->getOrder(); i++){

			for (int j = 0; j < g->getOrder(); j++){
				QBrush bgColor;

				if (matrix[i][j] == g->getInverseElement())
					bgColor = grayBrush;
				else
					bgColor = whiteBrush;

				auto rectangle = scene->addRect(i*RECTSIZE + TITLEMARGIN, j * RECTSIZE + TITLEMARGIN + global_yOffset, RECTSIZE, RECTSIZE, outlinePen, bgColor);

				if (maxX < i*RECTSIZE + TITLEMARGIN + global_xOffset)
					maxX = i*RECTSIZE + TITLEMARGIN + RECTSIZE + global_xOffset;

				if (maxY < j * RECTSIZE + TITLEMARGIN + global_yOffset)
					maxY = j * RECTSIZE + TITLEMARGIN + RECTSIZE + global_yOffset;


				QGraphicsTextItem* text = scene->addText(QString::fromStdString(std::to_string(matrix[i][j])));
				text->setFont(QFont("Arial", 20));
				text->setPos(i * RECTSIZE + TEXTMARGIN + TITLEMARGIN, j * RECTSIZE + TEXTMARGIN + TITLEMARGIN + global_yOffset);
			}
		}


	}	
}

void MainWindow::btnDraw_Clicked(){
	// Reset view
	scene->clear();
	ui.graphicsView->viewport()->update();
	//scene->setSceneRect(0, 0, ui.graphicsView->width()*2, ui.graphicsView->height()*2);

	// Get group parameters from textfields
	auto order = ui.sbInput->value();
	auto op = ui.cbOperation->currentIndex();

	// Build group
	FiniteGroup* g;

	switch (op){
	case FiniteGroup::ADDITION:
		g = new FiniteGroup(order, FiniteGroup::ADDITION);
		break;
	case FiniteGroup::MULTIPLICATION:
		g = new FiniteGroup(order, FiniteGroup::MULTIPLICATION);
		break;
	case FiniteGroup::EXPONENTIATION:
		g = new FiniteGroup(order, FiniteGroup::EXPONENTIATION);
		break;
	}	
	
	maxX = maxY = 0;
	drawGrid(g, 0, 0);

	if (ui.cbSubGroups->isChecked()){	
		// Find subgroups
		std::vector<FiniteGroup> subGroups;
		std::vector<std::vector<unsigned int>> subGroupInts;		// temporary structure to check for unique sub groups

		for (Element e : g->getElements()){
			if (g->getOrder() == e.getOrder())						// don't count G as a subgroup
				continue;

			std::vector<unsigned int> subgroupElements;
			unsigned int order = 0;
			for (unsigned int j = 1; j <= e.getOrder(); j++){
				unsigned int subgroupElement = MathUtils::modpow(e.getSymbol(), j, g->getModulo());
				subgroupElements.push_back(subgroupElement);
				order++;
			}
			std::sort(subgroupElements.begin(), subgroupElements.end());

			bool unique = true;

			// check if the subgroup is unique
			for (std::vector<unsigned int> group2 : subGroupInts){
				if (subgroupElements == group2)
					unique = false;
			}
			if (unique){
				FiniteGroup subgroup(subgroupElements, g->getModulo(), g->getOperator());
				subGroups.push_back(subgroup);
				subGroupInts.push_back(subgroupElements);

			}
		}

		// draw the subgroups
		for (FiniteGroup subGroup : subGroups){
			drawGrid(&subGroup, 0, maxY + 80);
		}
	}
}

void MainWindow::resizeEvent(QResizeEvent *) {
	QRectF bounds = scene->itemsBoundingRect();
	bounds.setWidth(bounds.width()*0.9);         // to tighten-up margins
	bounds.setHeight(bounds.height()*0.9);       // same as above
	ui.graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
	ui.graphicsView->centerOn(0, 0);
}