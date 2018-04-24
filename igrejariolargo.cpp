#include "igrejariolargo.h"

IgrejaRioLargo::IgrejaRioLargo(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant IgrejaRioLargo::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex IgrejaRioLargo::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex IgrejaRioLargo::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int IgrejaRioLargo::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int IgrejaRioLargo::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant IgrejaRioLargo::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
