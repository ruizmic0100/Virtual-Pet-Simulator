#include <stdio.h>
#include "lib/pico_multicore/include/pico/multicore.h"
#include "lib/pico_stdlib/include/pico/stdlib.h"
#include "lib/hardware_irq/include/hardware/irq.h"

#include "lib/LCD/LCD_1in8.h"
#include "lib/Config/Debug.h"
#include "lib/GUI/GUI_Paint.h"
#include "lib/GUI/ImageData.h"
#include "lib/Fonts/fonts.h"

#include "include/menus.h"
#include "include/character_config.h"
#include "include/displaystate.h"


//TODO(MSR): FIX loops not being actually RTOS.
//TODO(MST): Merge conflict will exist with home rig from now on.

// Multicore parameter needed.
#define FLAG_VALUE 123

// Function Declaration
int main(void);
int loop_5ms();
int loop_20ms();
int loop_200us();
int loop_1s();
void core1_entry();
int loop_complete();


bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int loop_complete() {
	return 1;	
}

// Core 1 interrupt handler.
void core1_interrupt_handler() {

    // LCD Init
    LCD_1IN8_Init(HORIZONTAL);
    LCD_1IN8_Clear(WHITE);
    
    // Set up Image.
    UDOUBLE Imagesize = LCD_1IN8_HEIGHT*LCD_1IN8_WIDTH*2;
    UWORD *BlackImage;
    BlackImage = (UWORD *)malloc(Imagesize);

    // Create a new image cache named BlackImage and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN8.WIDTH,LCD_1IN8.HEIGHT, 90, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);

    while(1) {
        
        // Apply the image in the display loop.
        loop_20ms(BlackImage);

        // Clear the screen.
        Paint_Clear(WHITE);

        // Check what Image is necessary to be displayed.
        if (desired_display == character_menu) {
            characterMenuDisplay();
        } else if (desired_display == stats_menu) {
            statsMenuDisplay();
        } else if (desired_display == inventory_menu) {
            printf("inventory if");
        } else {
            printf("no valid selection");
        }
    }

    // Receiver function whenever buffer is valid.
    if (multicore_fifo_rvalid()) { 
    }
    
    multicore_fifo_clear_irq(); // Clear Interrupt.

}

// Core 1 Main code.
void core1_entry() {

    // Configure Core 1 Interrupt.
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);

    irq_set_enabled(SIO_IRQ_PROC1, true);


    // Infinite While loop that never terminates to wait for interrupt.
    while(1) {
       tight_loop_contents(); 
    }
}


// Runs other loops.
int main(void)
{
    // Delay Main to let other stuff to properly setup.
    DEV_Delay_ms(100);
    printf("LCD_1in8_main Demo\r\n");
    DEV_Module_Init();

    // Launches core1_entry on seconds core.
    multicore_launch_core1(core1_entry);
    
    // Debug Led Setup.
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    
    // Initialize Display Loop();
    uint16_t start = 1;
    multicore_fifo_push_blocking(start);

    // Wait time to initialize Everything.
    DEV_Delay_ms(200);

    // Begin here for game.
    initializeWarriorStats();

    // Menu Controls prompt.
    printf("Controls for Menu (s = stats, i = inventory, c = character): \n");


    // Main Loop to refresh the screen.
    while(1) {
        loop_200us();
        loop_5ms();
		loop_20ms();
        loop_1s();
    }

}


// Fast Auxillary Loop.
int loop_200us() {
	//loop_complete();
    DEV_Delay_us(200);
}

// Status Loop for periphals.
int loop_5ms() {

    setDisplayState();
	//loop_complete();
    DEV_Delay_ms(5);
}

// Display loop running at 16ms(60hz).
int loop_20ms() {
    
    DEV_Delay_ms(20);
}

// 1 seconds loop for game engine.
int loop_1s() {
	//loop_complete();
    DEV_Delay_ms(1000);
}
