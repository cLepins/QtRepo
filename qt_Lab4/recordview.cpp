#include "recordview.h"
#include "ui_recordview.h"
#include "idatabase.h"

#include <QFileDialog>

RecordView::RecordView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecordView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initRecordModel()){
        ui->tableView->setModel(iDatabase.recordTabModel);
        ui->tableView->setSelectionModel(iDatabase.theRecordSelection);
    }
}

RecordView::~RecordView()
{
    delete ui;
}

void RecordView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewRecord();
    emit goRecordEditView(currow); // 跳转到编辑界面
}

void RecordView::on_btEdit_clicked()
{
    QModelIndex curIndex = ui->tableView->currentIndex();
    emit goRecordEditView(curIndex.row());
}

void RecordView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentRecord();
}

void RecordView::on_btSearch_clicked()
{
    QString filter = QString("patientname like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchRecord(filter);
}

// void RecordView::on_comboBox_activated(int index)
// {
//     QString sortField;
//     switch (index) {
//     case 0:
//         sortField = "PATIENTNAME"; // 按病人姓名排序
//         break;
//     case 1:
//         sortField = "DOCTORNAME"; // 按医生姓名排序
//         break;
//     case 2:
//         sortField = "CREATEDTIMESTAMP"; // 按就诊日期排序
//         break;
//     default:
//         sortField = "CREATEDTIMESTAMP"; // 默认按创建时间排序
//         break;
//     }
//     IDatabase::getInstance().sortRecordList(sortField, true);
// }


void RecordView::on_comboBox_activated(int index)
{
    QString sortField;
    switch (index) {
    case 0:
        qDebug()<<"i love nana";
        sortField = "PATIENTNAME"; // 数据库字段名
        break;
    case 1:
        qDebug()<<"forever";
        sortField = "DOCTORNAME"; // 数据库字段名
        break;
    default:
        sortField = "CREATEDTIMESTAMP";
        break;
    }
    if (IDatabase::getInstance().sortRecordList(sortField, true)) {
        IDatabase &iDatabase = IDatabase::getInstance();

        ui->tableView->setModel(iDatabase.recordTabModel);
        ui->tableView->reset();
    } else {
        qDebug() << "Sorting failed!";
    }
}

void RecordView::on_btExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存为CSV", "", "CSV 文件 (*.csv);;所有文件 (*.*)");
    if (!fileName.isEmpty()) {
        IDatabase::getInstance().exportRecordData(fileName);
    }
}
