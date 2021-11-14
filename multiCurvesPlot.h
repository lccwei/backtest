#ifndef MULTICURVESPLOT_H
#define MULTICURVESPLOT_H

#include "qcustomplot.h"
#define keyPress 50000
class multiCurvesPlot : public QCustomPlot {
    Q_OBJECT
public:
    multiCurvesPlot(QWidget* parent = nullptr);
    void setXValue(QVector<QString>& rawTimes) {
        rawTimes_ = rawTimes;
    }
    void getXYValue(int64_t& x, double& y);
public slots:
    void slotDoubleClicked(QMouseEvent*);

protected:
    // virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* pEvent) override;
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    void setTracer(double& x);
signals:
    void enterKeyPress(int64_t&, double&);

public:
private:
    QVector<QString> rawTimes_;
    QCPItemTracer* plottracer;
    QCPItemText* textLabel;
    double x = 0;
};

#endif  // MULTICURVESPLOT_H
