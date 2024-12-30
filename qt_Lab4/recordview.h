#ifndef RECORDVIEW_H
#define RECORDVIEW_H

#include <QDialog>

namespace Ui {
class RecordView;
}

class RecordView : public QDialog
{
    Q_OBJECT

public:
    explicit RecordView(QWidget *parent = nullptr);
    ~RecordView();

private:
    Ui::RecordView *ui;
};

#endif // RECORDVIEW_H
