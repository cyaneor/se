/**
 * @file runtime_throw.h
 * @brief Заголовочный файл, объединяющий макросы
 *        для обработки исключений в `runtime`.
 *
 * Этот файл включает в себя определения макросов для выбрасывания исключений
 * как в режиме отладки, так и в режиме релиза. В зависимости от настроек
 * компиляции, будут использоваться соответствующие реализации макросов
 * из файлов `runtime_throw_debug.h` и `runtime_throw_release.h`.
 *
 * Данный подход позволяет обеспечить гибкость в обработке ошибок,
 * предоставляя возможность включения или отключения отладочной
 * информации в зависимости от конфигурации сборки.
 *
 * @see se_runtime_throw_debug.h
 * @see se_runtime_throw_release.h
 */

#ifndef SE_RUNTIME_THROW_H
#define SE_RUNTIME_THROW_H

#ifdef SE_COMPILE_OPTION_DEBUG
#    include "runtime_throw_debug.h"
#else
#    include "runtime_throw_release.h"
#endif // SE_COMPILE_OPTION_DEBUG

#endif // SE_RUNTIME_THROW_H
