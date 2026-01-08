/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

struct zmk_widget_custom {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_custom_init(struct zmk_widget_custom *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_custom_obj(struct zmk_widget_custom *widget);