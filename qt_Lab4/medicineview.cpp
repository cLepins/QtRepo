#include "medicineview.h"
#include "ui_medicineview.h"

MedicineView::MedicineView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MedicineView)
{
    ui->setupUi(this);
}

MedicineView::~MedicineView()
{
    delete ui;
}
