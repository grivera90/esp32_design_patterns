#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "scale.h"

extern "C" void app_main(void)
{
    
    scale primary_load_cell(adc_chip::HX710A);
    
    while (true) {
        printf("Hello from app_main!\n");
        sleep(1);
    }
}
