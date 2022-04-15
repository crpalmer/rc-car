#include <stdio.h>
#include <stdlib.h>
#include "gp-input.h"
#include "gp-output.h"
#include "l298n.h"

int
main(int argc, char **argv)
{
    gpioInitialise();

    GPInput *b1 = new GPInput(23);
    b1->set_pullup_up();
    GPInput *b2 = new GPInput(24);
    b2->set_pullup_up();
    motor_t *m = new L298N(new GPOutput(18), new GPOutput(15), new GPOutput(14));

    while (1) {
	if (b1->get_with_debounce()) {
	    m->direction(1);
	    m->speed(1);
	} else if (b2->get_with_debounce()) {
	    m->direction(0);
	    m->speed(1);
	} else {
	    m->speed(0);
	}
    }
}

