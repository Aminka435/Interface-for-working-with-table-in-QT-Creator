#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include <QMessageBox>

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);
    
    QObject::connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->discardButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(ui->modelLineEdit->text());
    newRow.push_back(ui->priceLineEdit->text());
    newRow.push_back(ui->spinBox->text());
    newRow.push_back(ui->comboBox->currentText());
    newRow.push_back(ui->mileagelineEdit->text());
    newRow.push_back(ui->ex_priceLineEdit->text());
    newRow.push_back(ui->comboBox_2->currentText());

    // other fields
    newRow.push_back(0);
    newRow.push_back(0);
    newRow.push_back("");
    newRow.push_back(0.0);
    newRow.push_back("");
    newRow.push_back("");
    
    QMessageBox::warning(this, "Title", "Put up for sale!");
    
    accept();
}

const QList<QVariant>& AddRowDialog::getNewRow()
{
    return newRow;
}


AddRowDialog::~AddRowDialog()
{
    delete ui;
}
