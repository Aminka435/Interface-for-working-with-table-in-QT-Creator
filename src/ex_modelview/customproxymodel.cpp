#include "customproxymodel.h"

CustomProxyModel::CustomProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    minPrice = -1;
}


bool CustomProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex indexPrice = sourceModel()->index(sourceRow, 1, sourceParent);

    return priceInRange(sourceModel()->data(indexPrice).toDouble());
}

bool CustomProxyModel::priceInRange(double price) const
{
    return price >= minPrice;
}

void CustomProxyModel::setFilterMinimumPrice(double price)
{
    minPrice = price;
    invalidateFilter();
}

