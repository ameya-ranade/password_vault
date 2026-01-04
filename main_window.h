/*
 * main_window.h
 *
 *  Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>

#include "mainwindow.h"
#include "JSONhandler.h"
#include "Recordhandler.h"

#define SYS_STATE_INIT					0
#define SYS_STATE_LIST_DB				1

#define PAGE_MAIN						0
#define PAGE_ADD_NEW_DB					1
#define PAGE_SHOW_REC_DATA				2
#define PAGE_ADD_NEW_RECORD				3

#define MAX_IDLE_TIME					30000 /* in msec */

struct edit_record_info_t {
	char edit_record;
	int rec_index;
};

namespace Ui {
    class MainWindow;
}

class main_window : public QMainWindow
{
        Q_OBJECT
public:
    main_window(QMainWindow *parent = 0);
    Ui::MainWindow *main_win;

    void set_db_list_page(int state);

public slots:
	void app_state_machine();
	void onAdd_db();
	void onCreate_db();
	void onDbListItem_clicked(const QModelIndex &index);
	void onDbOpen_clicked();

	/* called on delete DB button on PAGE_MAIN clicked */
	void onDeleteDbClicked();


	void onBackToDbList_clicked();

	void onRecListItem_clicked(const QModelIndex &index);

	/* called when add record on PAGE_SHOW_REC_DATA is clicked */
	void open_add_rec_page();

	/* called when edit record on PAGE_SHOW_REC_DATA is clicked */
	void onEdit_record();

	/* called when delete record on PAGE_SHOW_REC_DATA is clicked */
	void onDelete_record();

	/* Called when add_rec button on PAGE_ADD_NEW_RECORD is clicked */
	void do_add_new_rec();

	/* Called when add_rec_cancel button on PAGE_ADD_NEW_RECORD is clicked */
	void cancel_add_new_rec();

	/* called when the view passwd button on PAGE_SHOW_REC_DATA is pressed */
	void to_view_passwd();

	/* called when the view passwd button on PAGE_SHOW_REC_DATA is released */
	void to_hide_passwd();

	/* Called when the user presses DB Location action */
	void onDBLocation_action();

	/* Called when the user presses Idle Time action */
	void onIdleTimeSet_action();

private:
    int sys_state;
    char *db_passwd;
    struct edit_record_info_t edit_record_info = {};
    QTimer *timer_obj;
    QLabel *status_text;
    JSON_handler *db_manager;
    Record_handler *rec_handler;
    QTimer *inactivity_timer;
};

#endif // MAIN_WINDOW_H
