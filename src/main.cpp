
#include "main.h"
// put function declarations here:
int myFunction(int, int);
static protimer_t protimer;
void setup() {
  // put your setup code here, to run once:
  protimer_init(&protimer);
}

void loop() {
  // put your main code here, to run repeatedly:

  //1. Read the button pad status

  //2. Make  an Event

  //3. Send the event to event dispatcher
  protimer_event_dispatcher();
}

static event_status_t protimer_event_dispatcher(protimer_t * mobj, event_t *e){
  event_status_t status;
  protimer_state_t source,target;
  source = mobj->active_state;

  status = protimer_state_machine(mobj,e);
  if (status == EVENT_TRANSITION){
    target = mobj->active_state;
    event_t ee;
    //1. run the exit action of the source state
    ee.sig = EXIT;
    mobj->active_state = source;
    protimer_state_machine(mobj,&ee);

    //2. run the entry action of the target state

    ee.sig = ENTRY;
    mobj->active_state = target;
    protimer_state_machine(mobj,&ee);



  }
}

