# -------------------------------------------------------------------------------------- #
# Конфигурация типа библиотеки для сборки                                                #
#                                                                                        #
# Этот скрипт выбирает тип библиотеки, которую необходимо создать, в зависимости         #
# от значения переменной SE_LIBRARY_OPTION_STATIC_BUILD. Если переменная установлена        #
# в TRUE (или ON), создаётся статическая библиотека. В противном случае — динамическая. #
# -------------------------------------------------------------------------------------- #

# Проверяем значение переменной SE_LIBRARY_OPTION_STATIC_BUILD
if (SE_LIBRARY_OPTION_STATIC_BUILD)
    # Если переменная SE_LIBRARY_OPTION_STATIC_BUILD установлена,
    # создаём статическую библиотеку с использованием исходных файлов SE_TARGET_SOURCE_FILES
    add_library(${CMAKE_PROJECT_NAME} STATIC ${SE_TARGET_SOURCE_FILES})
elseif (SE_LIBRARY_OPTION_SHARED_BUILD)
    # Если переменная SE_LIBRARY_OPTION_SHARED_BUILD установлена,
    # создаём динамическую библиотеку с использованием исходных файлов SE_TARGET_SOURCE_FILES
    add_library(${CMAKE_PROJECT_NAME} SHARED ${SE_TARGET_SOURCE_FILES})
else ()
    # Если ни одна из предыдущих переменных не установлена, создаём исполняемый файл
    add_executable(${CMAKE_PROJECT_NAME} ${SE_TARGET_SOURCE_FILES})
endif ()
