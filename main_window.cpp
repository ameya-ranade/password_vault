/**********************************************************************************
 * 	main_window.cpp
 *
 * 	Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 *********************************************************************************/


#include "main_window.h"

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtWidgets/QInputDialog>

main_window::main_window(QMainWindow *parent) : QMainWindow(parent), main_win(new Ui::MainWindow)
{
    main_win->setupUi(this);
    this->main_win->stackedWidget->setCurrentIndex(PAGE_MAIN);
    this->status_text = new QLabel();
    this->main_win->statusbar->addWidget(this->status_text);
    this->status_text->setText("SYS_STATE_LIST_DB");

    /* Settings */
    QSettings *settings = new QSettings(QSettings::UserScope, "ARanade", "PassVault");

    QString dbpath = settings->value("db_path").toString();
    if(dbpath.isEmpty())
    {
    	settings->setValue("db_path", QDir::currentPath());
    	dbpath = QDir::currentPath();
    }
    int max_idle_time = settings->value("idle_timeout", MAX_IDLE_TIME).toInt();

    this->db_manager = new JSON_handler(dbpath);
    this->main_win->db_list->setModel(this->db_manager);

    this->rec_handler = new Record_handler();
    this->main_win->records_list->setModel(this->rec_handler);

    this->timer_obj = new QTimer();
    this->timer_obj->setSingleShot(true);
    this->timer_obj->setInterval(200);

    this->inactivity_timer = new QTimer;
    this->inactivity_timer->setSingleShot(true);
    this->inactivity_timer->setInterval(max_idle_time);

    /* Connect inactivity timer to return to main page when idle for 30 sec */
    QObject::connect(this->inactivity_timer, &QTimer::timeout, this, &main_window::onBackToDbList_clicked);

    QObject::connect(this->timer_obj, SIGNAL(timeout()),
    		this, SLOT(app_state_machine()));

    QObject::connect(this->main_win->add_db, SIGNAL(clicked()),
    		this, SLOT(onAdd_db()));

    QObject::connect(this->main_win->delete_db, SIGNAL(clicked()),
    		this, SLOT(onDeleteDbClicked()));

    QObject::connect(this->main_win->new_db_button, SIGNAL(clicked()),
    		this, SLOT(onCreate_db()));

    QObject::connect(this->main_win->db_list, SIGNAL(clicked(const QModelIndex &)),
    		this, SLOT(onDbListItem_clicked(const QModelIndex &)));

    QObject::connect(this->main_win->open_db, SIGNAL(clicked()),
    		this, SLOT(onDbOpen_clicked()));

    QObject::connect(this->main_win->button_cancel_new_db, SIGNAL(clicked()),
    		this, SLOT(onBackToDbList_clicked()));



    QObject::connect(this->main_win->records_list, SIGNAL(clicked(const QModelIndex &)),
    					this, SLOT(onRecListItem_clicked(const QModelIndex &)));

    QObject::connect(this->main_win->button_back_to_main, SIGNAL(clicked()),
    		this, SLOT(onBackToDbList_clicked()));

    QObject::connect(this->main_win->button_add_records, SIGNAL(clicked()),
    		this, SLOT(open_add_rec_page()));

    QObject::connect(this->main_win->button_edit_record, SIGNAL(clicked()),
       		this, SLOT(onEdit_record()));

    QObject::connect(this->main_win->button_delete_record, SIGNAL(clicked()),
       		this, SLOT(onDelete_record()));


    QObject::connect(this->main_win->add_rec_do, SIGNAL(clicked()),
    		this, SLOT(do_add_new_rec()));

    QObject::connect(this->main_win->add_rec_cancel, SIGNAL(clicked()),
    		this, SLOT(cancel_add_new_rec()));


    QObject::connect(this->main_win->show_passwd, SIGNAL(pressed()),
    		this, SLOT(to_view_passwd()));

    QObject::connect(this->main_win->show_passwd, SIGNAL(released()),
    		this, SLOT(to_hide_passwd()));

    /* Action */
    QObject::connect(this->main_win->actionDB_Location, SIGNAL(triggered()),
    		this, SLOT(onDBLocation_action()));

    QObject::connect(this->main_win->actionIdle_Time, SIGNAL(triggered()),
    			this, SLOT(onIdleTimeSet_action()));

    this->sys_state = SYS_STATE_INIT;
    this->db_passwd = 0;
    /* Trigger state machine run */
    this->timer_obj->start();
}

