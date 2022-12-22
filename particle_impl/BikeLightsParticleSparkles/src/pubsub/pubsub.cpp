#include "pubsub.h"
#include "Particle.h"
#include "threads_init/threads_list.h"
#include "event_type_list.h"
#include "error.h"

static os_queue_t global_eventspace;
static bool event_management_init = false;

static os_queue_t local_eventspaces[NUM_THREADS];
static event_type_t **subscribed_eventspaces;
static int num_subscribed_events[NUM_THREADS];

int num_eventspaces = 0;

static os_mutex_t event_management_mutx;

void event_management_module_init(void){
    os_queue_create(&global_eventspace, sizeof(event_data_t), 32, NULL);
    subscribed_eventspaces = (event_type_t**)malloc(sizeof(event_type_t*) * NUM_THREADS);
    memset(num_subscribed_events, 0, sizeof(num_subscribed_events));
    os_mutex_create(&event_management_mutx);
    event_management_init = true;
}

void event_management_thread(void *parameters){
    for(;;){
        event_data_t event;
        os_queue_take(global_eventspace, &event, (system_tick_t)-1, NULL);

        // Go through all the local event spaces, publish to whoever is subscribed to them
        os_mutex_lock(event_management_mutx);
        for(int n = 0; n < num_eventspaces; n++){
            for(int i = 0; i < num_subscribed_events[n]; i++){
                if(subscribed_eventspaces[n][i] == event.event){
                    os_queue_put(local_eventspaces[n], (void*)&event, (system_tick_t)-1, NULL);
                }
            }
        }
        os_mutex_unlock(event_management_mutx);
    }
}

int publish_event(event_type_t event, void *ptr){
    if(!event_management_init){
        return ERR_INT;
    }
    event_data_t data;
    data.event = event;
    data.ptr = ptr;

    if(os_queue_put(global_eventspace, (void*)&data, (system_tick_t)-1, NULL) == 0){
        return ERR_OK;
    }

    return ERR_INT;
}

int subscribe_eventlist(event_type_t *event_list, int num_events, int event_length_max){
    if(!event_management_init){
        return ERR_INT;
    }

    os_mutex_lock(event_management_mutx);

    os_queue_create(&local_eventspaces[num_eventspaces], sizeof(event_data_t), event_length_max, NULL);
    subscribed_eventspaces[num_eventspaces] = (event_type_t*)malloc(sizeof(event_type_t) * num_events);

    // Add to list of events
    for(int n = 0; n < num_events; n++){
        subscribed_eventspaces[num_eventspaces][n] = event_list[n];
    }
    num_subscribed_events[num_eventspaces] = num_events;
    int ret = num_eventspaces;
    num_eventspaces++;
    os_mutex_unlock(event_management_mutx);
    return ret;
}

bool available_events(int eventspace){
    if(!event_management_init){
        return false;
    }

    event_data_t data;
    if(os_queue_peek(local_eventspaces[eventspace], &data, 0, NULL) == 0){
        return true;
    }

    return false;
}

event_data_t consume_event(int eventspace){
    event_data_t event;
    memset(&event, 0, sizeof(event_data_t));

    if(!event_management_init){
        return event;
    }

    os_queue_take(local_eventspaces[eventspace], &event, (system_tick_t)-1, NULL);

    return event;
}