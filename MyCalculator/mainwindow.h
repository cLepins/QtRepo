#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QKeyEvent>
#include <math.h>
#include <QMap>
#include <QPushButton>

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

    void btnSigleOperandClicked();
    void keyPressEvent(QKeyEvent* event);

    void on_delButton_clicked();

    void on_clearButton_clicked();

    void on_CeButton_clicked();

    void on_modeButton_clicked();

    void on_dotButton_clicked();

    void on_zeroButton_clicked();



    void on_equalButton_clicked();

private:
    Ui::MainWindow *ui;
    QString Edit;
    QStack<QString> operands_;
    QStack<QString> opercodes_;
    QMap<int,QPushButton*> btnNums;

};
#endif // MAINWINDOW_H
