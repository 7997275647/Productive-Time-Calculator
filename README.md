# Productive-Time-Calculator

**Author:** Sandeep Reddy Modugu 
**Version:** 1  
**Date:** 

## Overview

This project is an embedded system that calculates and displays "productive time" using an Arduino Uno and a state machine designed with UML. The system allows users to set a timer, increment or decrement time, pause, and abort the countdown. It keeps track of productive time, which can be useful for timing work sessions or similar activities.

## State Machine Design

The system uses a UML-based state machine with the following states:

- **IDLE**: Initial state where timers are reset, and "Set Time" is displayed.
- **TIME_SET**: Allows the user to increment or decrement the countdown time in 60-second intervals.
- **COUNTDOWN**: Starts counting down from the set time, tracking productive time.
- **PAUSE**: Pauses the countdown timer.
- **STAT**: Displays the total productive time at the end.

Refer to the UML state diagram for detailed state transitions.

## Components

- **Arduino Uno**: Main controller to handle the state machine logic.
- **Led Display**: Shows messages like "Set Time", "Paused", and remaining time.
- **Buzzer**: Emits a beep on specific events for audio feedback.

## Setup Instructions

1. **Hardware Setup**:
   - Connect a display module to the Arduino for time and state messages.
   - Connect a buzzer to the Arduino for audio alerts.

2. **Software Setup**:
   - Download and install the VS code (add platform IO extention).
   - Open the project code file and upload it to the Arduino Uno.

3. **Running the Project**:
   - Power on the Arduino Uno.
   - Use buttons connected to Arduino inputs to trigger events like `START_PAUSE`, `INC_TIME`, and `DEC_TIME`.
   - Observe time updates and messages on the display and listen for the beep on specific events.

## Events and Transitions

| Event         | Description                                    |
|---------------|------------------------------------------------|
| `TIME_TICK`   | Timer tick event that updates countdown time.  |
| `START_PAUSE` | Starts or pauses the countdown timer.          |
| `ABRT`        | Aborts current operation and resets to **IDLE**.|
| `INC_TIME`    | Increases the countdown time by 60 seconds.    |
| `DEC_TIME`    | Decreases the countdown time by 60 seconds.    |



This document outlines the software requirements for the Productive Time calculator system. 

For any questions or further information, please contact modugusandy@gmail.com.



![State Machine Diagram](include/Protimer_State_Machine.png).

