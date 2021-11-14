#ifndef PUBLICTABLEVIEW_H
#define PUBLICTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QString>
class publicTableModel;

class publicTableView : public QTableView {
    Q_OBJECT
public:
    explicit publicTableView(QWidget* parent = 0);
    publicTableModel* tableModel() {
        return m_model;
    };
    /**
     * @brief  初始化数据
     */
    void iniData(QStringList& headers, QVector<QStringList>& data);
    void updataValue(QVector<QStringList>& value);
    void updataRowValue(int& row, QStringList& value);
    int getCurrentRow();

private:
    publicTableModel* m_model;
};

#endif  // PUBLICTABLEVIEW_H