void main_window::app_state_machine()
{
	switch(this->sys_state)
	{
	case SYS_STATE_INIT:
		this->status_text->setText("SYS_STATE_LIST_DB");
		this->set_db_list_page(0);
		this->sys_state = SYS_STATE_LIST_DB;
	    /* Trigger state machine run */
	    this->timer_obj->start();
		break;

	case SYS_STATE_LIST_DB:
		this->status_text->setText("SYS_STATE_LIST_DB");
		break;

	default:

		break;
	}
}

void main_window::set_db_list_page(int state)
{
	if(state == 0)
	{
		this->main_win->delete_db->setEnabled(false);
		this->main_win->open_db->setEnabled(false);
	}
	else
	{
		this->main_win->delete_db->setEnabled(true);
		this->main_win->open_db->setEnabled(true);
	}
}

void main_window::onAdd_db()
{
	this->status_text->setText("Enter new DB Details");
	this->main_win->stackedWidget->setCurrentIndex(PAGE_ADD_NEW_DB);
}

void main_window::onCreate_db()
{
//	qDebug()<<"DB Name "<<this->main_win->new_db_name->text();
//	qDebug()<<"DB password "<<this->main_win->new_db_passwd->text();


	if(this->db_manager->create_new_database(this->main_win->new_db_name->text(),
			this->main_win->new_db_passwd->text()))
	{
		this->status_text->setText("New DB Created");
	}
	else
	{
		this->status_text->setText("New DB Creation failed");
	}

	this->main_win->stackedWidget->setCurrentIndex(PAGE_MAIN);
}

void main_window::onDbListItem_clicked(const QModelIndex &index)
{
	this->main_win->delete_db->setEnabled(true);
	this->main_win->open_db->setEnabled(true);
	this->status_text->setText("Select Action");
}

void main_window::onDbOpen_clicked()
{
	QByteArray *db_data = new QByteArray();
	this->db_passwd = (char *)calloc(1,20);

//    qDebug()<<"DB Name "<<this->main_win->db_list->currentIndex().data().toString();
	if (0 == this->db_manager->read_database(this->main_win->db_list->currentIndex().data().toString(),
									this->main_win->decrypt_pass->text(),
									*db_data))
	{
		/* Save DB Passwd to encrypt in case records are edited */
		memcpy(this->db_passwd, this->main_win->decrypt_pass->text().toStdString().c_str(), this->main_win->decrypt_pass->text().length());

		/* Parse data */
		this->status_text->setText("Parsing Data");
		this->rec_handler->parse_json(*db_data);
		this->main_win->stackedWidget->setCurrentIndex(PAGE_SHOW_REC_DATA);
	}
	else
	{
		this->status_text->setText("Error opening DB");
	}
	delete(db_data);

	/* Start inactivity monitoring */
	this->inactivity_timer->start();
}

void main_window::onDeleteDbClicked()
{
	this->db_manager->delete_database(this->main_win->db_list->currentIndex().data().toString());
}

void main_window::onRecListItem_clicked(const QModelIndex &index)
{
	this->rec_handler->get_record_data(index.row(),
					*this->main_win->display_username,
					*this->main_win->display_password);

	/* Reset idle monitoring */
	this->inactivity_timer->start();
}

void main_window::onBackToDbList_clicked()
{
	this->main_win->db_list->setFocus();
	this->main_win->delete_db->setEnabled(false);
	this->main_win->open_db->setEnabled(false);
	this->main_win->decrypt_pass->clear();
	this->main_win->db_list->clearSelection();

	/* Delete the db passwd saved */
	if(this->db_passwd)
	{
		memset(this->db_passwd, 0, 20);
	}
	this->main_win->stackedWidget->setCurrentIndex(PAGE_MAIN);
	/* Stop inactivity timer if active */
	if(this->inactivity_timer->isActive())
	{
		this->inactivity_timer->stop();
	}

}

void main_window::open_add_rec_page()
{
	this->main_win->add_red_desc->clear();
	this->main_win->add_rec_uname->clear();
	this->main_win->add_rec_passwd->clear();

	this->main_win->display_username->clear();
	this->main_win->display_password->clear();
	this->main_win->db_list->clearSelection();

	this->main_win->stackedWidget->setCurrentIndex(PAGE_ADD_NEW_RECORD);

	/* Stop inactivity timer */
	this->inactivity_timer->stop();
}

