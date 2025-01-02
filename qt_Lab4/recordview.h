#ifndef RECORDVIEW_H
#define RECORDVIEW_H

#include <QWidget>

namespace Ui {
class RecordView;
}

class RecordView : public QWidget
{
    Q_OBJECT

public:
    explicit RecordView(QWidget *parent = nullptr);
    ~RecordView();

private slots:
    void on_btAdd_clicked();
    void on_btEdit_clicked();
    void on_btDelete_clicked();
    void on_btSearch_clicked();
    void on_comboBox_activated(int index);
    void on_btExport_clicked();

signals:
    void goRecordEditView(int idx);

private:
    Ui::RecordView *ui;
};

#endif // RECORDVIEW_H
