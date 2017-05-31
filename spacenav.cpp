/** 
 * @author Can Erdogan
 * @date 2017-05-31
 * @brief Connects to spacenav using the spacenav library and outputs motion and button information
 */

#include <stdio.h>
#include <stdlib.h>
#include <spnav.h>
#include <unistd.h>

int main(void) {

	spnav_event sev;
	if(spnav_open()==-1) {
	  	fprintf(stderr, "failed to connect to the space navigator daemon\n");
		return 1;
	}

	while(true) {
		spnav_poll_event(&sev);
		if(sev.type == SPNAV_EVENT_MOTION) {
			printf("got motion event: t(%d, %d, %d) ", sev.motion.x, sev.motion.y, sev.motion.z);
			printf("r(%d, %d, %d)\n", sev.motion.rx, sev.motion.ry, sev.motion.rz);
		} else if(sev.type == SPNAV_EVENT_BUTTON) {
			printf("got button %s event b(%d)\n", sev.button.press ? "press" : "release", sev.button.bnum);
		} else printf("nothing!\n");
	}

	spnav_close();
	return 0;
}
