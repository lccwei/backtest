#include "titlewidget.h"
#include "ui_titlewidget.h"

titleWidget::titleWidget(QWidget* parent) : QWidget(parent), ui(new Ui::titleWidget) {
    ui->setupUi(this);
}

titleWidget::~titleWidget() {
    delete ui;
}

void titleWidget::setValue(LiteApi::IBackTtestResult& back) {
    ui->absic->setText(QString::number(back.stat.absRtn()));
    ui->grtic->setText(QString::number(back.stat.totRtn()));
    ui->anliic->setText(QString::number(back.stat.anualRtn()));
    ui->revic->setText(QString::number(back.stat.relRtn()));
    ui->alpha->setText(QString::number(back.stat.alpha()));
    ui->beta->setText(QString::number(back.stat.beta()));
    ui->infort->setText(QString::number(back.stat.infoRto()));
    ui->shart->setText(QString::number(back.stat.sharp()));
    ui->retvol->setText(QString::number(back.stat.rtnWave()));
    ui->maxdra->setText(QString::number(back.stat.maxDrawdown()));
}

void titleWidget::on_pushButton_clicked() {}
