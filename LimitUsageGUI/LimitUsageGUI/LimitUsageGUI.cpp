#include "LimitUsageGUI.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>


#include <stdlib.h>


LimitUsageGUI::LimitUsageGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initDatabase();

	connect(&loadPermission, &QNetworkAccessManager::finished, this, &LimitUsageGUI::recvMaoPermission);

	connect(&countMinute, &QTimer::timeout, this, &LimitUsageGUI::countOneMinute);
	countMinute.setSingleShot(true);
	countMinute.start(59000);
}

void LimitUsageGUI::closeEvent(QCloseEvent* e)
{
	e->ignore();
}

void LimitUsageGUI::initDatabase() {
	dbTimeRecord = QSqlDatabase::addDatabase("QSQLITE", "MaoFlightMap");
	dbTimeRecord.setDatabaseName(Mao_DB_Path);

	if (false == dbTimeRecord.open())
		throw 0;//TODO

	dbQuery = new QSqlQuery(dbTimeRecord);

	dbQuery->exec("CREATE TABLE Record ("
		"millisecond INT primary key not null unique,"
		"Date text,"
		"DuringMinute INT,"
		"DownTime text"
		")");
}

void LimitUsageGUI::countOneMinute() {

	//QMessageBox::information(this,
	//	"asdgsadgasdg",
	//	"sadgasdgasdg",
	//	QMessageBox::Ok | QMessageBox::Help | QMessageBox::Cancel, QMessageBox::Ok);

	tempToday = QDate::currentDate();

	dbQuery->exec("SELECT "
		"DuringMinute "
		"FROM Record "
		"WHERE Date='" + tempToday.toString() + "'");

	if (true == dbQuery->next()) {
		// increase During by one
		int nowMinute = dbQuery->value(0).toInt() + 1;

		// alter item in DB
		QString query = "UPDATE Record SET DuringMinute = %1 WHERE Date='" + tempToday.toString() + "'";
		query = query.arg(nowMinute);
		dbQuery->exec(query);

		if (nowMinute > Mao_Allow_Minute) {
			//trigger shutdown PC
			checkMaoPermissionAndShutdownPC();
		}
		else {
			countMinute.start(59000);
		}
	}
	else {
		// insert new line
		QString query = "INSERT INTO Record "
			"("
			"millisecond,"
			"Date,"
			"DuringMinute,"
			"DownTime"
			")"
			" VALUES "
			"("
			"%1,"
			"\"%2\","
			"%3,"
			"\"%4\""
			")";
		query = query
			.arg(tempToday.toJulianDay())
			.arg(tempToday.toString())
			.arg(1)
			.arg(Mao_NULL_String);


		if (false == dbQuery->exec(query))
			throw 0;//TODO

		countMinute.start(59000);
	}
}

void LimitUsageGUI::checkMaoPermissionAndShutdownPC() {

	//check Mao's Permission from maojianwei.com - Red Button !
	getMaoPermission();
}

void LimitUsageGUI::getMaoPermission() {
	QUrl url = Mao_Permission_URL;
	QNetworkRequest req = QNetworkRequest(url);
	loadPermission.get(req);
}

void LimitUsageGUI::recvMaoPermission(QNetworkReply* reply) {
	QString data = reply->readAll();
	if (data.indexOf(';') >= 0)
	{
		QStringList permissionInfo = data.split(';');
		if (permissionInfo.length() >= 1)
		{
			bool allow = checkMaoPermission(permissionInfo);

			if (true == allow) {
				recordDownTime();
				shutdownPC();
				return;
			}
		}
	}
	countMinute.start(59000);
}

bool LimitUsageGUI::checkMaoPermission(QStringList & permissionInfo) {

	QString allowS = permissionInfo[0];
	if (-1 != allowS.indexOf(Mao_Permission_OK)) {
		return true;
	}
	return false;
}

void LimitUsageGUI::recordDownTime() {
	QString query = "UPDATE Record SET DownTime = \"%1\" WHERE Date='" + tempToday.toString() + "'";
	query = query.arg(QDateTime::currentDateTime().toString());
	dbQuery->exec(query);
}

void LimitUsageGUI::shutdownPC() {
	system("shutdown /s /f /t 30 /c '今天看电脑太久了，起来休息一下'");
	//ui.debugLabel->setText(QDateTime::currentDateTime().toString());
}
