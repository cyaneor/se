/**
 * @file runtime_return.h
 * @brief Заголовочный файл для макроса `se_runtime_return`.
 *
 * Этот файл содержит определение макроса `se_runtime_return`,
 * который позволяет немедленно завершить выполнение функции и вернуть заданное значение.
 * Макрос используется для реализации ранних выходов из функции, например, в обработчиках ошибок.
 *
 * @details Макрос `se_runtime_return` является удобным инструментом для ситуаций,
 *          когда нужно прекратить выполнение функции в любой момент и вернуть значение,
 *          без необходимости дополнительно писать инструкции для выхода из функции.
 *
 * @note Использование макроса следует ограничить, чтобы избежать излишней сложности
 *       в коде и сохранить его читаемость. Этот макрос полезен в случаях,
 *       когда необходимо выполнить ранний выход из функции или обработать ошибку.
 */

#ifndef SE_RUNTIME_RETURN_H
#define SE_RUNTIME_RETURN_H

/**
 * @def se_runtime_return
 * @brief Прерывание выполнения с возвратом заданного значения.
 *
 * Этот макрос позволяет выполнить немедленный выход из функции с возвратом указанного значения.
 * Он может быть использован в случаях, когда необходимо прервать выполнение функции и вернуть
 * результат в любом месте кода.
 *
 * @param ... Значение, которое будет возвращено из функции.
 * @return Возвращает значение, переданное в параметре.
 *
 * @note Использование этого макроса следует ограничить ситуациями,
 *       когда необходимо немедленно завершить выполнение функции с возвратом значения.
 *       Он может быть полезен в обработчиках ошибок или при реализации ранних выходов.
 */
#define se_runtime_return(...) return __VA_ARGS__

#endif // SE_RUNTIME_RETURN_H
