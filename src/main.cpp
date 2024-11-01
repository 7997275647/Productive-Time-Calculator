
#include "main.h"
#include "Lcd.h"

static uint8_t debounce_button_pad_value(uint8_t button_pad_value);
static void protimer_event_dispatcher(protimer_t * mobj, event_t *e);
static void display_init();
// put function declarations here:
int myFunction(int, int);
static protimer_t protimer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display_init();
  Serial.println("Productive timer application");
  Serial.println("============================");
  pinMode(PIN_BUTTON1, INPUT);
  pinMode(PIN_BUTTON2, INPUT);
  pinMode(PIN_BUTTON3, INPUT);
  protimer_init(&protimer);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t b1,b2,b3,button_pad_value;
  protimer_user_event_t ue;
  static uint32_t current_time = millis();
  protimer_tick_event_t te = {.ss=0}; 

  b1 = digitalRead(PIN_BUTTON1);
  b2 = digitalRead(PIN_BUTTON2);
  b3 = digitalRead(PIN_BUTTON3);
  button_pad_value = (b1<<2)|(b2<<1)|b3;

  // Software Button De bouncing
  button_pad_value = debounce_button_pad_value(button_pad_value);

  //1. Read the button pad status
  //2. Make  an Event
  //3. Send the event to event dispatcher
  if(button_pad_value){
    if (button_pad_value == BTN_PAD_INC_TIME){
      ue.super.sig = INC_TIME;
    }
    else if (button_pad_value == BTN_PAD_DEC_TIME){
      ue.super.sig = DEC_TIME;
    }
    else if (button_pad_value == BTN_PAD_ABRT){
      ue.super.sig = ABRT;
    }
    else if (button_pad_value == BTN_PAD_START_PAUSE){
      ue.super.sig = START_PAUSE;
    }

    protimer_event_dispatcher(&protimer,&ue.super);
  }

  //4. Dispatch the time tick event for every 100 ms
  if (millis()-current_time>=100){
    current_time = millis();
    te.super.sig = TIME_TICK;
    if(++te.ss > 10) te.ss = 1;
    protimer_event_dispatcher(&protimer,&te.super);

  }
   
}

static void protimer_event_dispatcher(protimer_t * mobj, event_t *e){
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

static uint8_t debounce_button_pad_value(uint8_t button_pad_value){
button_state_t button_sw_state;
static uint32_t current_time;
if(button_pad_value){
  switch (button_sw_state){
    case PRESSED:{
      if(!button_pad_value){
        
        button_sw_state = BOUNCE;
        current_time = millis();
      }
      break;

    }
    case BOUNCE:{
      if(millis()- current_time > 50){
        if(button_pad_value){
          button_sw_state= PRESSED;
          return button_pad_value;
        }
        
      }
      else{
        button_sw_state= NOT_PRESSED;
      }
      break;

    }
    case NOT_PRESSED:{
      if(button_pad_value){
        button_sw_state= BOUNCE;
        current_time = millis();
      }

    }
  }
}

  return 0;

}

 static void display_init(){
  lcd_begin(16,2);
  lcd_clear();
  lcd_move_cursor_L_to_R();
  lcd_set_cursor(0,0);
  lcd_no_auto_scroll();
  lcd_cursor_off();

 }

