#ifndef SYNCHRONIZATIONMANAGER_H
#define SYNCHRONIZATIONMANAGER_H

#include <QObject>

namespace Domain {
	class Scenario;
}


namespace ManagementLayer
{
	/**
	 * @brief Управляющий синхронизацией
	 */
	class SynchronizationManager : public QObject
	{
		Q_OBJECT

	public:
		explicit SynchronizationManager(QObject* _parent, QWidget* _parentView);

	public slots:
		/**
		 * @brief Авторизоваться используя сохранённые параметры авторизации
		 */
		void login();

		/**
		 * @brief Авторизоваться
		 */
		void aboutLogin(const QString& _userName, const QString& _password);

		/**
		 * @brief Закрыть авторизацию
		 */
		void aboutLogout();

		/**
		 * @brief Загрузить список доступных проектов
		 */
		void aboutLoadProjects();

		/**
		 * @brief Синхронизировать сценарий полностью
		 * @note Скачать с сервера все версии, которых нет в БД и
		 *		 отправить на сервер все версии, которых не на нём.
		 *		 Используется при открытии проекта.
		 */
		void aboutSyncScenario(bool _isDraft = false);

		/**
		 * @brief Загрузить данные, которых нет в БД
		 */
		void aboutSyncData();

		/**
		 * @brief Актуализировать сценарий
		 */
		void aboutUpdateScenario(bool _isDraft = false);

		/**
		 * @brief Актуализировать данные
		 */
		void aboutUpdateData();

		/**
		 * @brief Сохранить последнюю версию сценария на сервер
		 */
		/** @{ */
		void aboutSaveScenarioToServer(bool _isDraft, bool _isAsync);
		void aboutSaveScenarioToServer(Domain::Scenario* _scenario, bool _isAsync);
		/** @} */

		/**
		 * @brief Сохранить заданную версию сценария в локальную БД
		 * @note Если UUID не задан, сохранена будет последняя версия и актуализирована
		 */
		void aboutSaveScenarioToDB(const QString& _uuid, bool _isDraft);

		/**
		 * @brief Сохранить данные сценария
		 */
		void aboutSaveData();

		/**
		 * @brief Отправить изменение на сервер
		 */
		void aboutSaveDataToServer(const QString& _changeUuid);

		/**
		 * @brief Сохранить заданное изменение в локальную БД
		 */
		void aboutSaveDataToDB(const QString& _changeUuid);

	signals:
		/**
		 * @brief Авторизация пройдена успешно
		 */
		void loginAccepted(const QString& _userName);

		/**
		 * @brief Авторизация не пройдена
		 */
		void loginNotAccepted(const QString& _userName, const QString& _password, const QString& _error);

		/**
		 * @brief Авторизация закрыта
		 */
		void logoutAccepted();

		/**
		 * @brief Список доступных проектов получен
		 */
		void remoteProjectsLoaded(const QString& _projectsXml);

		/**
		 * @brief Не удалось получить список доступных проектов
		 */
		void remoteProjectsNotLoaded(const QString& _error);

	private:
		/**
		 * @brief Настроить соединения
		 */
		void initConnections();

		/**
		 * @brief Заблокировать ненадолго выполнение функции
		 * @note Применяется для того, чтобы интерфейс не моргал
		 */
		void sleepALittle();

	private:
		/**
		 * @brief Указатель на главную форму приложения
		 */
		QWidget* m_view;

		/**
		 * @brief Ключ сессии
		 */
		QString m_sessionKey;

		/**
		 * @brief Дата и время последнего отправленного изменения данных
		 */
		QString m_lastSendedDataDatetime;



		//
		// Пока не используемые функции
		//

//		/**
//		 * @brief Получить список синхронизируемых проектов
//		 * @note Тут должны быть как собственные, так и те, к которым предоставлен доступ
//		 */
//		void projectsList() {}

//		/**
//		 * @brief Синхронизировать проект
//		 */
//		void syncProject() {}

//		/**
//		 * @brief Передать управляющему "слепок" с изменениями
//		 */
//		void appendChanges() {}

//		/**
//		 * @brief Передать управляющему позицию курсора
//		 */
//		void setCursorPosition(int _position);

//	signals:
//		/**
//		 * @brief Обновить информацию о курсорах
//		 */
//		void updateCursors();

//		/**
//		 * @brief Применить изменения принятые от сервера
//		 */
//		void applyChanges();

//	private slots:
//		/**
//		 * @brief Оправить изменения на сервер
//		 */
//		void aboutSendChangesToServer() {}

//		/**
//		 * @brief Получены изменения от сервера
//		 */
//		void aboutGetChangesFromServer() {}

//	private:
//		/**
//		 * @brief Авторизован ли пользователь в данный момент
//		 */
//		bool isLogged() const { return true; }

//	private:
//		/**
//		 * @brief Позиция курсора
//		 */
//		int m_cursorPosition;
	};
}

#endif // SYNCHRONIZATIONMANAGER_H
