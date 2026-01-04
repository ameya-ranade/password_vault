/*
 * main.cpp
 *
 * 	Created on: Dec 22, 2023
 *  Author: Ameya Ranade  (ranadeameya@outlook.com)
 */

#include <QtWidgets/QApplication>

#include "main_window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    main_window mainwindow;
    mainwindow.show();
	return app.exec();
}
