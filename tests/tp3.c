#include <stdlib.h>

#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"

int ei_main(int argc, char** argv){
    ei_surface_t main_window = NULL;
    ei_size_t		 main_window_size;
    ei_event_t event;

    ei_point_t start, end;
    ei_color_t c;

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window_size.width	= 640;
    main_window_size.height	= 480;
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    c.red = 0xff, c.green = 0xff, c.blue = 0xff, c.alpha = 0xff;
    start.x = 320, start.y = 240;
    hw_surface_lock(main_window);
    ei_fill(main_window, &c, EI_FALSE);
    c.red = 0x00, c.green = 0x00, c.blue = 0x00, c.alpha = 0x00;
    end.x = 270, end.y = 340;
    ei_draw_line(main_window, start, end, c);
    end.x = 220, end.y = 340;
    ei_draw_line(main_window, start, end, c);
    end.x = 220, end.y = 290;
    ei_draw_line(main_window, start, end, c);
    end.x = 220, end.y = 240;
    ei_draw_line(main_window, start, end, c);
    end.x = 220, end.y = 190;
    ei_draw_line(main_window, start, end, c);
    end.x = 220, end.y = 140;
    ei_draw_line(main_window, start, end, c);
    end.x = 270, end.y = 140;
    ei_draw_line(main_window, start, end, c);
    end.x = 320, end.y = 140;
    ei_draw_line(main_window, start, end, c);
    end.x = 370, end.y = 140;
    ei_draw_line(main_window, start, end, c);
    end.x = 420, end.y = 140;
    ei_draw_line(main_window, start, end, c);
    end.x = 420, end.y = 190;
    ei_draw_line(main_window, start, end, c);
    end.x = 420, end.y = 240;
    ei_draw_line(main_window, start, end, c);
    end.x = 420, end.y = 290;
    ei_draw_line(main_window, start, end, c);
    end.x = 420, end.y = 340;
    ei_draw_line(main_window, start, end, c);
    end.x = 370, end.y = 340;
    ei_draw_line(main_window, start, end, c);
    hw_surface_unlock(main_window);

/*	ei_linked_point_t* first_point;
	ei_linked_point_t* nd_point;
	ei_linked_point_t* rd_point;
	first_point->point.x=50;
	first_point->point.y=100;	
	nd_point->point.x=150;
	nd_point->point.y=100;
	rd_point->point.x=150;
	rd_point->point.y=180;
	first_point->next=nd_point;
	nd_point->next=rd_point;
	rd_point->next=NULL;

	ei_draw_polyline(main_window,first_point,c);*/

    hw_surface_update_rects(NULL);

    // Wait for a key press.
    event.type = ei_ev_none;
    while (event.type != ei_ev_keydown) {
        hw_event_wait_next(&event);
    }

    // Free hardware resources.
    hw_quit();

    // Terminate program with no error code.
    return 0;
}
