#include "demo.hpp"

using namespace godot;

void Demo::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_amplitude"), &Demo::get_amplitude);
    ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &Demo::set_amplitude);
    ClassDB::add_property("Demo", PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");

    ClassDB::bind_method(D_METHOD("get_speed"), &Demo::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Demo::set_speed);
    ClassDB::add_property("Demo", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void Demo::_process(double delta) {
    time_passed += speed * delta;
    Vector2 new_position = Vector2(
        amplitude + (amplitude * sin(time_passed * 2.0)),
        amplitude + (amplitude * cos(time_passed * 1.5))
    );
    set_position(new_position);
}

