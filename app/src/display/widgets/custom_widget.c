#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display/widgets/custom_widget.h>
#include <zmk/event_manager.h>
#include <zmk/events/your_event.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct custom_status_state {
    // Define your widget state here
    uint8_t value;
    bool active;
};

static void set_status_symbol(lv_obj_t *label, struct custom_status_state state) {
    char text[64];
    snprintf(text, sizeof(text), "Value: %d", state.value);
    lv_label_set_text(label, text);
}

void custom_status_update_cb(struct custom_status_state state) {
    struct zmk_widget_custom *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        zmk_widget_custom_set_status(widget, state);
    }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_custom, struct custom_status_state, custom_status_update_cb,
                            get_current_status)

ZMK_SUBSCRIPTION(widget_custom, zmk_your_event_changed);

int zmk_widget_custom_init(struct zmk_widget_custom *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 40, 15);

    widget->label = lv_label_create(widget->obj);
    lv_obj_align(widget->label, LV_ALIGN_CENTER, 0, 0);

    char text[64];
    snprintf(text, sizeof(text), "Hallo");
    lv_label_set_text(widget->label, text);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_custom_obj(struct zmk_widget_custom *widget) { return widget->obj; }

int zmk_widget_custom_set_status(struct zmk_widget_custom *widget,
                                 struct custom_status_state state) {
    set_status_symbol(widget->label, state);
    return 0;
}