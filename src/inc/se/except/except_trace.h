#ifndef SE_EXCEPT_TRACE_H
#define SE_EXCEPT_TRACE_H

/**
 * @struct se_except_trace
 * @brief Структура, содержащая информацию о трассировке исключения.
 *
 * Используется в режиме отладки для хранения данных
 * о месте возникновения исключения.
 */
typedef struct se_except_trace
{
    /**
     * @var timestamp
     * @brief Метка времени возникновения исключения.
     *
     * Указатель на строку, содержащую значение `__TIMESTAMP__`
     * в момент выброса исключения.
     */
    const char *timestamp;

    /**
     * @var filename
     * @brief Имя файла, где произошло исключение.
     *
     * Указатель на строку, содержащую значение `__FILE__`
     * в момент выброса исключения.
     */
    const char *filename;

    /**
     * @var function
     * @brief Имя функции, где произошло исключение.
     *
     * Указатель на строку, содержащую значение `__FUNCTION__`
     * в момент выброса исключения.
     */
    const char *function;
} se_except_trace_t;

#endif // SE_EXCEPT_TRACE_H
