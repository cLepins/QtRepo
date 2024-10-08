#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QFontComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

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
    //pubilc :unsigned long long xuandejiji
    ~MainWindow();

private:
    QLabel* flabCurFile;
    QProgressBar* progressBar;
    QSpinBox* spinFontSize;
    QFontComboBox* comboFont;
    void initUI();


private slots:
    void on_actionNew_triggered();

    void on_actionAbout_triggered();




    void on_actionBo_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
