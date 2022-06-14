#include "aboutdialog.h"
#include "ui_aboutdialog.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    scene->addEllipse(-35, 7, 0, 7);
    scene->addLine(0, 5, 7, 9);
    scene->addLine(0, 0, 0, 0);
    scene-> addEllipse(4, 8, 9, 0);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
