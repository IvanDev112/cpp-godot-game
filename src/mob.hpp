#ifndef MOB_HPP
#define MOB_HPP
#include <godot_cpp/classes/rigid_body2d.hpp>

namespace godot {

class Mob : public RigidBody2D {
    GDCLASS(Mob, RigidBody2D)
private:

protected:
    static void _bind_methods();
public:
    Mob() {}
    ~Mob() {}

    void _ready() override;
    
    void _on_visible_on_screen_notifier_2d_screen_exited();
};

}

#endif // MOB_HPP