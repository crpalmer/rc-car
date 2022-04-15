#include <stdio.h>
#include <stdlib.h>
#include "gp-input.h"
#include "gp-output.h"
#include "l298n.h"
#include "nes.h"

#define F_event "/dev/input/by-id/usb-0079_Controller-event-joystick"

int
main(int argc, char **argv)
{
    FILE *f;
    nes_event_t e;

    gpioInitialise();

    motor_t *m = new L298N(new GPOutput(18), new GPOutput(15), new GPOutput(14));

    if ((f = fopen(F_event, "r")) == NULL) {
	perror(F_event);
	exit(0);
    }

    while (nes_read(&e, f) >= 0) {
	if (e.button != NES_UP_DOWN) {
	} else if (e.dir > 0) {
	    m->direction(1);
	    m->speed(1);
	} else if (e.dir < 0) {
	    m->direction(0);
	    m->speed(1);
	} else {
	    m->speed(0);
	}
    }
}

