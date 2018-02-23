#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LimitUsageGUI.h"

#include <QTimer>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "MaoConst.h"


class LimitUsageGUI : public QMainWindow
{
	Q_OBJECT

public:
	LimitUsageGUI(QWidget *parent = Q_NULLPTR);

private:
	void closeEvent(QCloseEvent* e);

	void initDatabase();
	void recordDownTime();
	void shutdownPC();

	void countOneMinute();

	void checkMaoPermissionAndShutdownPC();
	void getMaoPermission();
	void recvMaoPermission(QNetworkReply * reply);
	bool checkMaoPermission(QStringList & permissionInfo);

private:


	Ui::LimitUsageGUIClass ui;

	QTimer countMinute;

	QSqlDatabase dbTimeRecord;
	QSqlQuery * dbQuery;

	QNetworkAccessManager loadPermission;

	QDate tempToday;
};
