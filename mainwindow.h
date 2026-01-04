/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDB_Location;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *main_page;
    QGridLayout *gridLayout_2;
    QPushButton *delete_db;
    QFrame *line;
    QFormLayout *formLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_selecteddb;
    QLineEdit *decrypt_pass;
    QPushButton *add_db;
    QPushButton *open_db;
    QVBoxLayout *verticalLayout_2;
    QListView *db_list;
    QWidget *add_db_page;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *new_db_name;
    QLabel *label_2;
    QLineEdit *new_db_passwd;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *button_cancel_new_db;
    QFrame *line_4;
    QPushButton *new_db_button;
    QWidget *show_rec_page;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QListView *records_list;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_back_to_main;
    QPushButton *button_add_records;
    QPushButton *button_edit_record;
    QPushButton *button_delete_record;
    QVBoxLayout *verticalLayout_5;
    QLabel *Username;
    QLineEdit *display_username;
    QLabel *Password;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *display_password;
    QPushButton *show_passwd;
    QWidget *add_rec_page;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLineEdit *add_red_desc;
    QLabel *label_3;
    QLineEdit *add_rec_uname;
    QLabel *label_4;
    QLineEdit *add_rec_passwd;
    QHBoxLayout *horizontalLayout;
    QPushButton *add_rec_cancel;
    QPushButton *add_rec_do;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 300);
        actionDB_Location = new QAction(MainWindow);
        actionDB_Location->setObjectName(QString::fromUtf8("actionDB_Location"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        main_page = new QWidget();
        main_page->setObjectName(QString::fromUtf8("main_page"));
        gridLayout_2 = new QGridLayout(main_page);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        delete_db = new QPushButton(main_page);
        delete_db->setObjectName(QString::fromUtf8("delete_db"));

        gridLayout_2->addWidget(delete_db, 1, 0, 1, 1);

        line = new QFrame(main_page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 0, 2, 1, 1);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setContentsMargins(-1, -1, 9, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_3->setItem(0, QFormLayout::FieldRole, verticalSpacer);

        label_selecteddb = new QLabel(main_page);
        label_selecteddb->setObjectName(QString::fromUtf8("label_selecteddb"));
        label_selecteddb->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, label_selecteddb);

        decrypt_pass = new QLineEdit(main_page);
        decrypt_pass->setObjectName(QString::fromUtf8("decrypt_pass"));
        decrypt_pass->setFocusPolicy(Qt::ClickFocus);
        decrypt_pass->setEchoMode(QLineEdit::Password);
        decrypt_pass->setAlignment(Qt::AlignCenter);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, decrypt_pass);


        gridLayout_2->addLayout(formLayout_3, 0, 3, 1, 1);

        add_db = new QPushButton(main_page);
        add_db->setObjectName(QString::fromUtf8("add_db"));

        gridLayout_2->addWidget(add_db, 1, 1, 1, 1);

        open_db = new QPushButton(main_page);
        open_db->setObjectName(QString::fromUtf8("open_db"));

        gridLayout_2->addWidget(open_db, 1, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, -1, 5, -1);
        db_list = new QListView(main_page);
        db_list->setObjectName(QString::fromUtf8("db_list"));

        verticalLayout_2->addWidget(db_list);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 2);

        stackedWidget->addWidget(main_page);
        add_db_page = new QWidget();
        add_db_page->setObjectName(QString::fromUtf8("add_db_page"));
        formLayout_2 = new QFormLayout(add_db_page);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(add_db_page);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        new_db_name = new QLineEdit(add_db_page);
        new_db_name->setObjectName(QString::fromUtf8("new_db_name"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, new_db_name);

        label_2 = new QLabel(add_db_page);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        new_db_passwd = new QLineEdit(add_db_page);
        new_db_passwd->setObjectName(QString::fromUtf8("new_db_passwd"));
        new_db_passwd->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, new_db_passwd);

        line_2 = new QFrame(add_db_page);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(2, QFormLayout::SpanningRole, line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        button_cancel_new_db = new QPushButton(add_db_page);
        button_cancel_new_db->setObjectName(QString::fromUtf8("button_cancel_new_db"));

        horizontalLayout_4->addWidget(button_cancel_new_db);

        line_4 = new QFrame(add_db_page);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_4);

        new_db_button = new QPushButton(add_db_page);
        new_db_button->setObjectName(QString::fromUtf8("new_db_button"));

        horizontalLayout_4->addWidget(new_db_button);


        formLayout_2->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_4);

        stackedWidget->addWidget(add_db_page);
        show_rec_page = new QWidget();
        show_rec_page->setObjectName(QString::fromUtf8("show_rec_page"));
        gridLayout_4 = new QGridLayout(show_rec_page);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, -1, 5, -1);
        records_list = new QListView(show_rec_page);
        records_list->setObjectName(QString::fromUtf8("records_list"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(records_list->sizePolicy().hasHeightForWidth());
        records_list->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(records_list);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);

        line_3 = new QFrame(show_rec_page);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_3, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 5, -1, 5);
        button_back_to_main = new QPushButton(show_rec_page);
        button_back_to_main->setObjectName(QString::fromUtf8("button_back_to_main"));

        horizontalLayout_5->addWidget(button_back_to_main);

        button_add_records = new QPushButton(show_rec_page);
        button_add_records->setObjectName(QString::fromUtf8("button_add_records"));

        horizontalLayout_5->addWidget(button_add_records);

        button_edit_record = new QPushButton(show_rec_page);
        button_edit_record->setObjectName(QString::fromUtf8("button_edit_record"));

        horizontalLayout_5->addWidget(button_edit_record);

        button_delete_record = new QPushButton(show_rec_page);
        button_delete_record->setObjectName(QString::fromUtf8("button_delete_record"));

        horizontalLayout_5->addWidget(button_delete_record);


        gridLayout_4->addLayout(horizontalLayout_5, 2, 0, 1, 5);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, -1, 5, -1);
        Username = new QLabel(show_rec_page);
        Username->setObjectName(QString::fromUtf8("Username"));

        verticalLayout_5->addWidget(Username);

        display_username = new QLineEdit(show_rec_page);
        display_username->setObjectName(QString::fromUtf8("display_username"));
        display_username->setReadOnly(true);

        verticalLayout_5->addWidget(display_username);

        Password = new QLabel(show_rec_page);
        Password->setObjectName(QString::fromUtf8("Password"));

        verticalLayout_5->addWidget(Password);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        display_password = new QLineEdit(show_rec_page);
        display_password->setObjectName(QString::fromUtf8("display_password"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(display_password->sizePolicy().hasHeightForWidth());
        display_password->setSizePolicy(sizePolicy1);
        display_password->setEchoMode(QLineEdit::Password);
        display_password->setReadOnly(true);

        horizontalLayout_2->addWidget(display_password);

        show_passwd = new QPushButton(show_rec_page);
        show_passwd->setObjectName(QString::fromUtf8("show_passwd"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(show_passwd->sizePolicy().hasHeightForWidth());
        show_passwd->setSizePolicy(sizePolicy2);
        show_passwd->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(show_passwd);


        verticalLayout_5->addLayout(horizontalLayout_2);


        gridLayout_4->addLayout(verticalLayout_5, 0, 2, 1, 3);

        stackedWidget->addWidget(show_rec_page);
        add_rec_page = new QWidget();
        add_rec_page->setObjectName(QString::fromUtf8("add_rec_page"));
        formLayout = new QFormLayout(add_rec_page);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_5 = new QLabel(add_rec_page);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        add_red_desc = new QLineEdit(add_rec_page);
        add_red_desc->setObjectName(QString::fromUtf8("add_red_desc"));

        formLayout->setWidget(0, QFormLayout::FieldRole, add_red_desc);

        label_3 = new QLabel(add_rec_page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        add_rec_uname = new QLineEdit(add_rec_page);
        add_rec_uname->setObjectName(QString::fromUtf8("add_rec_uname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, add_rec_uname);

        label_4 = new QLabel(add_rec_page);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        add_rec_passwd = new QLineEdit(add_rec_page);
        add_rec_passwd->setObjectName(QString::fromUtf8("add_rec_passwd"));
        add_rec_passwd->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, add_rec_passwd);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        add_rec_cancel = new QPushButton(add_rec_page);
        add_rec_cancel->setObjectName(QString::fromUtf8("add_rec_cancel"));

        horizontalLayout->addWidget(add_rec_cancel);

        add_rec_do = new QPushButton(add_rec_page);
        add_rec_do->setObjectName(QString::fromUtf8("add_rec_do"));

        horizontalLayout->addWidget(add_rec_do);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout);

        stackedWidget->addWidget(add_rec_page);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 20));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionDB_Location);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Password DB", nullptr));
        actionDB_Location->setText(QCoreApplication::translate("MainWindow", "DB Location", nullptr));
        delete_db->setText(QCoreApplication::translate("MainWindow", "Delete DB", nullptr));
        label_selecteddb->setText(QCoreApplication::translate("MainWindow", "Enter DB Password", nullptr));
        decrypt_pass->setPlaceholderText(QCoreApplication::translate("MainWindow", "decryption password", nullptr));
        add_db->setText(QCoreApplication::translate("MainWindow", "Add New DB", nullptr));
        open_db->setText(QCoreApplication::translate("MainWindow", "Open DB", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "DB Name", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Encryption Password", nullptr));
        button_cancel_new_db->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        new_db_button->setText(QCoreApplication::translate("MainWindow", "Create DB", nullptr));
        button_back_to_main->setText(QCoreApplication::translate("MainWindow", "Show Db List", nullptr));
        button_add_records->setText(QCoreApplication::translate("MainWindow", "Add Record", nullptr));
        button_edit_record->setText(QCoreApplication::translate("MainWindow", "Edit Record", nullptr));
        button_delete_record->setText(QCoreApplication::translate("MainWindow", "Delete Record", nullptr));
        Username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        Password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        show_passwd->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Descrption", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        add_rec_cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        add_rec_do->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
