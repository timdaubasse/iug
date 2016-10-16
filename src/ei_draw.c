#include "ei_draw.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



static inline ei_color_t alpha_blend(const ei_color_t in_pixel, const ei_color_t dst_pixel)
{
    ei_color_t blended;
    float alpha = ((float)in_pixel.alpha) / 255.f;
    blended.red   = (1.f -  alpha) * dst_pixel.red   + alpha * in_pixel.red;
    blended.green = (1.f -  alpha) * dst_pixel.green + alpha * in_pixel.green;
    blended.blue  = (1.f -  alpha) * dst_pixel.blue  + alpha * in_pixel.blue;
    blended.alpha = 255;
    return blended;
}


void ei_draw_line(ei_surface_t surface, const ei_point_t start,
                  const ei_point_t end, const ei_color_t color) {
    int e, m;
    ei_point_t p, sp, ep;
    if(start.x > end.x){
        sp.x = end.x, sp.y = end.y;
        ep.x = start.x, ep.y = start.y;
    }
    else{
        sp.x = start.x, sp.y = start.y;
        ep.x = end.x, ep.y = end.y;
    }

    p.x = sp.x, p.y = sp.y;
    if(ep.x - sp.x >= (ep.y - sp.y > 0 ? ep.y - sp.y : sp.y - ep.y)){//si coeff <= 1
        printf("yes\n");//TODO DELETEME
        e = sp.x - ep.x;
        while(p.x <= ep.x){
            hw_put_pixel(surface, p, color);
            p.x++;
            if(ep.y >= sp.y){
                e += 2 * (ep.y - sp.y);
                if(e >= 0){
                    p.y++;
                    e -= 2 * (ep.x - sp.x);
                }
            }
            else{
                e -= 2 * (ep.y - sp.y);
                if(e >= 0){
                    p.y--;
                    e -= 2 * (ep.x - sp.x);
                }
            }
        }
    }
    else{
        printf("no  %d  %d\n", ep.x, ep.y);//TODO DELETEME
        e = sp.y - ep.y;
        while(p.x <= ep.x){//TODO changeme
            printf("SWEG %d  %d\n", p.x, p.y);
            hw_put_pixel(surface, p, color);
            if(ep.y >= sp.y){
                p.y++;
                e += 2 * (ep.x - sp.x);
                if(e >= 0){
                    p.x++;
                    e -= 2 * (ep.y - sp.y);
                }
            }
            else{
                p.y--;
                e += 2 * (ep.x - sp.x);
                if(e >= 0){
                    p.x++;
                    e += 2 * (ep.y - sp.y);
                }
            }
        }
    }
 }



int ei_draw_polyline(ei_surface_t surface,
                     const ei_linked_point_t* first_point,
                     const ei_color_t color)
{

    if (first_point == NULL) {
        fprintf(stderr, " no points for the polyline\n;");
        return 1;
    }

    /* TO BE COMPLETED */

    return 0;
}


void ei_draw_text(ei_surface_t surface, const ei_point_t* where,
                  const char* text, const ei_font_t font,
                  const ei_color_t* color)
{
    ei_size_t text_size;
    ei_surface_t s_text;
    ei_font_t default_font;

    if (font == NULL) {
        default_font = hw_text_font_create(ei_default_font_filename, ei_font_default_size);
        s_text = hw_text_create_surface(text, default_font, color);
        hw_text_font_free(default_font);
    } else {
        s_text = hw_text_create_surface(text, font, color);
    }


    hw_surface_lock(s_text);
    ei_copy_surface(surface, s_text, where, EI_TRUE);
    hw_surface_unlock(s_text);

    hw_surface_free(s_text);
}


void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_bool_t use_alpha)
{
    ei_point_t pos;
    ei_color_t c = color == NULL ? ei_font_default_color : *color;
    ei_color_t p;
    ei_size_t size = hw_surface_get_size(surface);
    for (pos.x = 0; pos.x < size.width; pos.x++) {
        for (pos.y = 0; pos.y < size.height; pos.y++) {
            p = hw_get_pixel(surface, pos);
            if (use_alpha) {
                hw_put_pixel(surface, pos, alpha_blend(c, p));
            } else {
                hw_put_pixel(surface, pos, c);
            }
        }
    }
}


int ei_copy_surface(ei_surface_t destination, const ei_surface_t source,
                    const ei_point_t *top_left, const ei_bool_t use_alpha)
{
    ei_point_t pos, new_pos;

    ei_size_t source_size = hw_surface_get_size(source);

    ei_size_t dst_size = hw_surface_get_size(destination);

    ei_color_t in_pixel, out_pixel;


    for (pos.x = 0; pos.x < source_size.width; pos.x++) {
        for (pos.y = 0; pos.y < source_size.height; pos.y++) {
            in_pixel = hw_get_pixel(source, pos);

            new_pos.x = top_left->x + pos.x;
            new_pos.y = top_left->y + pos.y;

            if (new_pos.x>=0 && new_pos.x < dst_size.width
                && new_pos.y>=0 &&  new_pos.y < dst_size.height) {
                if (use_alpha) {
                    out_pixel = hw_get_pixel(destination, new_pos);
                    hw_put_pixel(destination, new_pos, alpha_blend(in_pixel, out_pixel));
                } else {
                    hw_put_pixel(destination, new_pos, in_pixel);
                }
            }
        }
    }
    return 0;
}
