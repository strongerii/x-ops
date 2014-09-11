#include <stdio.h>
#include <stdlib.h>
#include "ev_mgr.h"


 void s_in (EV_P_ ev_io *w, int revents)
{
	printf ("s_in ready\n");

	ev_io_stop (EV_A_ w);
	ev_break (EV_A_ EVBREAK_ALL);
}

 void time_out(EV_P_ ev_io *w, int revents)
{
	printf("hello! Time is over!\n");	
	
	ev_break (EV_A_ EVBREAK_ONE);
}

 void clock_cb(EV_P_ ev_io *w, int revents)
{
	printf("hello! now 3 secs!\n");	
	
}
 void signal_cb(EV_P_ ev_io *w, int revents)
{
	printf("hello! capture signal!\n"); 
}

int main()
{
	struct ev_loop *loop = EV_DEFAULT;
	ev_io *watcher = NULL;
	ev_timer timer;
	ev_periodic clock;
	ev_signal signal;
	
	init_ev_items();
	watcher = get_valid_ev_item();
	if(NULL == loop || NULL == watcher){
		printf("libev init failed!\n");
		return -1;
	}
	printf("GET %d\n",watcher->fd);

	ev_io_init(watcher,s_in,0,EV_READ);										//ev_io
	ev_io_start(loop,watcher);

	ev_timer_init(&timer,time_out,3,0);										//ev_timer
	ev_timer_start(loop,&timer);

	ev_periodic_init(&clock,clock_cb,fmod (ev_now (loop), 3600.),3 , 0);	//ev_periodic
	ev_periodic_start(loop,&clock);

	ev_signal_init(&signal,signal_cb,SIGINT);								//ev_signal
	ev_signal_start(loop,&signal);
	
	ev_run(loop,0);

	printf("Program is end\n");
	
	exit(0);
}
