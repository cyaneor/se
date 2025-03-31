/**
 * @file attribute_symbol.h
 * @brief Заголовочный файл, определяющий макрос
 *        для управления видимостью символов при сборке.
 *
 * Этот файл предоставляет макрос `SE_ATTRIBUTE_SYMBOL`,
 * который используется для управления видимостью символов
 * в зависимости от типа сборки библиотеки (статическая или динамическая).
 *
 * Макрос автоматически адаптируется к настройкам компиляции,
 * обеспечивая правильную экспорт/импорт символов.
 */

#ifndef SE_ATTRIBUTE_SYMBOL_H
#define SE_ATTRIBUTE_SYMBOL_H

#include "compiler.h"

#ifdef SE_LIBRARY_OPTION_STATIC_BUILD
/**
 * @def SE_ATTRIBUTE_SYMBOL
 * @brief Помечает символы как публичные для статической компоновки.
 *
 * При сборке библиотеки как статической или в случае, когда библиотека не используется
 * как общая, символы помечаются как публичные, но без атрибутов, связанных с общей библиотекой.
 * Это стандартное поведение для статической компоновки, где символы доступны, но не имеют
 * атрибутов общей библиотеки.
 */
#    define SE_ATTRIBUTE_SYMBOL
#else
#    ifdef SE_LIBRARY_OPTION_SHARED_BUILD
/**
 * @def SE_ATTRIBUTE_SYMBOL
 * @brief Помечает символы для экспорта при сборке библиотеки как общей библиотеки.
 *
 * При сборке библиотеки как общей (shared) этот макрос помечает символы как публичные
 * для экспорта. Он расширяется до `SE_COMPILER_ATTRIBUTE_SYMBOL_EXPORT`,
 * что делает символы доступными для других приложений или библиотек.
 */
#        define SE_ATTRIBUTE_SYMBOL SE_COMPILER_ATTRIBUTE_SYMBOL_EXPORT
#    else
/**
 * @def SE_ATTRIBUTE_SYMBOL
 * @brief Помечает символы для импорта при использовании библиотеки как общей библиотеки.
 *
 * Когда библиотека используется как общая (shared), этот макрос помечает символы для импорта.
 * Он расширяется до `SE_COMPILER_ATTRIBUTE_SYMBOL_IMPORT`, что позволяет символам быть связаны
 * и использованы в других приложениях или библиотеках, которые используют эту общую библиотеку.
 */
#        define SE_ATTRIBUTE_SYMBOL SE_COMPILER_ATTRIBUTE_SYMBOL_IMPORT
#    endif // SE_LIBRARY_OPTION_SHARED_BUILD
#endif     // SE_LIBRARY_OPTION_STATIC_BUILD

#endif // SE_ATTRIBUTE_SYMBOL_H
