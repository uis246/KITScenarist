#include "DatabaseHistoryMapper.h"

#include <DataLayer/Database/Database.h>

#include <3rd_party/Helpers/QVariantMapWriter.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

using DataMappingLayer::DatabaseHistoryMapper;

namespace {
	const QString ID_KEY = "id";
	const QString QUERY_KEY = "query";
	const QString QUERY_VALUES_KEY = "query_values";
	const QString DATETIME_KEY = "datetime";
}


QList<QMap<QString, QString> > DatabaseHistoryMapper::history(const QString& _fromDatetime)
{
	QSqlQuery q_loader = DatabaseLayer::Database::query();
	q_loader.exec(
		QString("SELECT %1, %2, %3, %4 FROM _database_history WHERE %4 > '%5'")
		.arg(ID_KEY, QUERY_KEY, QUERY_VALUES_KEY, DATETIME_KEY, _fromDatetime)
		);

	QList<QMap<QString, QString> > databaseHistory;
	while (q_loader.next()) {
		QMap<QString, QString> historyRecord;
		historyRecord.insert(ID_KEY, q_loader.value(ID_KEY).toString());
		historyRecord.insert(QUERY_KEY, q_loader.value(QUERY_KEY).toString());
		historyRecord.insert(QUERY_VALUES_KEY, q_loader.value(QUERY_VALUES_KEY).toString());
		historyRecord.insert(DATETIME_KEY, q_loader.value(DATETIME_KEY).toString());

		databaseHistory.append(historyRecord);
	}

	return databaseHistory;
}

QMap<QString, QString> DatabaseHistoryMapper::historyRecord(const QString& _uuid)
{
	QSqlQuery q_loader = DatabaseLayer::Database::query();
	q_loader.exec(
		QString("SELECT %1, %2, %3, %4 FROM _database_history WHERE %1 = '%5'")
		.arg(ID_KEY, QUERY_KEY, QUERY_VALUES_KEY, DATETIME_KEY, _uuid)
		);

	q_loader.next();
	QMap<QString, QString> historyRecord;
	historyRecord.insert(ID_KEY, q_loader.value(ID_KEY).toString());
	historyRecord.insert(QUERY_KEY, q_loader.value(QUERY_KEY).toString());
	historyRecord.insert(QUERY_VALUES_KEY, q_loader.value(QUERY_VALUES_KEY).toString());
	historyRecord.insert(DATETIME_KEY, q_loader.value(DATETIME_KEY).toString());

	return historyRecord;
}

void DatabaseHistoryMapper::storeHistoryRecord(const QString& _uuid, const QString& _query,
	const QString& _queryValues, const QString& _datetime)
{
	QSqlQuery q_saver = DatabaseLayer::Database::query();
	q_saver.prepare(
		QString("INSERT INTO _database_history (%1, %2, %3, %4) VALUES(?, ?, ?, ?)")
		.arg(ID_KEY, QUERY_KEY, QUERY_VALUES_KEY, DATETIME_KEY)
		);
	q_saver.addBindValue(_uuid);
	q_saver.addBindValue(_query);
	q_saver.addBindValue(_queryValues);
	q_saver.addBindValue(_datetime);
	q_saver.exec();
}

void DatabaseHistoryMapper::applyHistoryRecord(const QString& _query, const QString& _queryValues)
{
	QSqlQuery q_saver = DatabaseLayer::Database::query();
	q_saver.prepare(_query);
	QVariantMap values = QVariantMapWriter::dataStringToMap(_queryValues);
	foreach (const QString& key, values.keys()) {
		q_saver.addBindValue(values.value(key));
	}
	q_saver.exec();
}

DatabaseHistoryMapper::DatabaseHistoryMapper()
{
}


