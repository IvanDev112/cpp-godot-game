#ifndef HUD_HPP
#define HUD_HPP

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

class HUD : public CanvasLayer {
    GDCLASS(HUD, CanvasLayer)
protected:
    static void _bind_methods();
public:
    HUD() {}
    ~HUD() {}

    void _ready() override;

    void show_message(const String &text);
    void update_score(int score);

    void _on_start_button_pressed();
    void _on_message_timer_timeout();
};

}

#endif // HUD_HPP