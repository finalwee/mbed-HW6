#include "mbed.h"
#include <cstdio>


InterruptIn button(USER_BUTTON);
DigitalOut led(LED1);
Timeout  press_threhold;
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void button_release_detecting()
{
    printf("disable\n");
    button.enable_irq();
}



void button_pressed()
{
    button.disable_irq();
    
    //press_threhold.attach(&button_release_detecting, 1.0);
    queue.call(button_release_detecting);
    //queue.call_in(1000, button_release_detecting);
}

void button_released()
{
    led = !led;
}


// main() runs in its own thread in the OS
int main()
{
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    button.fall(&button_pressed);
    button.rise(&button_released);
    while (1);
}

