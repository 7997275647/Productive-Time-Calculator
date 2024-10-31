#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

//Signals of protimer state machine
typedef enum{
    TIME_TICK,
    ABRT,
    INC_TIME,
    DEC_TIME,
    START_PAUSE,
    // Internal Activity Signals
    ENTRY,
    EXIT
}protimer_signal_t;

// States of state machine application
typedef enum{
    IDLE,
    STAT,
    TIME_SET,
    COUNTDOWN,
    PAUSE
}protimer_state_t;

// Main application struct
typedef struct{
    uint32_t current_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
}protimer_t;

/*Events*/
/*Generic(super) Event Structure*/
typedef struct{
    uint8_t sig;
}event_t;
/*User Generated Events*/
typedef struct{
    event_t super;
}protimer_user_event_t;

/*Tick Events*/
typedef struct{
    event_t super;
    uint8_t ss;
}protimer_tick_event_t;

typedef enum{
    EVENT_HANDLED,
    EVENT_IGNORED,
    EVENT_TRANSITION
}event_status_t;


void protimer_init(protimer_t *mobj);

event_status_t protimer_state_machine(protimer_t * mobj, event_t *e);



#endif