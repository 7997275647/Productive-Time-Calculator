#include "main.h"


/******************************************state handlers prototypes*******************************************/
event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const*const e);
event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t const*const e);
event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t const*const e);
event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t const*const e);
event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t const*const e);



/*****************************************Helper functions prototypes*****************************************/
void disp_time(int x);
void disp_clr(void);
void disp_msg(String s);
void do_beep(void);


/**Init Function**/

void protimer_init(protimer_t *mobj){
    mobj->active_state =IDLE;
    mobj->pro_time = 0;

}

event_status_t protimer_state_machine(protimer_t * mobj, event_t *e){
    switch (mobj->active_state){
        case IDLE:{
            return protimer_state_handler_IDLE(mobj,e);
            
        }
        case TIME_SET:{
            return protimer_state_handler_TIME_SET(mobj,e);
            
        }
        case STAT:{
            return protimer_state_handler_STAT(mobj,e);
            
        }
        case COUNTDOWN:{
            return protimer_state_handler_COUNTDOWN(mobj,e);
            
        }
        case PAUSE:{
            return protimer_state_handler_PAUSE(mobj,e);
            
        }
        

    }
    return EVENT_IGNORED;
}
    event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const*const e){
        switch (e->sig){
            case ENTRY:{
                mobj->current_time = 0;
                mobj->elapsed_time = 0;
                disp_time(0);
                disp_msg("Set Time");
                return EVENT_HANDLED;

            }
            case EXIT:{
                disp_clr();
                return EVENT_HANDLED;

            }
            case TIME_TICK:{
                if(((protimer_tick_event_t * )e)->ss ==5){
                    do_beep();
                    return EVENT_HANDLED;
                }
                return EVENT_IGNORED;

            }
            case START_PAUSE:{
                mobj->active_state = STAT;
                return EVENT_TRANSITION;

            }
            case INC_TIME:{
                mobj->current_time +=60;
                mobj->active_state = TIME_SET;
                return EVENT_TRANSITION;

            }
            
        }

        return EVENT_IGNORED;

    }




    event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t const*const e){
        switch (e->sig){
            case ENTRY:{
                disp_time(mobj->current_time);
                return EVENT_HANDLED;
            }
          
            case TIME_TICK:{

            }
            case START_PAUSE:{
                if(mobj->current_time >= 60){
                    mobj->active_state = COUNTDOWN;
                    return EVENT_TRANSITION; 
                }

            }
            case ABRT:{
                mobj->active_state = IDLE;
                return EVENT_TRANSITION;

            }
            case INC_TIME:{
                mobj->current_time +=60;
                disp_time(mobj->current_time);
                return EVENT_HANDLED;

            }
            case DEC_TIME:{
                if(mobj->current_time >= 60){
                    mobj->current_time -=60;
                    disp_time(mobj->current_time);
                    return EVENT_HANDLED;
                }
                return EVENT_IGNORED;
                
            }
        }
        return EVENT_IGNORED;


    }




    event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t const*const e){
        switch (e->sig){
            case ENTRY:{
                disp_time(mobj->pro_time);
                disp_msg("Productive Time");
                return EVENT_HANDLED;

            }
            case EXIT:{
                disp_clr();
                return EVENT_HANDLED;

            }
            case TIME_TICK:{
                if(((protimer_tick_event_t *)e)->ss == 10){
                    mobj->active_state = IDLE;
                    return EVENT_TRANSITION;
                }

            }
            
        }
        return EVENT_IGNORED;

    }



    event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t const*const e){
        switch (e->sig){
            
            case EXIT:{
                mobj->pro_time += mobj->elapsed_time;
                mobj->elapsed_time = 0;
                return EVENT_HANDLED;
            }
            case TIME_TICK:{
                if(((protimer_tick_event_t *)e)->ss == 10){
                    --mobj->current_time;
                    ++mobj->elapsed_time;
                    disp_time(mobj->current_time);
                    if (!mobj->current_time){
                        mobj->active_state = IDLE;
                        return EVENT_TRANSITION;
                        
                    }
                    return EVENT_HANDLED;

                }

            }
            case START_PAUSE:{
                mobj->active_state = PAUSE;
                return EVENT_TRANSITION;

            }
            case ABRT:{
                mobj->active_state = IDLE;
                return EVENT_TRANSITION;


            }
           
        }
        return EVENT_IGNORED;


    }




    event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t const*const e){
        switch (e->sig){
            case ENTRY:{
                disp_msg("Paused");
                return EVENT_HANDLED;
            }
            case EXIT:{
                disp_clr();
                return EVENT_HANDLED;

            }
           
            case START_PAUSE:{
                mobj->active_state = COUNTDOWN;
                return EVENT_TRANSITION;

            }
            case ABRT:{
                mobj->active_state = IDLE;
                return EVENT_TRANSITION;

            }
            case INC_TIME:{
                mobj->current_time+=60;
                return EVENT_TRANSITION;

            }
            case DEC_TIME:{
                if (mobj->current_time>= 60){
                    mobj->current_time -= 60;
                    return EVENT_TRANSITION;
                }
                return EVENT_IGNORED;
                
            }
        }
        return EVENT_IGNORED;


    }




    /**************************************Helper functions***************************************/

    void disp_time(int x){

    }

    void do_beep(void){

    }

    void disp_msg(String s){

    }

    void disp_clr(void){

    }






