/*
 * Recordhandler.h
 *
 *  Created on: Dec 22, 2023
 *      Author: aranade
 */

#ifndef RECORDHANDLER_H_
#define RECORDHANDLER_H_

#include <QtCore/QAbstractListModel>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLineEdit>

class Record_handler : public QAbstractListModel
{
public:
	Record_handler();
	virtual ~Record_handler();
	void parse_json(QByteArray& data);
	void encode_json(QByteArray& data);

	int get_records_count();
	void get_record_data(int index, QLineEdit &uname, QLineEdit &passwd);
	void get_record_data(int index, QLineEdit &uname, QLineEdit &passwd, QLineEdit &desc);
	void add_new_record(char* data);
	void add_new_record(QString desc, QString uname, QString passwd);
	void edit_record(int index, QString desc, QString uname, QString passwd);
	void delete_record(qsizetype index);
	void delete_record(int index);

	bool get_data_status();
	void reset_data_status();
	void cleanup(QByteArray& data);


	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
	bool dirty_data;
	QJsonArray records_list;
};

#endif /* RECORDHANDLER_H_ */
