/**
 * @file attribute_force_inline.h
 * @brief Заголовочный файл, предоставляющий алиас
 *        для атрибута принудительной инлайнизации функций.
 *
 * Этот файл определяет макрос `SE_ATTRIBUTE_FORCE_INLINE`,
 * который является удобным псевдонимом для `SE_COMPILER_ATTRIBUTE_FORCE_INLINE`.
 *
 * Он используется для принудительной инлайнизации функций
 * в критически важных по производительности участках кода.
 *
 * Основные особенности:
 * - Предоставляет единообразное короткое имя для атрибута инлайнирования.
 * - Полностью совместим с оригинальным макросом `SE_COMPILER_ATTRIBUTE_FORCE_INLINE`.
 * - Поддерживает все компиляторы, с которыми работает базовый макрос.
 *
 * Пример использования:
 * @code
 * SE_ATTRIBUTE_FORCE_INLINE void critical_function() {
 *     // Тело функции
 * }
 * @endcode
 *
 * @see SE_COMPILER_ATTRIBUTE_FORCE_INLINE
 */
#ifndef SE_ATTRIBUTE_FORCE_INLINE_H
#define SE_ATTRIBUTE_FORCE_INLINE_H

#include "compiler.h"

/**
 * @def SE_ATTRIBUTE_FORCE_INLINE
 * @brief Алиас для макроса принудительной инлайнизации функций.
 * @details Этот макрос является псевдонимом для SE_COMPILER_ATTRIBUTE_FORCE_INLINE,
 *          предоставляя более короткое и удобное имя для атрибута принудительной инлайнизации.
 *          Поведение и поддерживаемые компиляторы идентичны оригинальному макросу.
 *
 * @see SE_COMPILER_ATTRIBUTE_FORCE_INLINE
 */
#define SE_ATTRIBUTE_FORCE_INLINE SE_COMPILER_ATTRIBUTE_FORCE_INLINE

#endif // SE_ATTRIBUTE_FORCE_INLINE_H