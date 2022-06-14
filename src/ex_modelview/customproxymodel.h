#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModel(QObject *parent = nullptr);

    double filterMinimumPrice() const { return minPrice; }
    void setFilterMinimumPrice(double price);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool priceInRange(double price) const;

    double minPrice;
};


#endif // CUSTOMPROXYMODEL_H
