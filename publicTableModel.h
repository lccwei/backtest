#ifndef PUBLICTABLEMODEL_H
#define PUBLICTABLEMODEL_H

#include <QAbstractTableModel>

class publicTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    publicTableModel(QObject* parent = 0);
    /**
     * @brief  获取行数
     * @param QModelIndex   模板参数
     */
    int rowCount(const QModelIndex& parent) const;
    /**
     * @brief  获取列数
     * @param QModelIndex   模板参数
     */
    int columnCount(const QModelIndex& parent) const;
    /**
     * @brief  数据加载
     * @param QModelIndex   模板参数,role
     */
    QVariant data(const QModelIndex& index, int role) const;
    /**
     * @brief  设置状态
     * @param QModelIndex   模板参数
     * @return ItemFlags枚举值
     */
    Qt::ItemFlags flags(const QModelIndex& index) const;
    /**
     * @brief  设置标题
     * @param headers   标题名
     */
    void setHorizontalHeader(const QStringList& headers);
    /**
     * @brief  更新参数
     * @param headers   标题名
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /**
     * @brief  设置参数
     * @param data   详细参数
     */
    void setData(const QVector<QStringList>& data);
    QVector<QStringList>& DataVector() {
        return m_data;
    }
    ~publicTableModel(void);

signals:

public slots:

private:
    QStringList m_HorizontalHeader;
    QVector<QStringList> m_data;
};

#endif  // PUBLICTABLEMODEL_H
