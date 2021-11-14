#include "customplotWidget.h"

customplotWidget::customplotWidget(QWidget* parent) : QWidget(parent) {}

void customplotWidget::initPlot(QStringList& names) {
    customPlot_ = new multiCurvesPlot(this);
    QCPDataContainer<QCPFinancialData> datas;

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::LocalTime);
    dateTimeTicker->setDateTimeFormat("yyyy/MM/dd");
    dateTimeTicker->setTickOrigin(QDateTime::currentDateTime());
    dateTimeTicker->setTickCount(13);
    //    QCPFinancial* financial = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    //    financial->setName("dayK");
    //    financial->setBrushPositive(BrushPositive);
    //    financial->setPenPositive(PenPositive);
    //    financial->setBrushNegative(BrushNegative);
    //    financial->setPenNegative(PenNegative);
    //    financial->data()->set(datas);
    int i = 0;
    QCPGraph* graph = nullptr;
    for (auto name : names) {
        graph = customPlot_->addGraph();
        QPen pen(QColor(qSin(i * 0.3) * 100 + 100,
                        qSin(i * 0.6 + 0.7) * 100 + 100,
                        qSin(i * 0.4 + 0.6) * 100 + 100),
                 2);
        i += 5;

        graph->setName(name);
        graph->setPen(pen);
        graph->setScatterStyle(
            QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(Qt::red + i), QColor(Qt::white), 6));
        graph->setSmooth(true);  // 开启平滑曲线
        graphs_.push_back(graph);
    }

    customPlot_->xAxis->setTicker(dateTimeTicker);
    customPlot_->rescaleAxes();
    customPlot_->xAxis->scaleRange(1.05, customPlot_->xAxis->range().center());
    customPlot_->yAxis->scaleRange(1.05, customPlot_->yAxis->range().center());
    customPlot_->legend->setVisible(true);
    customPlot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes
                                 | QCP::iSelectLegend | QCP::iSelectPlottables);
    customPlot_->axisRect()->setRangeZoomFactor(1.2, 2.2);
    auto gridLayout = new QVBoxLayout(this);
    gridLayout->addWidget(customPlot_, 1, 0);
    setLayout(gridLayout);
    connect(customPlot_,
            SIGNAL(mouseDoubleClick(QMouseEvent*)),
            this,
            SLOT(slotDoubleClicked(QMouseEvent*)));
}

void customplotWidget::iniDatas(QVector<double>& rawTimes,
                                QVector<QVector<double>>& rawDatas,
                                QStringList& names) {
    customPlot_ = new multiCurvesPlot(this);
    QCPDataContainer<QCPFinancialData> datas;

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::LocalTime);
    dateTimeTicker->setDateTimeFormat("yyyy/MM/dd");
    dateTimeTicker->setTickOrigin(QDateTime::currentDateTime());
    dateTimeTicker->setTickCount(15);
    //    QCPFinancial* financial = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    //    financial->setName("dayK");
    //    financial->setBrushPositive(BrushPositive);
    //    financial->setPenPositive(PenPositive);
    //    financial->setBrushNegative(BrushNegative);
    //    financial->setPenNegative(PenNegative);
    //    financial->data()->set(datas);
    QVector<QColor> ColorOptions = { "#c23531", "#2f4554", "#61a0a8", "#d48265" };
    int i = 0, s = 0;
    QCPGraph* graph = nullptr;
    for (auto data : rawDatas) {
        graph = customPlot_->addGraph();
        QPen pen(QColor(qSin(i * 0.3) * 100 + 100,
                        qSin(i * 0.6 + 0.7) * 100 + 100,
                        qSin(i * 0.4 + 0.6) * 100 + 100),
                 2);
        i += 5;
        if (names.size() > s)
            graph->setName(names.at(s));
        graph->setPen(pen);
        graph->setScatterStyle(
            QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(Qt::red + i), QColor(Qt::white), 6));
        // graph->setData(timeDatas, MA5Datas);
        graph->setData(rawTimes, data);
        // graph->setSmooth(true);  // 开启平滑曲线
        graphs_.push_back(graph);
        s++;
    }

    customPlot_->xAxis->setTicker(dateTimeTicker);
    customPlot_->rescaleAxes();
    //    customPlot_->xAxis->scaleRange(1.05, customPlot_->xAxis->range().center());
    //    customPlot_->yAxis->scaleRange(1.05, customPlot_->yAxis->range().center());
    customPlot_->legend->setVisible(true);
    //    customPlot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes
    //                                 | QCP::iSelectLegend | QCP::iSelectPlottables);
    customPlot_->axisRect()->setRangeZoomFactor(1.2, 2.2);
    auto gridLayout = new QVBoxLayout(this);
    gridLayout->addWidget(customPlot_, 1, 0);
    setLayout(gridLayout);
    connect(customPlot_,
            SIGNAL(mouseDoubleClick(QMouseEvent*)),
            this,
            SLOT(slotDoubleClicked(QMouseEvent*)));
    connect(customPlot_, &multiCurvesPlot::enterKeyPress, [this](int64_t& x, double& y) {
        qDebug() << x << y;
        emit sigDoubleClicked(x, y);
    });

    // connect(customPlot_, SIGNAL(mouseWheel(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(customPlot_->xAxis,
            SIGNAL(rangeChanged(const QCPRange&)),
            this,
            SLOT(onYAxisRangeChange(const QCPRange&)));
}

