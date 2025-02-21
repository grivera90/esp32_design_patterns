#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "scale.h"

extern "C" void app_main(void)
{
    
    scale primary_load_cell(adc_chip::HX710A);
    
    while (true) 
    {
		double weight = primary_load_cell.get_weight();
        printf("Hello from app_main!\n");
        printf("peso: %f\n", weight);
        sleep(1);
    }
}
