#ifndef MAIN_HPP
#define MAIN_HPP
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Main : public Node {
    GDCLASS(Main, Node)
private:
    Ref<PackedScene> mob_scene;
    int score;
protected:
    static void _bind_methods();
public:
    Main() : mob_scene(nullptr), score(0) {}
    ~Main() {}

    void _ready() override;

    void game_over();
    void new_game();

    void _on_start_timer_timeout();
    void _on_score_timer_timeout();
    void _on_mob_timer_timeout();

    void set_mob_scene(const Ref<PackedScene> p_mob_scene) { mob_scene = p_mob_scene; }
    Ref<PackedScene> get_mob_scene() const { return mob_scene; }
};

}

#endif // MAIN_HPP