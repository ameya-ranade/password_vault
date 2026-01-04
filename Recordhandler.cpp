/*
 * Recordhandler.cpp
 *
 *  Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#include "Recordhandler.h"

#include <QtCore/QDebug>

Record_handler::Record_handler()
{
	this->dirty_data = false;

}

Record_handler::~Record_handler() {
	// TODO Auto-generated destructor stub
}

void Record_handler::parse_json(QByteArray& data)
{
	QJsonDocument json_doc;
//	qDebug()<<"File contents after ";
//	qDebug()<<data;

	QJsonParseError err;
	json_doc = QJsonDocument::fromJson(data, &err);

	beginResetModel();
	this->records_list = json_doc.object().value("records").toArray();
	endResetModel();

//	qDebug()<<"Number of elements "<<this->records_lst.size();
	return;
}

void Record_handler::encode_json(QByteArray& data)
{
	QJsonDocument doc;

	QJsonObject root_object;
	root_object.insert("records", this->records_list);
	doc.setObject(root_object);
	data = doc.toJson();
}

int Record_handler::rowCount(const QModelIndex & /*parent*/ ) const
{
	return this->records_list.size();
}

QVariant Record_handler::data(const QModelIndex &index, int role) const
{
	if(role == Qt::DisplayRole)
	{
		QJsonValue record = this->records_list.at(index.row());
		return record.toObject().value("title").toString();
	}

	return QVariant();
}

int Record_handler::get_records_count()
{
	return this->records_list.size();
}

void Record_handler::get_record_data(int index,
		QLineEdit &uname,
		QLineEdit &passwd)
{
	QJsonValue record = this->records_list.at(index);

	uname.setText(record.toObject().value("username").toString()) ;
	passwd.setText(record.toObject().value("password").toString()) ;
}

void Record_handler::get_record_data(int index, QLineEdit &uname, QLineEdit &passwd, QLineEdit &desc)
{
	QJsonValue record = this->records_list.at(index);

	uname.setText(record.toObject().value("username").toString()) ;
	passwd.setText(record.toObject().value("password").toString()) ;
	desc.setText(record.toObject().value("title").toString());
}
void Record_handler::add_new_record(char* indata)
{
//	qDebug()<<indata;
	QString data = QString::fromLocal8Bit(indata);
	QStringList data_split = data.split(":");

	if(data_split.size() == 3)
	{
		QJsonObject inner_record;
		inner_record.insert("title", data_split.at(0));
		inner_record.insert("username", data_split.at(1));
		inner_record.insert("password", data_split.at(2));
//		qDebug()<<inner_record;

		this->records_list.append(inner_record);
		this->dirty_data = true;
	}
	else
	{
		qWarning()<<"Wrong data format ";
	}
}

void Record_handler::add_new_record(QString desc, QString uname, QString passwd)
{
	QJsonObject inner_record;
	inner_record.insert("title", desc);
	inner_record.insert("username", uname);
	inner_record.insert("password", passwd);

	beginResetModel();
	this->records_list.append(inner_record);
	endResetModel();

	this->dirty_data = true;
}

void Record_handler::edit_record(int index, QString desc, QString uname, QString passwd)
{
	QJsonObject record ;
	record.insert("title", desc );
	record.insert("username", uname);
	record.insert("password", passwd);

	beginResetModel();
	this->records_list.replace(index, record);
	endResetModel();
}

void Record_handler::delete_record(qsizetype index)
{
	this->records_list.removeAt(index - 1);
	endResetModel();
	this->dirty_data = true;
//	qDebug()<<"Delete record "<<index;
}

void Record_handler::delete_record(int index)
{
	beginResetModel();
	this->records_list.removeAt(index);
	endResetModel();
//	qDebug()<<"Delete record "<<index;
}

bool Record_handler::get_data_status()
{
	return this->dirty_data;
}

void Record_handler::reset_data_status()
{
	this->dirty_data = false;
}

void Record_handler::cleanup(QByteArray& data)
{
	QJsonDocument doc;

	QJsonObject root_object;
	root_object.insert("records", this->records_list);
	doc.setObject(root_object);
	data = doc.toJson();
}
