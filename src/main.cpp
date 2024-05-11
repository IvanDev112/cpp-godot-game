#include "main.hpp"
#include "player.hpp"
#include "mob.hpp"
#include "hud.hpp"

#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>

using namespace godot;

void Main::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ClassDB::bind_method(D_METHOD("set_mob_scene", "p_mob_scene"), &Main::set_mob_scene);
    ClassDB::add_property("Main", PropertyInfo(Variant::OBJECT, "mob_scene"), "set_mob_scene", "get_mob_scene");

    ClassDB::bind_method(D_METHOD("on_start_timer_timeout"), &Main::_on_start_timer_timeout);
    ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
    ClassDB::bind_method(D_METHOD("on_score_timer_timeout"), &Main::_on_score_timer_timeout);
    ClassDB::bind_method(D_METHOD("new_game"), &Main::new_game);
    ClassDB::bind_method(D_METHOD("game_over"), &Main::game_over);
}

void Main::_ready() {
    get_node<Timer>("StartTimer")->connect("timeout", Callable(this, "on_start_timer_timeout"));
    get_node<Timer>("MobTimer")->connect("timeout", Callable(this, "on_mob_timer_timeout"));
    get_node<Timer>("ScoreTimer")->connect("timeout", Callable(this, "on_score_timer_timeout"));
    get_node<HUD>("Hud")->connect("start_game", Callable(this, "new_game"));
    get_node<Player>("Player")->connect("hit", Callable(this, "game_over"));
}

void Main::game_over() {
    get_node<Timer>("ScoreTimer")->stop();
    get_node<Timer>("MobTimer")->stop();
    get_node<HUD>("Hud")->call("show_game_over");
    get_node<AudioStreamPlayer>("Music")->stop();
    get_node<AudioStreamPlayer>("DeathSound")->play();
}

void Main::new_game() {
    get_tree()->call_group("mobs", "queue_free");
    get_node<AudioStreamPlayer>("Music")->play();
    score = 0;
    get_node<Player>("Player")->start(get_node<Marker2D>("StartPosition")->get_position());
    get_node<Timer>("StartTimer")->start();

    get_node<HUD>("Hud")->update_score(score);
    get_node<HUD>("Hud")->show_message("Get Ready");
}

void Main::_on_start_timer_timeout() {
    get_node<Timer>("ScoreTimer")->start();
    get_node<Timer>("MobTimer")->start();
}

void Main::_on_score_timer_timeout() {
    score += 1;
    get_node<HUD>("Hud")->update_score(score);
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