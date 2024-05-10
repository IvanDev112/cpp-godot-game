#include "player.hpp"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_body_entered", "body"), &Player::_on_body_entered);
    ADD_SIGNAL(MethodInfo("hit"));
}

void Player::start(const Vector2 &pos) {
    set_position(pos);
    show();
    get_node<CollisionShape2D>("CollisionShape2D")->set_disabled(false);
}

void Player::_ready() {
    connect("body_entered", Callable(this, "on_body_entered"));
    get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_scale(Vector2(0.5, 0.5));
    screen_size = get_viewport_rect().size;
    hide();
}

void Player::_process(double delta) {
    Vector2 velocity = Vector2(0.0, 0.0);
    Input *input = Input::get_singleton();
    AnimatedSprite2D *anim = get_node<AnimatedSprite2D>("AnimatedSprite2D");

    if (input->is_action_pressed("move_right")) {
        velocity.x += 1;
    }
    if (input->is_action_pressed("move_left")) {
        velocity.x -= 1;
    }
    if (input->is_action_pressed("move_down")) {
        velocity.y += 1;
    }
    if (input->is_action_pressed("move_up")) {
        velocity.y -= 1;
    }

    if (velocity.x != 0.0) {
        anim->set_animation("walk");
        anim->set_flip_v(false);
        anim->set_flip_h(velocity.x < 0.0);
    } else if (velocity.y != 0.0) {
        anim->set_animation("up");
        anim->set_flip_v(velocity.y > 0);
    }

    if (velocity.length() > 0.0) {
        velocity = velocity.normalized() * speed;
        anim->play();
    } else {
        anim->stop();
    }

    Vector2 position = get_position();
    position += velocity * delta;
    position = position.clamp(Vector2(0.0, 0.0), screen_size);
    set_position(position);
}

void Player::_on_body_entered(Node2D *body) {
    hide();
    emit_signal("hit");
    get_node<CollisionShape2D>("CollisionShape2D")->set_deferred("disabled", true);
}