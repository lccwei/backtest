#include "multiCurvesPlot.h"

multiCurvesPlot::multiCurvesPlot(QWidget* parent) : QCustomPlot(parent) {
    plottracer = new QCPItemTracer(this);
    this->setMouseTracking(true);
    //设置追踪曲线
    plottracer->setGraph(this->graph(0));
    //设置十字浮标样式
    QPen* pen = new QPen;
    pen->setColor(QColor(Qt::black));  //黄色
    pen->setStyle(Qt::DashLine);       //虚线
    plottracer->setPen(*pen);
    textLabel = new QCPItemText(this);
    //下面的代码就是设置游标说明的外观和对齐方式等状态
    textLabel->setLayer("overlay");
    textLabel->setPen(QPen(Qt::black));
    textLabel->setBrush(Qt::cyan);
    textLabel->setPadding(QMargins(2, 2, 2, 2));  //边界宽度
    textLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    //下面这个语句很重要，它将游标说明锚固在tracer位置处，实现自动跟随
    textLabel->position->setParentAnchor(plottracer->position);
}

void multiCurvesPlot::getXYValue(int64_t& x, double& y) {
    x = plottracer->position->key();
    y = plottracer->position->value();
}

void multiCurvesPlot::slotDoubleClicked(QMouseEvent*) {

    int64_t traceX = plottracer->position->key();
    double traceY = plottracer->position->value();
    qDebug() << traceX << traceY;
}

// void multiCurvesPlot::mousePressEvent(QMouseEvent* event) {
//    QCustomPlot::mouseReleaseEvent(event);

//    if (event->button() == Qt::LeftButton) {
//        auto traceX = plottracer->position->key();
//        double traceY = plottracer->position->value();
//        qDebug() << traceX << traceY;
//    }
//}

void multiCurvesPlot::mouseMoveEvent(QMouseEvent* pEvent) {
    QCustomPlot::mouseMoveEvent(pEvent);  //避免让父类的移动事件失效

    x = xAxis->pixelToCoord(pEvent->pos().x());  //鼠标点的像素坐标转plot坐标
    setTracer(x);
}

void multiCurvesPlot::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        x -= keyPress;
        setTracer(x);
    } else if (event->key() == Qt::Key_Right) {
        x += keyPress;
        setTracer(x);
    } else if (event->key() == Qt::Key_Return) {
        int64_t x = plottracer->position->key();
        auto y = plottracer->position->value();
        emit enterKeyPress(x, y);
    }
}

void multiCurvesPlot::setTracer(double& x) {
    plottracer->setGraph(this->graph(0));  //设置游标吸附在traceGraph这条曲线上
    plottracer->setGraphKey(x);  //设置游标的X值（这就是游标随动的关键代码）
    QSharedPointer<QCPGraphDataContainer> tmpContainer;
    auto traceX = plottracer->position->key();
    double traceY = plottracer->position->value();
    QString name = this->graph(0)->name();
    for (int i = 0; i < this->graphCount(); ++i) {
        QCPGraph* graph = this->graph(i);
        QCPPlottableLegendItem* item = this->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected()) {
            plottracer->setGraph(this->graph(i));  //设置游标吸附在traceGraph这条曲线上
            plottracer->setGraphKey(x);
            traceX = plottracer->position->key();
            traceY = plottracer->position->value();
            name = this->graph(i)->name();
        }
    }

    textLabel->setText(QDateTime::fromTime_t(traceX).toString("yyyy/MM/dd") + "\n" + name + ": "
                       + QString::number(traceY));  //游标文本框，指示游标的Y值
    this->replot();
}
