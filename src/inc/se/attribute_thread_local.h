/**
 * @file attribute_thread_local.h
 * @brief Определение атрибута для локальных потоковых переменных.
 *
 * Этот файл содержит определения макроса для указания, что переменные являются локальными
 * для потока. В зависимости от конфигурации, атрибут может быть определен с использованием
 * компиляторского атрибута или оставаться пустым.
 *
 * - Если включена опция SE_LIBRARY_OPTION_THREAD_LOCAL, макрос SE_ATTRIBUTE_THREAD_LOCAL
 *   будет определен как атрибут компилятора, указывающий на то,
 *   что переменные локальны для потока.
 *
 * - В противном случае, этот макрос остается пустым,
 *   что означает отсутствие специального атрибута для локальности в потоке.
 */

#ifndef SE_ATTRIBUTE_THREAD_LOCAL_H
#define SE_ATTRIBUTE_THREAD_LOCAL_H

#include "compiler.h"

#ifdef SE_LIBRARY_OPTION_THREAD_LOCAL
/**
 * @def SE_ATTRIBUTE_THREAD_LOCAL
 * @brief Атрибут для локальных потоковых переменных.
 *
 * Если включена опция SE_LIBRARY_OPTION_THREAD_LOCAL,
 * этот макрос будет определен как атрибут компилятора,
 * указывающий на то, что переменная является локальной для потока.
 */
#    define SE_ATTRIBUTE_THREAD_LOCAL SE_COMPILER_ATTRIBUTE_THREAD_LOCAL
#else
/**
 * @def SE_ATTRIBUTE_THREAD_LOCAL
 * @brief Пустой макрос для локальных потоковых переменных.
 *
 * Если опция SE_LIBRARY_OPTION_THREAD_LOCAL
 * не включена, этот макрос остается пустым, что означает, что
 * переменные не имеют специального атрибута для локальности в потоке.
 */
#    define SE_ATTRIBUTE_THREAD_LOCAL
#endif

#endif // SE_ATTRIBUTE_THREAD_LOCAL_H
