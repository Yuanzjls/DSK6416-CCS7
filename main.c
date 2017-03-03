#include "dsk6416.h"
#include "dsk6416_led.h"
#include "dsk6416_dip.h"


/*
 *  main() - Main code routine, initializes BSL and runs LED application
 */

void main()
{
    /* Initialize the board support library, must be first BSL call */
    DSK6416_init();

    /* Initialize the LED and DIP switch modules of the BSL */
    DSK6416_LED_init();
    DSK6416_DIP_init();

    while(1)
    {
        /* Toggle LED #0 */
        DSK6416_LED_toggle(0);

        /* Check DIP switch #3 and light LED #3 accordingly, 0 = switch pressed */
        if (DSK6416_DIP_get(3) == 0)
            /* Switch pressed, turn LED #3 on */
            DSK6416_LED_on(3);
        else
            /* Switch not pressed, turn LED #3 off */
            DSK6416_LED_off(3);

        /* Spin in a software delay loop for about 200ms */
       DSK6416_waitusec(200000);
    }
}
