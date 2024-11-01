#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#define PIN_BUTTON1 2
#define PIN_BUTTON2 3
#define PIN_BUTTON3 4

// Pins of LCD
#define PIN_LCD_RS 5
#define PIN_LCD_RW 6
#define PIN_LCD_EN 7
#define PIN_LCD_D4 8
#define PIN_LCD_D5 9
#define PIN_LCD_D6 10
#define PIN_LCD_D7 11

//button pad values
#define BTN_PAD_INC_TIME 4
#define BTN_PAD_DEC_TIME 2
#define BTN_PAD_ABRT 6
#define BTN_PAD_START_PAUSE 1

#define PIN_BUZZER 12


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


typedef enum{
    NOT_PRESSED,
    PRESSED,
    BOUNCE
}button_state_t;


void protimer_init(protimer_t *mobj);

event_status_t protimer_state_machine(protimer_t * mobj, event_t *e);



#endif