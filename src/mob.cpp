#include "mob.hpp"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

using namespace godot;

void Mob::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_visible_on_screen_notifier_2d_screen_exited"), &Mob::_on_visible_on_screen_notifier_2d_screen_exited);
}

void Mob::_ready() {
    get_node<VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D")->connect("screen_exited", Callable(this, "on_visible_on_screen_notifier_2d_screen_exited"));
    AnimatedSprite2D *anim = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    PackedStringArray mob_types = anim->get_sprite_frames()->get_animation_names();
    RandomNumberGenerator rng;
    rng.randomize();
    anim->play(mob_types[rng.randi() % mob_types.size()]);
}

void Mob::_on_visible_on_screen_notifier_2d_screen_exited() {
    queue_free();
    
}