#include <main.h>

#ifdef __cplusplus
extern "C" {
#endif

// Global variables for interrupt handler (must match stm32f7xx_it.c declarations)
extern volatile int button_flag;
extern volatile int COMMAND;
extern volatile int current_mode;
extern volatile uint8_t button_press_count;
extern volatile uint32_t button_press_time;

#ifdef __cplusplus
}
#endif

int application();
