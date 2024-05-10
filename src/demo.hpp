#ifndef DEMO_HPP
#define DEMO_HPP
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Demo : public Sprite2D {
    GDCLASS(Demo, Sprite2D)
private:
    double time_passed;
    double amplitude;
    double speed;
protected:
    static void _bind_methods();
public:
    Demo() : time_passed(0.0), amplitude(10.0), speed(1.0) {}
    ~Demo() {}

    void _process(double delta) override;

    void set_amplitude(const double p_amplitude) { amplitude = p_amplitude; }
    double get_amplitude() const { return amplitude; }

    void set_speed(const double p_speed) { speed = p_speed; }
    double get_speed() const { return speed; }
};

}

#endif // DEMO_HPP