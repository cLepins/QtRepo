#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_comboBox_activated(int index);

signals:
    void goPatientEditView(int idx);

private:
    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
