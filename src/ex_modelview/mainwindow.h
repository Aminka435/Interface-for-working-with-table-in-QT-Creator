#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "examplemodel.h"
#include "customproxymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void loadFile();
    void saveFile();
    void addRowSlot();
    
    void on_tableView_doubleClicked(const QModelIndex &index);
    void updateFilter(const QString & text);
    void updateFilter2(const QString & text);
    void updateFilterMinPrice(int value);
    void updateFromLineEdit(int value);
    void showAbout();
    
    void deleteRowSlot();
    void on_priceFromSlider_valueChanged(int value);
    
    void changeActiveRow(const QModelIndex &index);

    void on_mostExpensiveButton_clicked();

    void on_leastExpensiveButton_clicked();

    void on_alphabeticOrderButton_clicked();


private:
    size_t _shownDetailsColumn;
    ExampleModel *_exampleModel;
    QSortFilterProxyModel *proxyModel;
    QSortFilterProxyModel *proxyModel2;
    CustomProxyModel *proxyModelPrice;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