void customplotWidget::addDatas(QVector<double>& rawTimes, QVector<QVector<double>>& rawDatas) {
    int i = 0;
    for (auto time : rawTimes) {
        int s = 0;
        for (auto it : rawDatas) {
            addData(graphs_[s], time, it[i]);
            s++;
        }
        i++;
    }
    customPlot_->replot();
}

void customplotWidget::clearDatas() {
    for (auto gr : graphs_) {
        gr->data().data()->clear();
    }
    customPlot_->replot();
}

void customplotWidget::slotDoubleClicked(QMouseEvent*) {
    int64_t x = 0;
    double y = 0.0;
    customPlot_->getXYValue(x, y);
    qDebug() << x << y;
    emit sigDoubleClicked(x, y);
}

void customplotWidget::onYAxisRangeChange(const QCPRange& range) {
    //    auto new_range = range * 1.025;
    //    customPlot_->yAxis->setRange(new_range);

    bool find = false;
    auto k_range = graphs_.first()->getKeyRange(find);
    QCPRange new_x_range = range;

    new_x_range.lower = k_range.lower < range.lower ? k_range.lower : range.lower;
    new_x_range.upper = k_range.upper > range.upper ? k_range.upper : range.upper;

    QCPRange y_range;

    bool first = true;
    for (auto& gr : graphs_) {
        find = false;
        auto rg = gr->getValueRange(find, QCP::sdBoth, new_x_range);
        if (first) {
            y_range = rg;
            first = false;
        } else if (find) {
            y_range.upper = rg.upper > y_range.upper ? rg.upper : y_range.upper;
            y_range.lower = rg.lower < y_range.lower ? rg.lower : y_range.lower;
        }
    }
    y_range *= 1.01;
    customPlot_->yAxis->setRange(y_range);
    customPlot_->xAxis->setRange(new_x_range);
    customPlot_->replot();
}

void customplotWidget::onEnterKeyPress() {
    int64_t x = 0;
    double y = 0.0;
    customPlot_->getXYValue(x, y);
    qDebug() << x << y;
    emit sigDoubleClicked(x, y);
}

// void customplotWidget::mousePress(QCPRange) {
//    customPlot_->yAxis->setRangeLower(0);
//    customPlot_->yAxis->setRangeUpper(100000.0);
//    // customPlot_->xAxis->setRangeLower(0);
//}

void customplotWidget::addData(QPointer<QCPGraph> graph, double key, double value) {
    graph->data()->add(QCPGraphData(key, value));
}
