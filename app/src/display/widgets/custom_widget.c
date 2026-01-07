#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display/widgets/custom_widget.h>
#include <zmk/event_manager.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct custom_status_state {
    // Define your widget state here
    uint8_t value;
    bool active;
};

int zmk_widget_custom_init(struct zmk_widget_custom *widget, lv_obj_t *parent) {
    char greetings[] = "Hello World!";

    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 40, 15);

    widget->label = lv_label_create(widget->obj);
    lv_obj_align(widget->label, LV_ALIGN_CENTER, 0, 0);

    lv_label_set_text(label, greetings);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_custom_obj(struct zmk_widget_custom *widget) { return widget->obj; }