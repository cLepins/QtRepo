#ifndef MEDICINEEDITVIEW_H
#define MEDICINEEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class MedicineEditView;
}

class MedicineEditView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineEditView(QWidget *parent = nullptr, int index = 0);
    ~MedicineEditView();

private slots:
    void on_pushButton_clicked(); // 完成
    void on_pushButton_2_clicked(); // 取消

private:
    Ui::MedicineEditView *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // MEDICINEEDITVIEW_H

