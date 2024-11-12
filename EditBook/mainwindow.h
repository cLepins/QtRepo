#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
private:
    bool userEditConfirmed();
private slots:

    void on_actionAbout_triggered();

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

    void on_actionSaveAs_triggered();

    void on_actionSave_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_TextEdit_textChanged();

    void on_actionleftBack_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionrightBack_triggered();

    void on_TextEdit_undoAvailable(bool b);

    void on_TextEdit_redoAvailable(bool b);

    void on_TextEdit_copyAvailable(bool b);

    void on_actionFontColor_triggered();

    void on_actionFontBackgroundColor_triggered();

    void on_actionBackgroundColor_triggered();

    void on_actionFont_triggered();

    void on_actionLineWrap_triggered();

    void on_actionShowToolbar_triggered();

    void on_actionStatusbar_triggered();

    void on_actionExit_triggered();

    void on_actionSelectAll_triggered();

    void on_TextEdit_cursorPositionChanged();

private:
    Ui::MainWindow *ui;
    bool EditChanged;
    QString FILEPATH;
    QLabel statusLabel;
    QLabel statusCursorLabel;
};
#endif // MAINWINDOW_H
