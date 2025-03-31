/**
 * @file runtime_exception_catch_stack.h
 * @brief Механизм обработки исключений времени выполнения.
 *
 * Данный модуль предоставляет:
 * - Стек фреймов исключений с ограниченной глубиной.
 * - Функции для управления контекстами исключений.
 * - Механизм нелокальных переходов при возникновении ошибок.
 * - Поддержку отладочной информации в DEBUG-сборках.
 *
 * @note Максимальная глубина стека определяется `SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX`.
 * @warning Требует аккуратного использования для поддержания целостности стека.
 */

#ifndef SE_RUNTIME_EXCEPTION_CATCH_STACK_H
#define SE_RUNTIME_EXCEPTION_CATCH_STACK_H

#include "bool.h"
#include "exception_catch.h"
#include "nullptr.h"
#include "runtime_terminate.h"

/**
 * @def se_runtime_exception_catch_stack_capture
 * @brief Макрос для захвата контекста выполнения
 *        и установки обработчика исключений.
 *
 * Объединяет операции `push` и `setjmp` в единую атомарную операцию:
 * 1. Помещает фрейм исключения в стек обработчиков.
 * 2. Захватывает текущий контекст выполнения с помощью `setjmp`.
 * 3. Возвращает точку входа для обработки исключений.
 *
 * @param x Указатель на фрейм исключения (`se_exception_catch_t*`).
 * @return 0 - при первоначальном сохранении контекста.
 * @return >0 - при переходе из `se_runtime_exception_catch_stack_throw()`.
 *
 * @note Используется как основа для реализации блоков `try/catch`.
 * @warning Должен использоваться ТОЛЬКО в условиях `if/switch`.
 *
 * Пример использования:
 * @code
 * if (se_runtime_exception_catch_stack_capture(frame)) {
 *   // Код обработки исключения
 * }
 * @endcode
 *
 * @see se_runtime_exception_catch_stack_push()
 * @see se_runtime_exception_catch_stack_throw()
 */
#define se_runtime_exception_catch_stack_capture(x)                                                \
    setjmp(se_runtime_exception_catch_stack_push(x)->env)

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Получить текущий активный фрейм исключения из стека обработки исключений.
 *
 * Функция возвращает указатель на текущий активный фрейм исключения в потоке.
 * Фрейм исключения представляет собой контекст обработки исключения
 * в текущей точке программы.
 *
 * @return se_exception_catch_t* Указатель на текущий фрейм исключения.
 */
se_exception_catch_t *
se_runtime_exception_catch_stack_get_current(void);

/**
 * @brief Проверяет, находится ли механизм обработки исключений в начальном состоянии.
 *
 * Функция проверяет, указывает ли текущий указатель исключения (`m_runtime_exception`)
 * на начало массива фреймов исключений (`m_runtime_exceptions`).
 * Это означает, что стек исключений пуст и нет активных обработчиков исключений.
 *
 * @return true - если указатель исключения находится
 *                в начальной позиции (нет активных обработчиков).
 * @return false - если есть хотя бы один активный обработчик исключения.
 */
bool
se_runtime_exception_catch_stack_is_begin(void);

/**
 * @brief Проверяет, достигнут ли максимальный уровень вложенности обработки исключений
 *
 * Функция определяет, достиг ли указатель текущего исключения (`m_runtime_exception`)
 * конца массива фреймов исключений. Это означает, что стек обработчиков исключений
 * заполнен до максимально возможного уровня (`SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX`).
 *
 * @return true - если достигнут максимальный уровень вложенности обработчиков исключений.
 * @return false - если есть возможность добавить новые обработчики исключений.
 */
bool
se_runtime_exception_catch_stack_is_end(void);

/**
 * @brief Перемещает указатель на следующий фрейм исключения и возвращает его.
 *
 * Функция выполняет следующие действия:
 * 1. Проверяет возможность перемещения (не достигнут ли конец стека исключений).
 * 2. Если перемещение возможно - увеличивает указатель текущего исключения.
 * 3. Возвращает новый текущий фрейм исключения.
 *
 * @return Указатель на следующий фрейм исключения, если перемещение успешно.
 * @return nullptr если достигнут максимальный уровень вложенности (конец стека).
 *
 * @note Используется для установки нового обработчика исключений.
 * @warning Перед вызовом необходимо убедиться в доступности
 *          следующего фрейма с помощью `se_runtime_exception_catch_stack_is_end()`.
 */
se_exception_catch_t *
se_runtime_exception_catch_stack_next(void);

/**
 * @brief Перемещает указатель на предыдущий фрейм исключения и возвращает его.
 *
 * Функция выполняет следующие действия:
 * 1. Проверяет, не находится ли указатель в начальном положении.
 * 2. Если перемещение возможно - уменьшает указатель текущего исключения.
 * 3. Возвращает новый текущий фрейм исключения.
 *
 * @return Указатель на предыдущий фрейм исключения, если перемещение успешно.
 * @return nullptr если указатель находится в начальном положении (нет активных обработчиков).
 *
 * @note Используется при завершении обработки исключения для возврата к предыдущему контексту.
 * @warning Перед вызовом необходимо убедиться, что указатель не в начальном положении.
 *          с помощью `se_runtime_exception_catch_stack_is_begin()`.
 */
