file(GLOB OPTIONS_FILES "${SE_CMAKE_CURRENT_OPTIONS_DIR}/*_options.cmake")
list(LENGTH OPTIONS_FILES LENGTH_RESULT)

if (LENGTH_RESULT EQUAL 0)
    message(NOTICE "There are no files with CMake options in the directory")
else ()
    message(STATUS "Found ${LENGTH_RESULT} files with CMake options in the directory:")

    # Создадим список для хранения файлов и их приоритетов
    set(OPTION_FILES_WITH_PRIORITY "")

    foreach (OPTION_FILE ${OPTIONS_FILES})
        # Читаем первую строку файла
        file(READ ${OPTION_FILE} FIRST_LINE)

        # Проверяем, есть ли приоритет в первой строке
        string(REGEX MATCH "# \\[([0-9]+)\\]" PRIORITY_MATCH "${FIRST_LINE}")
        if (PRIORITY_MATCH)
            # Извлекаем приоритет
            string(REGEX MATCH "[0-9]+" PRIORITY "${PRIORITY_MATCH}")
            list(APPEND OPTION_FILES_WITH_PRIORITY "${PRIORITY}:${OPTION_FILE}")
        else ()
            # Если приоритета нет, добавляем файл с приоритетом 9
            list(APPEND OPTION_FILES_WITH_PRIORITY "9:${OPTION_FILE}")
        endif ()
    endforeach ()

    # Сортируем файлы по приоритету
    list(SORT OPTION_FILES_WITH_PRIORITY)

    # Включаем файлы в порядке приоритета
    foreach (OPTION_WITH_PRIORITY ${OPTION_FILES_WITH_PRIORITY})
        string(SUBSTRING ${OPTION_WITH_PRIORITY} 2 -1 OPTION_FILE) # Убираем приоритет
        message(STATUS ":: including -> ${OPTION_FILE}")
        include(${OPTION_FILE})
    endforeach ()
endif ()
