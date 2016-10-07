#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "ei_types.h"
#include "ei_draw.h"
#include "ei_main.h"
#include "hw_interface.h"
TEST_CASE("fill_copy_window", "[unit]")
{
    ei_surface_t main_window = NULL;
    ei_size_t main_window_size, query_size;
    ei_color_t red = {0xff, 0x00, 0x00, 0xff}, query_color;
    ei_point_t origin = {0, 0};
    main_window_size.width = 640;
    main_window_size.height = 480;
    ei_point_t point, pos;
    ei_size_t surface_size ={300,300};


    main_window = hw_create_window(&main_window_size, EI_FALSE);

    SECTION( "fill_red" ) {
        hw_surface_lock(main_window);
        ei_fill(main_window, &red, EI_FALSE);
        for (int x=0; x<main_window_size.width; x++)
            for (int y=0; y<main_window_size.height; y++) {
                point.x = x;
                point.y = y;
                query_color = hw_get_pixel(main_window, point);
                REQUIRE( query_color.red == red.red );
                REQUIRE( query_color.green == red.green );
                REQUIRE( query_color.blue == red.blue );
            }
        hw_surface_unlock(main_window);
    }

    ei_surface_t surface = hw_surface_create(main_window, &surface_size );
    SECTION( "fill_default" ) {


        hw_surface_lock(surface);
        ei_fill(surface, NULL, EI_FALSE);

        for (int x=0; x<surface_size.width; x++)
            for (int y=0; y<surface_size.height; y++) {
                point.x = x;
                point.y = y;
                query_color = hw_get_pixel(surface, point);
                REQUIRE( query_color.red == ei_font_default_color.red );
                REQUIRE( query_color.green == ei_font_default_color.green );
                REQUIRE( query_color.blue == ei_font_default_color.blue );
            }

        hw_surface_unlock(surface);
    }
   SECTION("copy_surface", "[unit]")
    {
        hw_surface_lock(main_window);

        hw_surface_lock(surface);

        pos.x = 60;
        pos.y = 100;
        ei_copy_surface(main_window, surface, &pos, EI_FALSE);


        for (int x=0; x<surface_size.width; x++)
            for (int y=0; y<surface_size.height; y++) {
                point.x = x+pos.x;
                point.y = y+pos.y;
                query_color = hw_get_pixel(main_window, point);
                REQUIRE( query_color.red == ei_font_default_color.red );
                REQUIRE( query_color.green == ei_font_default_color.green );
                REQUIRE( query_color.blue == ei_font_default_color.blue );
            }
        hw_surface_unlock(surface);
        hw_surface_free(surface);

        hw_surface_unlock(main_window);

    }

}



int ei_main(int argc, char* argv[])
{
    // Init acces to hardware.
    hw_init();

    int result = Catch::Session().run( argc, argv );

    // Free hardware resources.
    hw_quit();

    return result;
}
