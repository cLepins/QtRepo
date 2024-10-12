#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QString>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString calculation();
private slots:

    void btnNumClicked();
    void btnOperandClicked();

    void on_mutiplyButton_clicked();

    void on_minusButton_clicked();

    void on_plusButton_clicked();

    void on_equalButton_clicked();

    void on_divideButton_clicked();

    void on_delButton_clicked();

    void on_clearButton_clicked();

    void on_CeButton_clicked();

    void on_modeButton_clicked();

    void on_dotButton_clicked();

    void on_zeroButton_clicked();



    void on_fenshuButton_clicked();

    void on_doubleXButton_clicked();

private:
    Ui::MainWindow *ui;
    QString Edit;
    QStack<QString> operands_;
    QStack<QString> opercodes_;
};
#endif // MAINWINDOW_H