se_exception_catch_t *
se_runtime_exception_catch_stack_prev(void);

/**
 * @brief Добавляет фрейм исключения в стек обработчиков.
 *
 * Функция выполняет следующие действия:
 * 1. Проверяет доступность места в стеке исключений.
 * 2. Сохраняет переданный фрейм исключения в текущей позиции.
 * 3. Перемещает указатель на следующую позицию в стеке.
 *
 * @param e Указатель на фрейм исключения для добавления в стек.
 * @return Указатель на добавленный фрейм исключения в случае успеха.
 * @return nullptr если стек исключений заполнен (достигнут `SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX`).
 *
 * @note Используется при входе в блок `try` для регистрации обработчика исключений.
 * @warning Необходимо гарантировать, что каждый `push` будет сбалансирован соответствующим `pop`.
 */
se_exception_catch_t *
se_runtime_exception_catch_stack_push(se_exception_catch_t *e);

/**
 * @brief Выбрасывает исключение и передает управление ближайшему обработчику.
 *
 * Функция выполняет нелокальный переход
 * к последнему зарегистрированному обработчику исключений:
 * 1. Получает предыдущий фрейм исключения из стека.
 * 2. Копирует информацию об исключении в фрейм.
 * 3. Выполняет переход через `longjmp` к точке обработки.
 * 4. Если обработчиков нет - аварийно завершает программу.
 *
 * @param exception Указатель на объект исключения для передачи обработчику.
 * @note Принудительно встраиваемая функция для оптимизации критичного пути.
 * @warning Должна вызываться только в контексте обработки ошибок.
 * @warning Нельзя вызывать если стек обработчиков пуст (приведет к завершению программы).
 */
SE_ATTRIBUTE(FORCE_INLINE)
SE_ATTRIBUTE(NORETURN)
void
se_runtime_exception_catch_stack_throw(const se_exception_t *exception)
{
    se_exception_catch_t *prev = se_runtime_exception_catch_stack_prev();
    if (prev)
    {
        prev->exception = *exception;
        longjmp(prev->env, se_error_get_code((se_error_t *)prev));
    }
    se_runtime_terminate();
}

/**
 * @brief Повторно выбрасывает текущее исключение вверх по стеку обработчиков.
 *
 * Функция выполняет следующие действия:
 * 1. Получает текущий фрейм исключения из стека обработчиков.
 * 2. Повторно выбрасывает содержащееся в нем исключение с помощью
 *    `se_runtime_exception_catch_stack_throw()`.
 *
 * @note Принудительно встраиваемая функция (`FORCE_INLINE`) для оптимизации критичного пути.
 * @note Используется в блоках `catch` для передачи исключения выше по стеку.
 * @warning Должна вызываться только в контексте обработки исключений.
 *
 * Пример использования:
 * @code
 * if (se_runtime_exception_catch_stack_capture(frame)) {
 *   // Обработка исключения
 *   se_runtime_exception_catch_stack_rethrow(); // Передаем исключение выше
 * }
 * @endcode
 *
 * @see se_runtime_exception_catch_stack_throw()
 * @see se_runtime_exception_catch_stack_get_current()
 */
SE_ATTRIBUTE(FORCE_INLINE)
SE_ATTRIBUTE(NORETURN)
void
se_runtime_exception_catch_stack_rethrow(void)
{
    const se_exception_catch_t *cur = se_runtime_exception_catch_stack_get_current();
    se_runtime_exception_catch_stack_throw(&cur->exception);
}

/**
 * @brief Выбрасывает ошибку времени выполнения
 *        с дополнительной отладочной информацией.
 *
 * Вспомогательная функция-обёртка
 * для `se_runtime_exception_catch_stack_throw()`, которая:
 * 1. Создаёт объект исключения на основе кода ошибки
 * 2. В отладочных сборках (`DEBUG`) сохраняет дополнительный контекст:
 *    - Временную метку момента возникновения ошибки
 *    - Исходный файл, где произошла ошибка
 *    - Имя функции, где произошла ошибка
 * 3. Делегирует вызов основному механизму выбрасывания исключений
 *
 * @param err Код ошибки для выбрасывания (тип `se_error_t`)
 *
 * @note `FORCE_INLINE` гарантирует минимальные накладные расходы для критичного пути обработки
 * ошибок.
 * @note Отладочная информация собирается только при определённом `SE_COMPILE_OPTION_DEBUG`.
 * @warning Как и все операции выбрасывания, требует соответствующего обработчика исключений.
 * @warning При отсутствии обработчика приведёт к завершению работы рантайма.
 */
SE_ATTRIBUTE(FORCE_INLINE)
SE_ATTRIBUTE(NORETURN)
void
se_runtime_exception_catch_stack_throw_error(se_error_t err)
{
#ifdef SE_COMPILE_OPTION_DEBUG
    const se_exception_t e = {.err = err, .trace = {__TIMESTAMP__, __FILE__, __FUNCTION__}};
#else
    const se_exception_t e = {.err = err};
#endif // SE_COMPILE_OPTION_DEBUG
    se_runtime_exception_catch_stack_throw(&e);
}

SE_COMPILER(EXTERN_C_END)

#endif // SE_RUNTIME_EXCEPTION_CATCH_STACK_H