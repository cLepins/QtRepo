/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomTextEdit;
    QListWidget *userListWidget;
    QLineEdit *sayLineEdit;
    QPushButton *sayButton;
    QPushButton *logoutButton;
    QWidget *loginPage;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QFrame *loginFrame;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *serverEdit;
    QLabel *label_3;
    QLineEdit *usernameEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(825, 620);
        MainWindow->setStyleSheet(QString::fromUtf8("#titleLable {\n"
"  background: white;\n"
"  color: blue;\n"
"  border: none;\n"
"  border-bottom: 1px solid black;\n"
"  padding: 5px;\n"
"  font: 24pt \"\351\273\221\344\275\223\";\n"
"  color: rgb(255, 255, 255);\n"
"  background-color: rgba(0, 170, 168, 0.66);\n"
"}\n"
"\n"
"#mainFrame {\n"
"  border: none;\n"
"  background: white;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background-color: rgb(173, 216, 230);\n"
"    border: 1px solid gray;\n"
"    border-radius: 25px;\n"
"    padding: 10px;\n"
"}\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        gridLayout->addWidget(titleLabel, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("#titleLable {\n"
"  background: white;\n"
"  color: blue;\n"
"  border: none;\n"
"  border-bottom: 1px solid black;\n"
"  padding: 5px;\n"
"  font: 24pt \"\351\273\221\344\275\223\";\n"
"  color: rgb(255, 255, 255);\n"
"  background-color: rgba(0, 170, 168, 0.66);\n"
"}\n"
"\n"
"#mainFrame {\n"
"  border: none;\n"
"  background: white;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background-color: rgb(173, 216, 230); /* \346\265\205\350\223\235\350\211\262 */\n"
"    border: 1px solid gray;\n"
"    border-radius: 25px;\n"
"    padding: 10px;\n"
"}\n"
""));
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        gridLayout_4 = new QGridLayout(chatPage);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName("roomTextEdit");

        horizontalLayout->addWidget(roomTextEdit);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userListWidget);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 3);

        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName("sayLineEdit");

        gridLayout_4->addWidget(sayLineEdit, 1, 0, 1, 1);

        sayButton = new QPushButton(chatPage);
        sayButton->setObjectName("sayButton");

        gridLayout_4->addWidget(sayButton, 1, 1, 1, 1);

        logoutButton = new QPushButton(chatPage);
        logoutButton->setObjectName("logoutButton");

        gridLayout_4->addWidget(logoutButton, 1, 2, 1, 1);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        gridLayout_3 = new QGridLayout(loginPage);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalSpacer_2 = new QSpacerItem(20, 186, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(238, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setFrameShape(QFrame::Shape::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(loginFrame);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_2 = new QLabel(loginFrame);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        serverEdit = new QLineEdit(loginFrame);
        serverEdit->setObjectName("serverEdit");

        gridLayout_2->addWidget(serverEdit, 0, 1, 1, 1);

        label_3 = new QLabel(loginFrame);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName("usernameEdit");

        gridLayout_2->addWidget(usernameEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);


        gridLayout_3->addWidget(loginFrame, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(238, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 185, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 2, 1, 1, 1);

        stackedWidget->addWidget(loginPage);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "lizixuan\347\232\204\350\201\212\345\244\251\345\256\244", nullptr));
        sayButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
