/**
 * @file version.h
 * @brief Заголовочный файл для работы с версиями библиотеки.
 *
 * Этот файл предоставляет функции для получения информации о версии библиотеки,
 * включая полную строку версии (major.minor.patch) и отдельные компоненты версии
 * (основную, младшую и исправительную). Используется для обеспечения совместимости
 * и контроля версий в проекте.
 *
 * Зависимости:
 * - attribute.h: Определение макроса `SE_ATTRIBUTE` для управления атрибутами функций.
 * - return.h: Определение типа `se_return_t`, используемого для возвращаемых значений.
 */

#ifndef SE_VERSION_H
#define SE_VERSION_H

#include "attribute.h"
#include "return.h"

// ------------------------------------------ Методы ------------------------------------------ //

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Возвращает строковое представление версии в формате "major.minor.patch".
 *
 * Эта функция использует макрос `se_str_from_args` для создания строки,
 * содержащей значения основных, младших и исправительных версий,
 * разделённых точками.
 *
 * @return Указатель на константную строку с версией (например, "1.2.3").
 *
 * @note Строка является статической
 *       и не должна быть освобождена вызывающим кодом.
 *
 * Пример использования:
 * @code
 * const char *version = se_version();
 * printf("Текущая версия: %s\n", version); // Вывод: "1.2.3" (пример)
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
const char *
se_version(void);

/**
 * @brief Возвращает значение основной (major) версии.
 *
 * Эта функция предоставляет доступ к компоненту основной версии,
 * определённому в `SE_VERSION_MAJOR`.
 *
 * @return Значение основной версии как `se_return_t`.
 *
 * Пример использования:
 * @code
 * se_return_t major = se_version_major();
 * printf("Major версия: %d\n", major); // Вывод: 1 (пример)
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
se_return_t
se_version_major(void);

/**
 * @brief Возвращает значение младшей (minor) версии.
 *
 * Эта функция предоставляет доступ к компоненту младшей версии,
 * определённому в `SE_VERSION_MINOR`.
 *
 * @return Значение младшей версии как `se_return_t`.
 *
 * Пример использования:
 * @code
 * se_return_t minor = se_version_minor();
 * printf("Minor версия: %d\n", minor); // Вывод: 2 (пример)
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
se_return_t
se_version_minor(void);

/**
 * @brief Возвращает значение исправительной (patch) версии.
 *
 * Эта функция предоставляет доступ к компоненту исправительной версии,
 * определённому в `SE_VERSION_PATCH`.
 *
 * @return Значение исправительной версии как `se_return_t`.
 *
 * Пример использования:
 * @code
 * se_return_t patch = se_version_patch();
 * printf("Patch версия: %d\n", patch); // Вывод: 3 (пример)
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
se_return_t
se_version_patch(void);

SE_COMPILER(EXTERN_C_END)

#endif // SE_VERSION_H
