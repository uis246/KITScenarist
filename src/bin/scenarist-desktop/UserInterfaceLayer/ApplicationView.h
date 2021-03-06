#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include <QWidget>


namespace UserInterface
{
	/**
	 * @brief Главное окно приложения
	 */
	class ApplicationView : public QWidget
	{
		Q_OBJECT
	public:
		explicit ApplicationView(QWidget* _parent = 0);

		/**
		 * @brief Добавить для сплитеров функциональность смены панелей местами
		 */
		void initSplittersRightClick();

	signals:
		/**
		 * @brief Пользователь хочет закрыть приложение
		 */
		void wantToClose();

	protected:
		/**
		 * @brief Переопределяется для отлавливания события закрытия приложения
		 */
		void closeEvent(QCloseEvent* _event);

		/**
		 * @brief Переопределяется для того, чтобы добавить для сплитеров функциональность смены панелей местами
		 */
		bool eventFilter(QObject* _object, QEvent* _event);
	};
}

#endif // APPLICATIONVIEW_H
