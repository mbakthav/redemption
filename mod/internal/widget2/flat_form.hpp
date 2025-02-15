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
 *   Copyright (C) Wallix 2010-2013
 *   Author(s): Christophe Grosjean, Dominique Lafages, Jonathan Poelen,
 *              Meng Tan
 */

#if !defined(REDEMPTION_MOD_INTERNAL_WIDGET2_FLAT_FORM_HPP)
#define REDEMPTION_MOD_INTERNAL_WIDGET2_FLAT_FORM_HPP

#include "composite.hpp"
#include "flat_button.hpp"
#include "multiline.hpp"
#include "image.hpp"
#include "widget2_rect.hpp"
#include "edit.hpp"
#include "password.hpp"
#include "theme.hpp"
#include "group_box.hpp"
#include "translation.hpp"
#include "regex.hpp"

class FlatForm : public WidgetParent
{
public:

enum {
    NONE = 0x00,
    COMMENT_DISPLAY = 0x01,
    COMMENT_MANDATORY = 0x02,
    TICKET_DISPLAY = 0x04,
    TICKET_MANDATORY = 0x08,
    DURATION_DISPLAY = 0x10,
    DURATION_MANDATORY = 0x20,
};
    const char * generic_warning;
    const char * format_warning;
    const char * toohigh_warning;
    const char * field_comment;
    const char * field_ticket;
    const char * field_duration;
    char warning_buffer[512];
    // WidgetGroupBox groupbox;
    WidgetLabel warning_msg;

    WidgetLabel comment_label;
    WidgetEdit comment_edit;
    WidgetLabel ticket_label;
    WidgetEdit ticket_edit;
    WidgetLabel duration_label;
    WidgetEdit duration_edit;
    WidgetLabel duration_format;
    WidgetLabel notes;
    WidgetFlatButton confirm;

    CompositeArray composite_array;
    int flags;

