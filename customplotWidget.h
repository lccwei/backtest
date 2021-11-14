#ifndef CUSTOMPLOTWIDGET_H
#define CUSTOMPLOTWIDGET_H

#include <QWidget>
#include "MyAxisTickerText.h"
#include "multiCurvesPlot.h"

class customplotWidget : public QWidget {
    Q_OBJECT
public:
    explicit customplotWidget(QWidget* parent = nullptr);
    void initPlot(QStringList& names);
    void
    iniDatas(QVector<double>& rawTimes, QVector<QVector<double>>& rawDatas, QStringList& names);
    void addDatas(QVector<double>& rawTimes, QVector<QVector<double>>& rawDatas);
    void clearDatas();

public slots:
    void slotDoubleClicked(QMouseEvent*);
    void onYAxisRangeChange(const QCPRange&);
    void onEnterKeyPress();

private:
    void addData(QPointer<QCPGraph> graph, double key, double value);
signals:
    void sigDoubleClicked(int64_t&, double&);

private:
    QVector<QPointer<QCPGraph>> graphs_;
    multiCurvesPlot* customPlot_;
};

#endif  // CUSTOMPLOTWIDGET_H
