#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class Player : public Area2D {
    GDCLASS(Player, Area2D)
private:
    double speed;
    Vector2 screen_size;
protected:
    static void _bind_methods();
public:
    Player() : speed(400.0), screen_size(Vector2(0.0, 0.0)) {}
    ~Player() {}

    void start(const Vector2 &pos);

    void _ready() override;
    void _process(double delta) override;

    void _on_body_entered(Node2D *body);
};

}

#endif // PLAYER_HPP