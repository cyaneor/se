# -------------------------------------------------------------------------------------- #
# Проверка размеров типов данных и добавление соответствующих дефиниций                  #
#                                                                                        #
# Этот скрипт проверяет размеры различных типов данных (void*, char, wchar_t, short,     #
# int, long, long long, __int128) на целевой платформе и добавляет макроопределения,     #
# которые могут быть использованы при компиляции для настройки поведения                 #
# программы в зависимости от характеристик платформы.                                    #
# -------------------------------------------------------------------------------------- #

# Включаем модуль CheckTypeSize, который позволяет проверять размеры типов данных
include(CheckTypeSize)

# Проверяем размер указателя на void (void*) и сохраняем результат в переменной SIZEOF_VOID_P
check_type_size("void *" SIZEOF_VOID_P)

# Проверяем размер типа "char" и сохраняем результат в переменной SIZEOF_CHAR
check_type_size("char" SIZEOF_CHAR)

# Проверяем размер типа "wchar_t" и сохраняем результат в переменной SIZEOF_WCHAR
check_type_size("wchar_t" SIZEOF_WCHAR)

# Проверяем размер типа "short" и сохраняем результат в переменной SIZEOF_SHORT
check_type_size("short" SIZEOF_SHORT)

# Проверяем размер типа "int" и сохраняем результат в переменной SIZEOF_INT
check_type_size("int" SIZEOF_INT)

# Проверяем размер типа "long" и сохраняем результат в переменной SIZEOF_LONG
check_type_size("long" SIZEOF_LONG)

# Проверяем размер типа "long long" и сохраняем результат в переменной SIZEOF_LLONG
check_type_size("long long" SIZEOF_LLONG)

# Проверяем размер типа "size_t" и сохраняем результат в переменной SIZEOF_SIZE
check_type_size("size_t" SIZEOF_SIZE)

# Проверяем размер типа "__int128" и сохраняем результат в переменной SIZEOF_INT128
check_type_size("__int128" SIZEOF_INT128)

# Если размер указателя на void был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_VOID_P})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_PTR_SIZE=${SIZEOF_VOID_P})
endif ()

# Если размер типа char был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_CHAR})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_CHAR_T_SIZE=${SIZEOF_CHAR})
endif ()

# Если размер типа wchar_t был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_WCHAR})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_WCHAR_T_SIZE=${SIZEOF_WCHAR})
endif ()

# Если размер типа short был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_SHORT})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_SHORT_T_SIZE=${SIZEOF_SHORT})
endif ()

# Если размер типа int был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_INT})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_INT_T_SIZE=${SIZEOF_INT})
endif ()

# Если размер типа long был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_LONG})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_LONG_T_SIZE=${SIZEOF_LONG})
endif ()

# Если размер типа long long был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_LLONG})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_LLONG_T_SIZE=${SIZEOF_LLONG})
endif ()

# Если размер типа size_t был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_SIZE})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_SIZE_T_SIZE=${SIZEOF_SIZE})
endif ()

# Если размер типа __int128 был определён, добавляем дефиницию для его размера в список компиляции
if (${HAVE_SIZEOF_INT128})
    list(APPEND SE_TARGET_PUBLIC_COMPILE_DEFINITIONS SE_INT128_T_SIZE=${SIZEOF_INT128})
endif ()
