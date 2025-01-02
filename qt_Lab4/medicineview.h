#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QWidget>

namespace Ui {
class MedicineView;
}

class MedicineView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineView(QWidget *parent = nullptr);
    ~MedicineView();

private slots:
    void on_btAdd_clicked();
    void on_btSearch_clicked();
    void on_btDelete_clicked();
    void on_btEdit_clicked();
    void on_comboBox_activated(int index);
    void on_btExport_clicked();
    void on_btImport_clicked();

signals:
    void goMedicineEditView(int idx);

private:
    Ui::MedicineView *ui;
};

#endif // MEDICINEVIEW_H

