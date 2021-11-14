#ifndef BACKTESTWIDGET_H
#define BACKTESTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class BacktestWidget;
}
QT_END_NAMESPACE

class BacktestWidget : public QWidget {
    Q_OBJECT

public:
    BacktestWidget(QWidget* parent = nullptr);
    ~BacktestWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QVector<double> calculateMA(const QVector<QVector<double>>& v, int dayCount);

private:
    Ui::BacktestWidget* ui;
    int64_t timet;
};
#endif  // BACKTESTWIDGET_H
