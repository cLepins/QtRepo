#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H


#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorEditView;
}

class DoctorEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditView(QWidget *parent = nullptr, int index = 0);
    ~DoctorEditView();

private slots:
    void on_pushButton_clicked(); // 完成

    void on_pushButton_2_clicked(); // 取消

private:
    Ui::DoctorEditView *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};
#endif
