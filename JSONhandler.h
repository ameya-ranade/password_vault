/*
 * JSONhandler.h
 *
 *  Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#ifndef JSONHANDLER_H_
#define JSONHANDLER_H_

#include <QtCore/QAbstractListModel>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include "Encryptdata.h"

class JSON_handler : public QAbstractListModel
{
public:
	JSON_handler();
	JSON_handler(QString dbpath);
	virtual ~JSON_handler();
	void set_db_path(QString);
	int get_db_size();
	bool create_new_database(QString db_name, QString passcode);
	void delete_database(QString db_name);

	void upate_db_list();
	int read_database(QString db_name, QString passcode, QByteArray& buf);
	void write_database(QString db_name, char *passcode, int pass_len, QByteArray& buf);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
	QDir *data_dir;
	QStringList file_list;
};

#endif /* JSONHANDLER_H_ */
