#include "mainwindow.h"
#include "./ui_mainwindow.h"


void MainWindow::initUI()
{
    flabCurFile = new QLabel;
    flabCurFile->setMidLineWidth(150);
    flabCurFile->setText("当前文件:");
    ui->statusbar->addWidget(flabCurFile);
    progressBar = new QProgressBar;

    progressBar->setMinimum(5);
    progressBar->setMaximum(50);
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBar);

    spinFontSize = new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    ui->mainToolBar->addWidget(new QLabel("字体大小"));
    ui->mainToolBar->addWidget(spinFontSize);

    comboFont = new QFontComboBox;
    ui->mainToolBar->addWidget(new QLabel("字体"));
    ui->mainToolBar->addWidget(comboFont);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionBo, &QAction::triggered, this, &MainWindow::on_actionBo_triggered);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::on_actionAbout_triggered);
    //connect(ui->actionBo,&QAction::triggered,ui->textEdit,&MainWindow::on_actionBo_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"sample_2","开发人员：李子轩");
}



void MainWindow::on_actionBo_triggered(bool checked)
{
    QTextCharFormat fmt;
    if(checked){
        fmt.setFontWeight(QFont::Bold);
    }
    else{
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}



void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    ui->actionUnder->setChecked(fmt.fontUnderline());
    ui->actiontltalic->setChecked(fmt.fontItalic());
    ui->actionBo->setChecked(fmt.font().bold());
}
