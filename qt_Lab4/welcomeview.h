#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();

private slots:

    void on_btDoctor_clicked();

    void on_btPatient_clicked();
    void on_btRecord_clicked();

    void on_btMedicine_clicked();

signals:
    void goDoctorView();
    void goPatientView();
    void goRecordView();
    void goMedicineView();
private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H
