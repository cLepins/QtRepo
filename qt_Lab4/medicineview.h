#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QDialog>

namespace Ui {
class MedicineView;
}

class MedicineView : public QDialog
{
    Q_OBJECT

public:
    explicit MedicineView(QWidget *parent = nullptr);
    ~MedicineView();

private:
    Ui::MedicineView *ui;
};

#endif // MEDICINEVIEW_H
