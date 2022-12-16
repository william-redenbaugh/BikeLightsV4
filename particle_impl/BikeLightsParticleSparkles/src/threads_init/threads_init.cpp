#include "threads_init.h"
#include "Particle.h"
#include "threads_list.h"

static TaskListData task_data[NUM_THREADS];

void threads_list_init(void)
{
    task_init_descriptor_t threads[NUM_THREADS] = THREAD_LIST;

    // Run each setup function for each task
    for (int n = 0; n < NUM_THREADS; n++)
    {
        threads[n].task_init_fun();
    }

    // Launch each task!
    for (int n = 0; n < NUM_THREADS; n++)
    {
        task_data[n].task_fun = threads[n].task_fun;
        task_data[n].task_name = threads[n].task_name;
        task_data[n].stack_size = threads[n].stack_size;
        task_data[n].task_priority = threads[n].task_priority;
        task_data[n].param = threads[n].param;

        task_data[n].handler =  new Thread(threads[n].task_name, threads[n].task_fun, threads[n].param, threads[n].task_priority, threads[n].stack_size);
    }
}