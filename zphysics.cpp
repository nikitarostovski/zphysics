/* zphysics.cpp */

#include "zphysics.h"

#include <cstdint>
#include <limits>

ZPhysics * ZPhysics::singleton;

Vec2 ZPhysics::get_position(int _id) {
    return solver.objects.data[_id].position;
}

int ZPhysics::add_object(Vec2 pos, Color color) {
    int id = solver.createObject(pos, color);
    return id;
}

void ZPhysics::object_accelerate(int _id, Vec2 ac) {
    solver.objects.data[_id].acceleration += ac;
}

void ZPhysics::step(float dt) {
    solver.update(dt);
    
    if (vertices.size() != solver.objects.size()) {
        vertices.resize(solver.objects.size());
        colors.resize(solver.objects.size());
    }
    
    thread_pool.dispatch(to<uint32_t>(solver.objects.size()), [&](uint32_t start, uint32_t end) {
        for (uint32_t i{start}; i < end; ++i) {
            const PhysicObject& object = solver.objects.data[i];
            vertices.set(i, object.position);
            colors.set(i, object.color);
        }
    });
    
    Ref<ArrayMesh> mesh = memnew(ArrayMesh);
    
    Array a;
    a.resize(Mesh::ARRAY_MAX);
    a[Mesh::ARRAY_VERTEX] = vertices;
    a[Mesh::ARRAY_COLOR] = colors;
    
    mesh->add_surface_from_arrays(Mesh::PRIMITIVE_POINTS, a);
    renderer->set_mesh(mesh);
}

void ZPhysics::bind_renderer(MeshInstance2D *mi) {
    renderer = mi;
}

void ZPhysics::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step", "dt"), &ZPhysics::step);
    ClassDB::bind_method(D_METHOD("addObject", "pos", "color"), &ZPhysics::add_object);
    ClassDB::bind_method(D_METHOD("getPosition", "id"), &ZPhysics::get_position);
    ClassDB::bind_method(D_METHOD("accelerateObject", "id", "acc"), &ZPhysics::object_accelerate);
    ClassDB::bind_method(D_METHOD("bindRenderer", "mi"), &ZPhysics::bind_renderer);
}

ZPhysics::ZPhysics()
    : world_size{300, 300}
    , solver{world_size, thread_pool} {
    
        singleton = this;
}

ZPhysics* ZPhysics::get_singleton() {
    return singleton;
}
