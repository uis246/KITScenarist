#ifndef SCENARIOSTORAGE_H
#define SCENARIOSTORAGE_H

#include "StorageFacade.h"

class QString;

namespace Domain {
	class Scenario;
	class ScenariosTable;
}

using namespace Domain;


namespace DataStorageLayer
{
	class ScenarioStorage
	{
	public:
		/**
		 * @brief Получить все версии сценария
		 */
		ScenariosTable* all();

		/**
		 * @brief Получить текущую версию сценария
		 */
		Scenario* current();

		/**
		 * @brief Сохранить текст сценария
		 * @param Текст сценария в формате xml
		 */
		Scenario* storeScenario(const QString& _name, const QString& _synopsis, const QString& _text);

		/**
		 * @brief Очистить хранилище
		 */
		void clear();

        /**
         * @brief Ожидание завершения всех операций с БД
         */
        void wait();

	private:
		ScenariosTable* m_all;

	private:
		ScenarioStorage();

		// Для доступа к конструктору
		friend class StorageFacade;
	};
}

#endif // SCENARIOSTORAGE_H