void main_window::onEdit_record()
{
	this->rec_handler->get_record_data(this->main_win->records_list->currentIndex().row(),
					*this->main_win->add_rec_uname,
					*this->main_win->add_rec_passwd,
					*this->main_win->add_red_desc);
	this->edit_record_info.edit_record = 1;
	this->edit_record_info.rec_index = this->main_win->records_list->currentIndex().row();

	this->main_win->stackedWidget->setCurrentIndex(PAGE_ADD_NEW_RECORD);

	/* Stop inactivity timer */
	this->inactivity_timer->stop();
}

void main_window::onDelete_record()
{
	QByteArray *db_data = new QByteArray();
//	qDebug()<<"Delete "<<this->main_win->records_list->currentIndex().row();
	this->rec_handler->delete_record(this->main_win->records_list->currentIndex().row());
	this->main_win->records_list->clearSelection();
	this->main_win->display_username->clear();
	this->main_win->display_password->clear();

	/* Write data to disk */
	this->rec_handler->encode_json(*db_data);
//	qDebug()<<"db name "<<this->main_win->display_selected_db->text();
	this->db_manager->write_database(this->main_win->db_list->currentIndex().data().toString(),
			this->db_passwd, 20, *db_data);

	delete(db_data);
}

void main_window::do_add_new_rec()
{
	QByteArray *db_data = new QByteArray();

	/* Edit record or add new record */
	if(this->edit_record_info.edit_record)
	{
		this->rec_handler->edit_record(this->edit_record_info.rec_index,
				this->main_win->add_red_desc->text(),
				this->main_win->add_rec_uname->text(),
				this->main_win->add_rec_passwd->text());
		this->edit_record_info = {0,0};
	}
	else
	{
		this->rec_handler->add_new_record(this->main_win->add_red_desc->text(),
				this->main_win->add_rec_uname->text(),
				this->main_win->add_rec_passwd->text());
	}

	this->main_win->add_red_desc->clear();
	this->main_win->add_rec_uname->clear();
	this->main_win->add_rec_passwd->clear();
	/* Return to the record list page
	 * the added record data is not yet written to disk */
	this->main_win->stackedWidget->setCurrentIndex(PAGE_SHOW_REC_DATA);

	/* Write data to disk */
	this->rec_handler->encode_json(*db_data);
//	qDebug()<<"db name "<<this->main_win->display_selected_db->text();
	this->db_manager->write_database(this->main_win->db_list->currentIndex().data().toString(),
			this->db_passwd, 20, *db_data);

	delete(db_data);

	/* Restart inactivity timer */
	this->inactivity_timer->start();
}

void main_window::cancel_add_new_rec()
{
	this->main_win->records_list->clearSelection();
	this->main_win->display_username->clear();
	this->main_win->display_password->clear();
	this->main_win->stackedWidget->setCurrentIndex(PAGE_SHOW_REC_DATA);

	/* Restart inactivity timer */
	this->inactivity_timer->start();
}

void main_window::to_view_passwd()
{
	this->main_win->display_password->setEchoMode(QLineEdit::Normal);
}

void main_window::to_hide_passwd()
{
	this->main_win->display_password->setEchoMode(QLineEdit::Password);
}

void main_window::onDBLocation_action()
{
	QSettings *settings = new QSettings(QSettings::UserScope, "ARanade", "PassVault");
	QString dbpath = settings->value("db_path").toString();
    if(dbpath.isEmpty())
    {
    	dbpath = QDir::currentPath();
    }

	QString dir = QFileDialog::getExistingDirectory(this,
							"Select DB Directory",
							dbpath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(!dir.isEmpty())
	{
		settings->setValue("db_path", dir);
		this->db_manager->set_db_path(dir);
	}

}

void main_window::onIdleTimeSet_action()
{
	QSettings *settings = new QSettings(QSettings::UserScope, "ARanade", "PassVault");
	int idle_time = settings->value("idle_timeout", MAX_IDLE_TIME).toInt();
	bool ok;
	int new_idle_time = QInputDialog::getInt(0, "Idle Time", "Enter new idle time",
			idle_time, 10000, 60000, 1000, &ok);

	QString info_text = "Idle time ";

	if(ok)
	{
		if(idle_time != new_idle_time)
		{
			info_text.append("= ");
			info_text.append(QString::number(new_idle_time));
			info_text.append(" ms");
			settings->setValue("idle_timeout", new_idle_time);
		}
		else
		{
			info_text.append("unchanged");
		}
	}
	else
	{
		info_text.append("unchanged");
	}


	this->status_text->setText(info_text);
}
