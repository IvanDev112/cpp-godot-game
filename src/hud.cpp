#include "hud.hpp"

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/button.hpp>

using namespace godot;

void HUD::_bind_methods() {
    ClassDB::bind_method(D_METHOD("show_message", "text"), &HUD::show_message);
    ClassDB::bind_method(D_METHOD("on_start_button_pressed"), &HUD::_on_start_button_pressed);
    ClassDB::bind_method(D_METHOD("on_message_timer_timeout"), &HUD::_on_message_timer_timeout);

    ADD_SIGNAL(MethodInfo("start_game"));
}

void HUD::_ready() {
    get_node<Button>("StartButton")->connect("pressed", Callable(this, "on_start_button_pressed"));
    get_node<Timer>("MessageTimer")->connect("timeout", Callable(this, "on_message_timer_timeout"));
}

void HUD::show_message(const String &text) {
    get_node<Label>("Message")->set_text(text);
    get_node<Label>("Message")->show();
    get_node<Timer>("MessageTimer")->start();
}

void HUD::update_score(int score) {
    get_node<Label>("ScoreLabel")->set_text(String::num_int64(score));
}

void HUD::_on_start_button_pressed() {
    get_node<Button>("StartButton")->hide();
    emit_signal("start_game");
}

void HUD::_on_message_timer_timeout() {
    get_node<Label>("Message")->hide();
}