#ifndef IGREJARIOLARGO_H
#define IGREJARIOLARGO_H

#include <QAbstractItemModel>

class IgrejaRioLargo : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit IgrejaRioLargo(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // IGREJARIOLARGO_H