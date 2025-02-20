# Lab 3 FreeRTOS

## On debugging

When C code is compiled with debug option, then compiler adds symbol names (variables, functions etc) and source code line information to the output executable file. When debugging with GDB single step (step-over) the debugger finds next source code line to be executed and sets a breakpoint on corresponding machine instruction address.

Multitasking messes this up. Debugger cannot know when interrupts will occur, so it cannot follow context switches to other tasks.

Example: You single step though the blink example. The code has vTaskDelay() call, that will switch to idle task until next timer tick. That will be stepped over as any program line, but there is no practical way of stepping into idle task, not with step-into or any other means. To see when idle task is active, you need to set a breakpoint into that task code. So to get an idea how tasks are sharing cpu time, you must set breakpoints to multiple tasks and see which breakpoint triggers first.

On ESP32-C6 you have 4 hardware breakpoints available, which might limit your debugging options.

## Assignment

Create multitasked program where 3 independent tasks each blinks its own LED. For project base use blink example. For creating new tasks, see generic_gpio example and [FreeRTOS documentation]([xTaskCreate - FreeRTOS™](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/01-xTaskCreate))

- red LED: 3Hz
- yellow LED: 7Hz
- green LED: 11Hz
  Translate blinking frequency to task delays; round to nearest FreeRTOS timer tick value (tick is 10ms by default, but you might explore adjusting system tick in project settings). Frequency = 1/(LED_on_time + LED_off_time). Blinking duty cycle does not need to be 50/50, so the two on/off times can be different.