    FlatForm(DrawApi& drawable, int16_t width, int16_t height,
             Widget2 & parent, NotifyApi* notifier, int group_id, Inifile & ini,
             Theme & theme, int flags = 0)
        : WidgetParent(drawable, Rect(0, 0, width, height), parent, notifier, group_id)
        , generic_warning(TR("%s field_required", ini))
        , format_warning(TR("%s invalid_format", ini))
        , toohigh_warning(TR("%s toohigh_duration", ini))
        , field_comment(TR("comment", ini))
        , field_ticket(TR("ticket", ini))
        , field_duration(TR("duration", ini))
        , warning_buffer()
        , warning_msg(drawable, 10, 0, *this, NULL, "", true, group_id,
                  theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , comment_label(drawable, 0, 10, *this, NULL, TR("comment", ini), true,
                        group_id, theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , comment_edit(drawable, this->comment_label.lx() + 20, 10, 300, *this, this,
                       0, group_id, theme.edit.fgcolor, theme.edit.bgcolor,
                       theme.edit.focus_color, ini.font, -1, 1, 1)
        , ticket_label(drawable, 0, 40, *this, NULL, TR("ticket", ini), true,
                       group_id, theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , ticket_edit(drawable, this->ticket_label.lx() + 20, 40, 300, *this, this,
                      0, group_id, theme.edit.fgcolor, theme.edit.bgcolor,
                      theme.edit.focus_color, ini.font, -1, 1, 1)
        , duration_label(drawable, 0, 70, *this, NULL, TR("duration", ini), true,
                         group_id, theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , duration_edit(drawable, this->duration_label.lx() + 20, 70, 300, *this, this,
                        0, group_id, theme.edit.fgcolor, theme.edit.bgcolor,
                        theme.edit.focus_color, ini.font, -1, 1, 1)
        , duration_format(drawable, 0, 100, *this, NULL, TR("note_duration_format", ini),
                          true, group_id, theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , notes(drawable, 0, 120, *this, NULL, TR("note_required", ini), true,
                group_id, theme.global.fgcolor, theme.global.bgcolor, ini.font)
        , confirm(drawable, 0, 0, *this, this, TR("confirm", ini), true, group_id,
                  theme.global.fgcolor, theme.global.bgcolor, theme.global.focus_color, ini.font,
                  6, 2)
        , flags(flags)
    {
        this->set_bg_color(theme.global.bgcolor);
        this->impl = &composite_array;
        this->add_widget(&this->warning_msg);
        if (this->flags & COMMENT_DISPLAY) {
            this->add_widget(&this->comment_label);
            this->add_widget(&this->comment_edit);
        }
        if (this->flags & TICKET_DISPLAY) {
            this->add_widget(&this->ticket_label);
            this->add_widget(&this->ticket_edit);
        }
        if (this->flags & DURATION_DISPLAY) {
            this->add_widget(&this->duration_label);
            this->add_widget(&this->duration_edit);
            this->add_widget(&this->duration_format);
        }
        if (this->flags & COMMENT_MANDATORY) {
            this->comment_label.set_text(TR("comment_r", ini));
        }
        if (this->flags & TICKET_MANDATORY) {
            this->ticket_label.set_text(TR("ticket_r", ini));
        }
        if (this->flags & DURATION_MANDATORY) {
            this->duration_label.set_text(TR("duration_r", ini));
        }

        int labelmaxwidth = std::max(this->comment_label.cx(),
                                     std::max(this->ticket_label.cx(),
                                              this->duration_label.cx()));
        this->warning_msg.rect.x = labelmaxwidth + 20;
        this->comment_edit.set_edit_x(labelmaxwidth + 20);
        this->ticket_edit.set_edit_x(labelmaxwidth + 20);
        this->duration_edit.set_edit_x(labelmaxwidth + 20);
        this->comment_edit.set_edit_cx(width - labelmaxwidth - 20);
        this->ticket_edit.set_edit_cx(width - labelmaxwidth - 20);
        this->duration_edit.set_edit_cx(width - labelmaxwidth - 20);
        this->duration_format.rect.x = labelmaxwidth + 20;
        if (this->flags & (COMMENT_MANDATORY | TICKET_MANDATORY | DURATION_MANDATORY)) {
            this->add_widget(&this->notes);
            this->notes.rect.x = labelmaxwidth + 20;
        }

        int y = 20;
        if (this->flags & COMMENT_DISPLAY) {
            this->comment_label.set_xy(this->comment_label.dx(), y);
            this->comment_edit.set_edit_y(y);
            y += 30;
        }
        if (this->flags & TICKET_DISPLAY) {
            this->ticket_label.set_xy(this->ticket_label.dx(), y);
            this->ticket_edit.set_edit_y(y);
            y += 30;
        }
        if (this->flags & DURATION_DISPLAY) {
            this->duration_label.set_xy(this->duration_label.dx(), y);
            this->duration_edit.set_edit_y(y);
            y += 30;
            this->duration_format.set_xy(this->duration_format.dx(), y);
            y += 20;
        }
        if (this->flags & (COMMENT_MANDATORY | TICKET_MANDATORY | DURATION_MANDATORY)) {
            this->notes.set_xy(this->notes.dx(), y);
        }

        this->add_widget(&this->confirm);
        this->confirm.set_button_x(width - this->confirm.cx());
        this->confirm.set_button_y(this->duration_edit.ly() + 20);
    }

    virtual ~FlatForm() {
        this->clear();
    }

    virtual void move_xy(int16_t x, int16_t y) {
        this->rect.x += x;
        this->rect.y += y;
        this->WidgetParent::move_xy(x,y);
    }
    virtual void set_xy(int16_t x, int16_t y) {
        this->move_xy(x - this->rect.x, y - this->rect.y);
    }

    virtual void notify(Widget2* widget, NotifyApi::notify_event_t event) {
        if (widget->group_id == this->confirm.group_id) {
            if (NOTIFY_SUBMIT == event) {
                this->check_confirmation();
            }
        }
        else {
            WidgetParent::notify(widget, event);
        }
    }
    void set_warning_buffer(const char * field, const char * format) {
        sprintf(this->warning_buffer, format, field);
        this->warning_msg.set_text(this->warning_buffer);
    }

    unsigned long check_duration(const char * duration) {
        unsigned long res = 0;
        unsigned long hours = 0;
        unsigned long minutes = 0;
        long d = 0;
        char * end_p = 0;
        try {
            d = strtoul(duration, &end_p, 10);
            if (*end_p == 'h') {
                res = (d > 0);
                hours = d;
                end_p++;
                d = strtoul(end_p, &end_p, 10);
                if (*end_p == 'm') {
                    res |= (d > 0);
                    minutes = d;
                    end_p++;
                }
                else if (d > 0) {
                    res = 0;
                }
            }
            else if (*end_p == 'm') {
                res = (d > 0);
                minutes = d;
                end_p++;
            }
        }
        catch (...) {
            res = 0;
        }
        if (res && *end_p != 0) {
            res = 0;
        }
        if (res > 0) {
            res = hours * 60 + minutes;
        }
        return res;
    }

    void check_confirmation() {
        if (((this->flags & COMMENT_DISPLAY) == COMMENT_DISPLAY) &&
            ((this->flags & COMMENT_MANDATORY) == COMMENT_MANDATORY) &&
            (this->comment_edit.num_chars == 0)) {
            this->set_warning_buffer(this->field_comment, this->generic_warning);
            this->set_widget_focus(&this->comment_edit, focus_reason_mousebutton1);
            this->draw(this->warning_msg.rect);
            return;
        }
        if (((this->flags & TICKET_DISPLAY) == TICKET_DISPLAY) &&
            ((this->flags & TICKET_MANDATORY) == TICKET_MANDATORY) &&
            (this->ticket_edit.num_chars == 0)) {
            this->set_warning_buffer(this->field_ticket, this->generic_warning);
            this->set_widget_focus(&this->ticket_edit, focus_reason_mousebutton1);
            this->draw(this->rect);
            return;
        }
        if (((this->flags & DURATION_DISPLAY) == DURATION_DISPLAY) &&
            ((this->flags & DURATION_MANDATORY) == DURATION_MANDATORY) &&
            (this->duration_edit.num_chars == 0)) {
            this->set_warning_buffer(this->field_duration, this->generic_warning);
            this->set_widget_focus(&this->duration_edit, focus_reason_mousebutton1);
            this->draw(this->rect);
            return;
        }
        if (((this->flags & DURATION_DISPLAY) == DURATION_DISPLAY) &&
            (this->duration_edit.num_chars != 0)) {
            long res = this->check_duration(this->duration_edit.get_text());
            // res is duration in hours.
            if ((res <= 0) || (res >= 600000)) {
                if (res <= 0) {
                    this->duration_edit.set_text("");
                    this->set_warning_buffer(this->field_duration, this->format_warning);
                }
                else {
                    this->set_warning_buffer(this->field_duration, this->toohigh_warning);
                }
                this->set_widget_focus(&this->duration_edit, focus_reason_mousebutton1);
                this->draw(this->rect);
                return;
            }
        }

        if (this->notifier) {
            this->notifier->notify(&this->confirm, NOTIFY_SUBMIT);
        }
    }

    virtual void rdp_input_scancode(long int param1, long int param2, long int param3, long int param4, Keymap2* keymap)
    {
        if (keymap->nb_kevent_available() > 0){
            switch (keymap->top_kevent()){
            case Keymap2::KEVENT_ESC:
                keymap->get_kevent();
                this->send_notify(NOTIFY_CANCEL);
                break;
            default:
                WidgetParent::rdp_input_scancode(param1, param2, param3, param4, keymap);
                break;
            }
        }
    }
};

#endif
