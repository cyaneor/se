# -------------------------------------------------------------------------------------- #
# Конфигурация версии проекта                                                            #
#                                                                                        #
# Этот скрипт преобразует версию проекта в список компонентов (мажорная, минорная и      #
# патч версии), сохраняет их в кэше и добавляет как макросы для использования в коде.    #
# Данная конфигурация позволяет получать версию проекта в различных частях сборки.       #
# -------------------------------------------------------------------------------------- #

# Заменяет точки в версии проекта на точки с запятыми.
# Например, "1.2.3" -> "1;2;3".
string(REPLACE "." ";" SE_VERSION_LIST ${PROJECT_VERSION})

# Получаем первый элемент списка (основная версия) и сохраняем в SE_VERSION_MAJOR.
list(GET SE_VERSION_LIST 0 SE_VERSION_MAJOR)

# Получаем второй элемент списка (минорная версия) и сохраняем в SE_VERSION_MINOR.
list(GET SE_VERSION_LIST 1 SE_VERSION_MINOR)

# Получаем третий элемент списка (патч версия) и сохраняем в SE_VERSION_PATCH.
list(GET SE_VERSION_LIST 2 SE_VERSION_PATCH)

# Сохраняем основную версию в кэш для последующего использования в CMake,
# и делаем это доступным как переменную кэша, добавляя FORCE,
# чтобы переопределить возможные ранее заданные значения.
set(SE_VERSION_MAJOR ${SE_VERSION_MAJOR} CACHE STRING "vm major version component" FORCE)

# Сохраняем минорную версию в кэш.
set(SE_VERSION_MINOR ${SE_VERSION_MINOR} CACHE STRING "vm minor version component" FORCE)

# Сохраняем патч-версию в кэш.
set(SE_VERSION_PATCH ${SE_VERSION_PATCH} CACHE STRING "vm patch version component" FORCE)

# Добавляем значения версий как определённые макросы,
# доступные для компиляции (compile definitions).
#
# Это позволит использовать их как SE_VERSION_MAJOR,
# SE_VERSION_MINOR и SE_VERSION_PATCH в коде.
list(APPEND SE_TARGET_PRIVATE_COMPILE_DEFINITIONS
        SE_VERSION_MAJOR=${SE_VERSION_MAJOR}
        SE_VERSION_MINOR=${SE_VERSION_MINOR}
        SE_VERSION_PATCH=${SE_VERSION_PATCH}
)

# Очищаем временные переменные SE_VERSION_MAJOR, SE_VERSION_MINOR и SE_VERSION_PATCH,
# так как они больше не нужны в глобальном пространстве CMake.
unset(SE_VERSION_MAJOR)
unset(SE_VERSION_MINOR)
unset(SE_VERSION_PATCH)
