#include <stdlib.h>
#include <stdio.h>

#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"



int ei_main(int argc, char* argv[])
{
    ei_surface_t main_window = NULL;
    ei_size_t		 main_window_size;
    ei_event_t event;
    ei_color_t red				= { 0xff, 0x00, 0x00, 0xff };
    ei_color_t blue		= { 0x00, 0x00, 0xff, 0xff };
    ei_color_t transp_green		= { 0x00, 0xff, 0x00, 0x88 };

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window_size.width	= 640;
    main_window_size.height	= 480;
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    //lock main window
    hw_surface_lock(main_window);

    ei_point_t pos;
    pos.x = 10;
    pos.y = 20;

    ei_color_t col = hw_get_pixel(main_window, pos);
    printf("%d %d %d %d \n", col.red, col.green, col.blue, col.alpha );
    hw_put_pixel(main_window, pos, blue);
    col = hw_get_pixel(main_window, pos);
    printf("%d %d %d %d \n", col.red, col.green, col.blue, col.alpha );




    // Fill the window in red
    ei_fill(main_window, &red, EI_FALSE);

    //read and display an image
    if (argc ==2) {
        ei_surface_t image = hw_image_load(argv[1]);

        pos.x = 50;
        pos.y = 100;
        //lock image
        hw_surface_lock(image);

        ei_copy_surface(main_window, image, &pos, EI_FALSE);

        //unlock image
        hw_surface_unlock(image);
        hw_surface_free(image);
    }
    else
        fprintf(stderr, "No image loaded\n");

    //create a rectangular surface
    ei_size_t surface_size;
    surface_size.width = 300;
    surface_size.height = 300;

    ei_surface_t surface = hw_surface_create(main_window, &surface_size );

    hw_surface_lock(surface);
    ei_fill(surface, &transp_green, EI_FALSE);



    //Draw and display text
    pos.x = 10;
    pos.y = 10;
    ei_draw_text(surface, &pos, "Test text", NULL, &ei_font_default_color );

     //display the rectangular surface
    pos.x = 60;
    pos.y = 100;
    ei_copy_surface(main_window, surface, &pos, EI_TRUE);
    hw_surface_unlock(surface);
    hw_surface_free(surface);


    //unlock main window
    hw_surface_unlock(main_window);

    //display
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
