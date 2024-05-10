#include "main.hpp"
#include "player.hpp"
#include "mob.hpp"
#include <godot_cpp/godot.hpp>

#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>

using namespace godot;

void Main::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ClassDB::bind_method(D_METHOD("set_mob_scene", "p_mob_scene"), &Main::set_mob_scene);
    ClassDB::add_property("Main", PropertyInfo(Variant::OBJECT, "mob_scene"), "set_mob_scene", "get_mob_scene");

    ClassDB::bind_method(D_METHOD("on_start_timer_timeout"), &Main::_on_start_timer_timeout);
    ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
    ClassDB::bind_method(D_METHOD("on_score_timer_timeout"), &Main::_on_score_timer_timeout);
}

void Main::_ready() {
    get_node<Timer>("StartTimer")->connect("timeout", Callable(this, "on_start_timer_timeout"));
    get_node<Timer>("MobTimer")->connect("timeout", Callable(this, "on_mob_timer_timeout"));
    get_node<Timer>("ScoreTimer")->connect("timeout", Callable(this, "on_score_timer_timeout"));
    new_game();
}

void Main::game_over() {
    get_node<Timer>("ScoreTimer")->stop();
    get_node<Timer>("MobTimer")->stop();
}

void Main::new_game() {
    score = 0;
    get_node<Player>("Player")->start(get_node<Marker2D>("StartPosition")->get_position());
    get_node<Timer>("StartTimer")->start();
}

void Main::_on_start_timer_timeout() {
    get_node<Timer>("ScoreTimer")->start();
    get_node<Timer>("MobTimer")->start();
}

void Main::_on_score_timer_timeout() {
    score += 1;
}

void Main::_on_mob_timer_timeout() {
    Mob *mob = (Mob *)mob_scene->instantiate();
    RandomNumberGenerator rng;
    rng.randomize();

    PathFollow2D *mob_spawn_location = get_node<PathFollow2D>("MobPath/MobSpawnLocation");
    mob_spawn_location->set_progress_ratio(rng.randf());

    double direction = mob_spawn_location->get_rotation() + M_PI / 2;
    mob->set_position(mob_spawn_location->get_position());

    direction += rng.randf_range(-M_PI / 4, M_PI / 4);
    mob->set_rotation(direction);

    Vector2 velocity = Vector2(rng.randf_range(150.0, 250.0), 0.0);
    mob->set_linear_velocity(velocity.rotated(direction));

    add_child(mob);
}