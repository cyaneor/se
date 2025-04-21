# -------------------------------------------------------------------------------------- #
# Синхронизация настроек CRT для MSVC                                                    #
#                                                                                        #
# Этот скрипт задаёт опции компиляции для подключения C Runtime Library (CRT) в          #
# зависимости от типа сборки (статическая или динамическая) при использовании MSVC.      #
# Использует /MT для статической CRT и /MD для динамической CRT.                         #
# -------------------------------------------------------------------------------------- #

if (SE_LIBRARY_OPTION_STATIC_BUILD)
    if (MSVC)
        list(APPEND SE_TARGET_PRIVATE_COMPILE_OPTIONS $<$<CONFIG:Release>:/MT> $<$<CONFIG:Debug>:/MTd>)
    endif ()
elseif (SE_LIBRARY_OPTION_SHARED_BUILD)
    if (MSVC)
        list(APPEND SE_TARGET_PRIVATE_COMPILE_OPTIONS $<$<CONFIG:Release>:/MD> $<$<CONFIG:Debug>:/MDd>)
    endif ()
else ()
    if (MSVC)
        list(APPEND SE_TARGET_PRIVATE_COMPILE_OPTIONS $<$<CONFIG:Release>:/MD> $<$<CONFIG:Debug>:/MDd>)
    endif ()
endif ()