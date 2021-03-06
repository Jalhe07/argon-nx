/*  
 * Copyright (c) 2018 Guillem96
 *
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "menu/gui/gui_menu_entry.h"
#include "mem/heap.h"
#include "gfx/gfx.h"
#include "utils/fs_utils.h"
#include <string.h>

#define DEFAULT_LOGO "argon/logos/default.bmp"

/* Creates a menu entry */
gui_menu_entry_t *gui_create_menu_entry(const char *text, 
                                        u8* bitmap, 
                                        u32 x, u32 y, 
                                        u32 width, u32 height, 
                                        int (*handler)(void *), void *param)
{
    gui_menu_entry_t *menu_entry = (gui_menu_entry_t *)malloc(sizeof(gui_menu_entry_t));
	strcpy(menu_entry->text, text);
    
    if (bitmap != NULL)
	    menu_entry->bitmap = bitmap;
    else
        menu_entry->bitmap = sd_file_read(DEFAULT_LOGO);

    menu_entry->x = x;
    menu_entry->y = y;
    menu_entry->width = width;
    menu_entry->height = height;
	menu_entry->handler = handler;
	menu_entry->param = param;
	return menu_entry;
}

/* Renders a gfx menu entry */
void gui_menu_render_entry(gui_menu_entry_t* entry, bool selected, bool render_bmp)
{
    if (render_bmp)
        gfx_render_bmp_arg_bitmap(&g_gfx_ctxt, entry->bitmap, 
                                    entry->x, entry->y, 
                                    entry->width, entry->height);

    u32 prevColor = g_gfx_con.fgcol;

    g_gfx_con.scale = 2;
    gfx_con_setpos(&g_gfx_con, entry->x, entry->y + entry->height + 20);
    
    if (selected)
        gfx_printf(&g_gfx_con, "%k%s%k", 0xFF1971FF, entry->text, prevColor);
    else
        gfx_printf(&g_gfx_con, "%s", entry->text);
}

void gui_menu_entry_destroy(gui_menu_entry_t* entry)
{
    free(entry->bitmap);
    free(entry->text);
    free(entry->param);
    free(entry);
}