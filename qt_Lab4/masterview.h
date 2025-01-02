#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "recordview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "welcomeview.h"
#include "medicineview.h"
#include "doctoreditview.h"
#include "medicineeditview.h"
#include "recordeditview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();
public slots:
    void goLoginView();
    void goWelcomeView(bool isAdmin);
    void goDoctorView();
    // void goDepartmentView();
    void goMedicineView();
    void goPatientEditView(int rowNo);
    void goDoctorEditView(int rowNo);
    void goPatientView();
    void goPreviousView();
    void goRecordView();
    void goMedicineEditView(int rowNo);
    void goRecordEditView(int rowNo);

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    RecordView *recordView;
    MedicineView *medicineView;
    //DepartmentView *departmentView;
    LoginView *loginView;
    PatientEditView *patientEditView;
    DoctorEditView *doctorEditView;
    MedicineEditView* medicineEditView;
    RecordEditView* recordEditView;
};
#endif // MASTERVIEW_H
