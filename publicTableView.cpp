#include "publicTableView.h"
#include "publicTableModel.h"
#include <QHeaderView>

publicTableView::publicTableView(QWidget* parent) : QTableView(parent) {
    m_model = new publicTableModel();
    setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选中模式为选中行
    this->setModel(m_model);
}

void publicTableView::iniData(QStringList& headers, QVector<QStringList>& data) {
    m_model->setHorizontalHeader(headers);
    m_model->setData(data);
    emit m_model->layoutChanged();
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->resizeColumnsToContents();
    this->horizontalHeader()->setStretchLastSection(true);
}
void publicTableView::updataValue(QVector<QStringList>& value) {
    QVector<QStringList>& data = m_model->DataVector();
    data = value;
    emit m_model->layoutChanged();
}

void publicTableView::updataRowValue(int& row, QStringList& value) {
    QVector<QStringList>& data = m_model->DataVector();
    if (data.size() > row) {
        QStringList& v = data[row];
        v = value;
        emit m_model->layoutChanged();
    }
}

int publicTableView::getCurrentRow() {
    QModelIndexList list = this->selectedIndexes();
    if (list.count() <= 0)
        return -1;
    return this->selectionModel()->currentIndex().row();
}
