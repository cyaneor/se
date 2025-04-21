/**
 * @file attribute.h
 * @brief Заголовочный файл для определения специфичных атрибутов проекта.
 *
 * Этот файл предназначен для централизованного управления атрибутами,
 * которые могут быть настроены в зависимости от конфигурации проекта.
 *
 * Конфигурация атрибутов осуществляется через CMake, что позволяет
 * гибко адаптировать поведение проекта в зависимости от выбранных
 * опций сборки.
 */

#ifndef SE_ATTRIBUTE_H
#define SE_ATTRIBUTE_H

#include "attribute_force_inline.h"
#include "attribute_noreturn.h"
#include "attribute_symbol.h"
#include "attribute_target.h"
#include "attribute_thread_local.h"
#include "attribute_unused.h"

/**
 * @def SE_ATTRIBUTE(N)
 * @brief Разворачивается до соответствующего макроса атрибута.
 *
 * Этот макрос принимает один аргумент `N` и объединяет его с
 * `SE_ATTRIBUTE_` для формирования полного имени макроса атрибута.
 *
 * @param N Суффикс определяемого макроса атрибута.
 */
#define SE_ATTRIBUTE(N) SE_ATTRIBUTE_##N

#endif // SE_ATTRIBUTE_H