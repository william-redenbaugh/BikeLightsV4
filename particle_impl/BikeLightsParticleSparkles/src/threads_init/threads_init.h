#ifndef _THREADS_INIT_H
#define _THREADS_INIT_H
#include "Particle.h"

/**
 * @brief Structure that manages task initialization.
 * @note Designed to help intiailize lists of tasks all at once.
 */
typedef struct {
    void(*task_fun)(void *param);
    void (*task_init_fun)(void);
    void *param;
    const char *task_name;
    size_t stack_size;
    int task_priority;
}task_init_descriptor_t;

struct TaskListData{
    void(*task_fun)(void *param);
    const char *task_name;
    size_t stack_size;
    void *param;
    int task_priority;
    Thread *handler;

};

/**
 * @brief Initialize all the threads that we put into our list.
 *
 */
void threads_list_init(void);

#endif