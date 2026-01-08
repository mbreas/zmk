/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/display/widgets/custom.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct custom_state {
    zmk_keymap_layer_index_t index;
    const char *label;
};

static void set_layer_symbol(lv_obj_t *label, struct custom_state state) {
    if (state.label == NULL || strlen(state.label) == 0) {
        char text[8] = {};

        snprintf(text, sizeof(text), LV_SYMBOL_KEYBOARD " %i", state.index);

        lv_label_set_text(label, text);
    } else {
        char text[14] = {};

        snprintf(text, sizeof(text), LV_SYMBOL_KEYBOARD " %s", state.label);

        lv_label_set_text(label, text);
    }

    lv_label_set_text(label, "Hello world!");
}

static void custom_update_cb(struct custom_state state) {
    struct zmk_widget_custom *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_layer_symbol(widget->obj, state); }
}

static struct custom_state custom_get_state(const zmk_event_t *eh) {
    zmk_keymap_layer_index_t index = zmk_keymap_highest_layer_active();
    return (struct custom_state){
        .index = index, .label = zmk_keymap_layer_name(zmk_keymap_layer_index_to_id(index))};
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_custom, struct custom_state, custom_update_cb, custom_get_state)

ZMK_SUBSCRIPTION(widget_custom, zmk_layer_state_changed);

int zmk_widget_custom_init(struct zmk_widget_custom *widget, lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);

    sys_slist_append(&widgets, &widget->node);

    widget_custom_init();
    return 0;
}

lv_obj_t *zmk_widget_custom_obj(struct zmk_widget_custom *widget) { return widget->obj; }
