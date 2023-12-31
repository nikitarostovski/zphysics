#pragma once
#include "collision_grid.hpp"
#include "../common/utils.hpp"
#include "../common/math.hpp"

struct PhysicObject {
    int id;
    bool is_static;
    float damping_ratio;
    float radius;
    Vec2 position      = {0.0f, 0.0f};
    Vec2 last_position = {0.0f, 0.0f};
    Vec2 acceleration  = {0.0f, 0.0f};
    Color color;

    PhysicObject() = default;

    explicit
    PhysicObject(int id_, Vec2 position_, Color color_, bool is_static_, float radius_, float damping_ratio_)
        : id(id_)
        , is_static(is_static_)
        , damping_ratio(damping_ratio_)
        , radius(radius_)
        , position(position_)
        , last_position(position_)
        , color(color_)
    {}

    void setPosition(Vec2 pos) {
        position      = pos;
        last_position = pos;
    }

    void update(float dt) {
        const Vec2 last_update_move = position - last_position;
        const Vec2 new_position = position + last_update_move + (acceleration - last_update_move * 40.0f) * (dt * dt);
        last_position = position;
        position = new_position;
        acceleration = {0.0f, 0.0f};
        slowdown(damping_ratio);
    }

    void stop() {
        last_position = position;
    }

    void slowdown(float ratio) {
        last_position = last_position + ratio * (position - last_position);
    }

    [[nodiscard]]
    float getSpeed() const {
        return ZMathVec2::length(position - last_position);
    }

    [[nodiscard]]
    Vec2 getVelocity() const {
        return position - last_position;
    }

    void addVelocity(Vec2 v) {
        last_position -= v;
    }

    void setPositionSameSpeed(Vec2 new_position) {
        const Vec2 to_last = last_position - position;
        position           = new_position;
        last_position      = position + to_last;
    }

    void move(Vec2 v) {
        position += v;
    }
};
