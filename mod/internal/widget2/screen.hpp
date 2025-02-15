/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Product name: redemption, a FLOSS RDP proxy
 *   Copyright (C) Wallix 2010-2012
 *   Author(s): Christophe Grosjean, Dominique Lafages, Jonathan Poelen,
 *              Meng Tan
 */

#if !defined(REDEMPTION_MOD_INTERNAL_WIDGET2_SCREEN_HPP)
#define REDEMPTION_MOD_INTERNAL_WIDGET2_SCREEN_HPP

#include "font.hpp"
#include "composite.hpp"
#include "tooltip.hpp"
#include "theme.hpp"

#include <typeinfo>

class WidgetScreen : public WidgetParent
{
public:
    Theme theme;
    WidgetTooltip * tooltip;
    Widget2 * current_over;

    CompositeArray composite_array;

    Pointer normal_pointer;
    Pointer edit_pointer;

    Font const & font;

    WidgetScreen(DrawApi& drawable, uint16_t width, uint16_t height, Font const & font,
                 NotifyApi * notifier = NULL, Theme * theme = NULL)
        : WidgetParent(drawable, Rect(0, 0, width, height), *this, notifier)
        , theme(theme ? *theme : Theme())
        , tooltip(NULL)
        , current_over(NULL)
        , normal_pointer(Pointer::POINTER_NORMAL)
        , edit_pointer(Pointer::POINTER_EDIT)
        , font(font)
    {
        this->impl = &composite_array;

        this->tab_flag = IGNORE_TAB;
    }

    virtual ~WidgetScreen()
    {
        if (this->tooltip) {
            delete this->tooltip;
            this->tooltip = NULL;
        }
    }

    void show_tooltip(Widget2 * widget, const char * text, int x, int y, int = 10) {
        if (text == NULL) {
            if (this->tooltip) {
                this->remove_widget(this->tooltip);
                this->refresh(this->tooltip->rect);
                delete this->tooltip;
                this->tooltip = NULL;
            }
        }
        else if (this->tooltip == NULL) {
            this->tooltip = new WidgetTooltip(this->drawable,
                                              x, y,
                                              *this, widget,
                                              text,
                                              this->theme.tooltip.fgcolor,
                                              this->theme.tooltip.bgcolor,
                                              this->theme.tooltip.border_color,
                                              this->font);
            int w = this->tooltip->get_tooltip_cx();
            int h = this->tooltip->get_tooltip_cy();
            int sw = this->rect.cx;
            int posx = ((x + w) > sw)?(sw - w):x;
            int posy = (y > h)?(y - h):0;
            this->tooltip->set_tooltip_xy(posx, posy);

            this->add_widget(this->tooltip);
            this->refresh(this->tooltip->rect);
        }
    }

    virtual bool next_focus() {
        if (this->current_focus) {
            if (this->current_focus->next_focus()) {
                return true;
            }

            Widget2 * future_focus_w = this->get_next_focus(this->current_focus, false);
            if (!future_focus_w) {
                future_focus_w = this->get_next_focus(NULL, false);
            }
            REDASSERT(this->current_focus);
            this->set_widget_focus(future_focus_w, focus_reason_tabkey);

            return true;
        }

        return false;
    }
    virtual bool previous_focus() {
        if (this->current_focus) {
            if (this->current_focus->previous_focus()) {
                return true;
            }

            Widget2 * future_focus_w = this->get_previous_focus(this->current_focus, false);
            if (!future_focus_w) {
                future_focus_w = this->get_previous_focus(NULL, false);
            }
            REDASSERT(this->current_focus);
            this->set_widget_focus(future_focus_w, focus_reason_backtabkey);

            return true;
        }

        return false;
    }

    virtual void rdp_input_mouse(int device_flags, int x, int y, Keymap2 * keymap)
    {
        Widget2 * w = this->last_widget_at_pos(x, y);
        if (this->current_over != w) {
            if (((w != NULL) ? w->pointer_flag : Pointer::POINTER_NORMAL) == Pointer::POINTER_EDIT) {
                this->drawable.server_set_pointer(edit_pointer);
            }
            else {
                this->drawable.server_set_pointer(normal_pointer);
            }
            this->current_over = w;
        }
        if (this->tooltip) {
            if (device_flags & MOUSE_FLAG_MOVE) {
                if (w != this->tooltip->notifier) {
                    this->hide_tooltip();
                }
            }
            if (device_flags & (MOUSE_FLAG_BUTTON1)) {
                this->hide_tooltip();
            }
        }
        WidgetParent::rdp_input_mouse(device_flags, x, y, keymap);
    }

    virtual void rdp_input_scancode(long int param1, long int param2, long int param3, long int param4, Keymap2* keymap)
    {
        if (this->tooltip) {
            this->hide_tooltip();
        }
        WidgetParent::rdp_input_scancode(param1, param2, param3, param4, keymap);
    }
};

#endif
