#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include "backtestapi.h"
namespace Ui {
class titleWidget;
}

class titleWidget : public QWidget {
    Q_OBJECT

public:
    explicit titleWidget(QWidget* parent = nullptr);
    ~titleWidget();
    void setValue(LiteApi::IBackTtestResult& back);

private slots:
    void on_pushButton_clicked();

private:
    Ui::titleWidget* ui;
};

#endif  // TITLEWIDGET_H
