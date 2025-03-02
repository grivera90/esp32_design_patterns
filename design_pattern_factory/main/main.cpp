#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "gpio_expander/gpio_expander_drv_factory.h"
#include "scale_class/scale.h"

#include "gpio_expander/gpio_expander_drv_factory.h"
#include "gpio_expander/gpio_expander.h"

extern "C" void app_main(void)
{
    
    scale primary_load_cell(adc_chip::HX710A);
    gpio_expander gpio_exapnder_keyboard(gpio_expander_chip::TCA9554, 0x27);
    
    while (true) 
    {
		double weight = primary_load_cell.get_weight();
        printf("Hello from app_main!\n");
        printf("peso: %f\n", weight);
        sleep(1);
    }
}
