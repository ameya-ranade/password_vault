/*
 * JSONhandler.cpp
 *
 *  Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#include "JSONhandler.h"

#include <QtCore/QDebug>

JSON_handler::JSON_handler()
{
	/* Set the data folder base path */
	this->data_dir = new QDir();
}

JSON_handler::JSON_handler(QString dbpath)
{
	/* Set the data folder base path */
	this->data_dir = new QDir();
	this->data_dir->setPath(dbpath);

	upate_db_list();
}

void JSON_handler::set_db_path(QString db_path)
{
	this->data_dir->setPath(db_path);
	upate_db_list();
}

JSON_handler::~JSON_handler() {
	// TODO Auto-generated destructor stub
}

void JSON_handler::upate_db_list()
{
	beginResetModel();
	this->file_list.clear();
	this->file_list = this->data_dir->entryList(*(new QStringList("*.secrec")));
	endResetModel();
}

int JSON_handler::rowCount(const QModelIndex & /*parent*/ ) const
{
	return this->file_list.size();
}

QVariant JSON_handler::data(const QModelIndex &index, int role) const
{
	if(role == Qt::DisplayRole)
	{
		return this->file_list.at(index.row());
	}

	return QVariant();
}



bool JSON_handler::create_new_database(QString db_name, QString passcode)
{
	QString new_file_name;
	Encrypt_data gcrypt;
	char *data = (char *)calloc(32, 1);
	char *pass_code = (char *)calloc(20, 1);

	new_file_name.clear();
	new_file_name.append(this->data_dir->absolutePath());
	new_file_name.append("/");
	new_file_name.append(db_name);
	new_file_name.append(".secrec");

	QFile *db_file = new QFile();
	db_file->setFileName(new_file_name);

	/* Set pass code */
	memcpy(pass_code, passcode.toLocal8Bit().data(), passcode.length());

	/* set data */
	*(unsigned short *)&data[4] = 19;
	sprintf(&data[6], "%s", "{ \"records\" : [ ] }");

	gcrypt.encrypt_database(pass_code, 20, data, 32);

	if(db_file->open(QIODevice::ReadWrite))
	{
		/* Empty data base */
		db_file->write(data, 32);
		db_file->close();

		this->upate_db_list();
		return true;
	}
	else
	{
		qWarning()<<"Error opening file";
		return false;
	}

	free(data);
	free(pass_code);
}

void JSON_handler::delete_database(QString db_name)
{
	QString file_name;
	file_name.append(this->data_dir->absolutePath());
	file_name.append("/");
	file_name.append(db_name);

	QFile *db_file = new QFile();
	db_file->setFileName(file_name);
	if(db_file->exists())
	{
		db_file->remove();
	}
	this->upate_db_list();
}

int JSON_handler::read_database(QString db_name, QString passcode, QByteArray& buf)
{
	int retval = 0;
	Encrypt_data gcrypt;
	unsigned short data_len;

	/* Get db size */
	QString new_file_name;
	new_file_name.clear();
	new_file_name.append(this->data_dir->absolutePath());
	new_file_name.append("/");
	new_file_name.append(db_name);

	QFile *db_file = new QFile();
	db_file->setFileName(new_file_name);
//	qDebug()<<"File path "<<new_file_name;
//	qDebug()<<"File size" << db_file->size();
	char *inbuf = (char *)calloc(db_file->size(), 1);

	/* get password */
	char *pass_code = (char *)calloc(20, 1);
	memcpy(pass_code, passcode.toLocal8Bit().data(), passcode.length());
//	qDebug()<<"Pass_code "<<pass_code;


	if(db_file->open(QIODevice::ReadWrite | QIODevice::ExistingOnly))
	{
		db_file->read(inbuf, db_file->size());
		db_file->close();

		if(gcrypt.decrypt_database(pass_code, 20, inbuf, db_file->size()))
		{
			qWarning()<<"Error reading db ";
			retval = -1;
		}
		else
		{
//		printf("%s Data len %hu\n", __FUNCTION__, *(unsigned short *)&inbuf[4]);

			data_len = *(unsigned short *)&inbuf[4];
			buf.resize(data_len);
			memcpy(buf.data(), &inbuf[6], data_len);


		}
	}
	else
	{
		qWarning()<<"Error opening file";
		retval = -2;
	}

	free(inbuf);
	free(pass_code);
	return retval;
}

void JSON_handler::write_database(QString db_name, char *passcode, int pass_len, QByteArray& buf)
{
	QString new_file_name;
	new_file_name.clear();
	new_file_name.append(this->data_dir->absolutePath());
	new_file_name.append("/");
	new_file_name.append(db_name);

	QFile *db_file = new QFile();
	db_file->setFileName(new_file_name);
	/* minimum buf size = data size + header 4 bytes + data len 2 bytes
	 * total buf size should be in multiples of 32 for the encryption algo */
	int bufsize = (((buf.size() + 6) / 32) + 1) * 32;
	char *outbuf = (char *)calloc(bufsize, 1);

	*(unsigned short *)&outbuf[4] = (unsigned short)buf.size();
	memcpy(outbuf + 6, buf.data(), buf.size());

//	for(int idx = 0; idx < bufsize; idx++)
//	{
//		printf("%X", (unsigned char)outbuf[idx]);
//	}

//	printf("JSON Write data: Indata before encryption %s ", buf.data());
	Encrypt_data gcrypt;

	gcrypt.encrypt_database(passcode, pass_len, outbuf, bufsize);

	if(db_file->open(QIODevice::ReadWrite | QIODevice::ExistingOnly))
	{
		/* set file pointer to start */
		db_file->seek(0);
		db_file->write(outbuf, bufsize);

		db_file->close();
	}
	else
	{
		qWarning()<<"Error opening file";
	}
}

