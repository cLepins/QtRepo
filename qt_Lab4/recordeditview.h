#ifndef RECORDEDITVIEW_H
#define RECORDEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class RecordEditView;
}

class RecordEditView : public QWidget
{
    Q_OBJECT

public:
    explicit RecordEditView(QWidget *parent = nullptr,int index = 0);
    ~RecordEditView();

private:
    Ui::RecordEditView *ui;
    QDataWidgetMapper *dataMapper;


private slots:
    void on_pushButton_clicked();//完成

    void on_pushButton_2_clicked();//取消

signals:
    void goPreviousView();

};

#endif // RECORDEDITVIEW_H
