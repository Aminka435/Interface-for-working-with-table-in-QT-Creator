#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include "aboutdialog.h"
#include <QFileDialog>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteRowSlot()));
    QObject::connect(ui->saveButton, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(ui->modelFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilter(const QString &)));
    
    QObject::connect(ui->priceFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMinPrice(int)));
    QObject::connect(ui->priceFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFromLineEdit(int)));
    
    QObject::connect(ui->tableDetailsView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeActiveRow(QModelIndex)));
    

    
    _exampleModel = new ExampleModel(this);
    
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModelPrice = new CustomProxyModel(this);

    proxyModel->setSourceModel(_exampleModel);
    proxyModel2->setSourceModel(proxyModel);
    proxyModelPrice->setSourceModel(proxyModel2);
    
    ui->tableDetailsView->setModel(proxyModelPrice);
    ui->tableDetailsView->setSortingEnabled(true);

    proxyModel->setFilterKeyColumn(0);
    proxyModel2->setFilterKeyColumn(3);

    
}

void MainWindow::showAbout()
{
    AboutDialog d;
    d.exec();
}

void MainWindow::updateFromLineEdit(int value)
{
    ui->priceFromLineEdit->setText(QVariant(value).toString());
}


void MainWindow::deleteRowSlot()
{
    QModelIndex idx1 = ui->tableDetailsView->currentIndex();
    QModelIndex idx2 = proxyModelPrice->mapToSource(idx1);
    QModelIndex idx3 = proxyModel2->mapToSource(idx2);
    QModelIndex idx4 = proxyModel->mapToSource(idx3);
    _exampleModel->removeRow(idx4.row());
    
}

void MainWindow::updateFilterMinPrice(int value)
{
    proxyModelPrice->setFilterMinimumPrice(value);
    
}


void MainWindow::updateFilter(const QString & text)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(text));
}
void MainWindow::updateFilter2(const QString & text)
{
    proxyModel2->setFilterFixedString(text);
}


void MainWindow::loadFile()
{
    delete _exampleModel;
    
    _exampleModel = new ExampleModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    

    proxyModel->setSourceModel(_exampleModel);

}


void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->saveDataTableToFile(fileName);

}

void MainWindow::addRowSlot()
{
    AddRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _exampleModel->appendRow(d.getNewRow());
         ui->tableDetailsView->hideColumn(proxyModel->columnCount() - 1);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    
}


void MainWindow::on_priceFromSlider_valueChanged(int value)
{
    
}


void MainWindow::changeActiveRow(const QModelIndex &index)
{
    int row = index.row();
    int column = 5;
    
    QModelIndex ageIndex = _exampleModel->index(row, column);
    
    QVariant ageData = _exampleModel->data(ageIndex);
    
}

void MainWindow::on_mostExpensiveButton_clicked()
{
    ui->tableDetailsView->sortByColumn(1,Qt::DescendingOrder);
}


void MainWindow::on_leastExpensiveButton_clicked()
{
    ui->tableDetailsView->sortByColumn(1,Qt::AscendingOrder);
}


void MainWindow::on_alphabeticOrderButton_clicked()
{
    ui->tableDetailsView->sortByColumn(0,Qt::AscendingOrder);
}

