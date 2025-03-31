/**
 * @file elif.h
 * @brief Заголовочный файл, содержащий макрос для упрощённой версии оператора `else if`.
 *
 * Этот файл определяет макрос `elif`, который является альтернативой стандартному оператору
 * `else if` в языке C. Использование этого макроса улучшает читаемость и делает код более
 * выразительным, что может быть полезно в некоторых корпоративных стандартах
 * или для улучшения визуального восприятия кода.
 *
 * @note Этот макрос предназначен для упрощения записи условных операторов,
 *       но необходимо быть осторожным при его использовании,
 *       чтобы не ухудшить понимание кода для других разработчиков.
 *
 * @see @ref elif
 */

#ifndef SE_ELIF_H
#define SE_ELIF_H

/**
 * @def elif
 * @brief Упрощённая версия оператора `else if`.
 *
 * Данный макрос предоставляет альтернативный способ записи конструкции `else if`,
 * улучшая читаемость кода или соблюдая корпоративные стандарты кодирования.
 *
 * @note Используйте этот макрос,
 *       если хотите сделать код более выразительным и лаконичным.
 *
 * Пример использования
 * @code
 * if (condition1) {
 *     // действия при условии 1
 * }
 * elif (condition2) {
 *     // действия при условии 2
 * }
 * else {
 *     // действия по умолчанию
 * }
 * @endcode
 */
#ifndef elif
#    define elif else if
#endif // elif

#endif // SE_ELIF_H
