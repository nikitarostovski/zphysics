/* zphysics.cpp */

#include "zphysics.h"

//#include "src/physics/physics.hpp"
//#include "src/thread_pool/thread_pool.hpp"

Vec2 ZPhysics::getPosition(int _id) {
    return solver.objects.data[_id].position;
}

int ZPhysics::addObject(Vec2 pos) {
    int id = solver.createObject(pos);
    return id;
}

void ZPhysics::step(float dt, CanvasItem *node) {
    solver.update(dt);
    
    vertices.resize(solver.objects.size());
//    for (int i = 0; i < solver.objects.data.size(); i++) {
//        Vec2 pos = solver.objects.data[i].position;
//        node->draw_circle(pos, 1.0, Color(1.0, 0.0, 0.0, 1.0));
//    }
    
    thread_pool.dispatch(to<uint32_t>(solver.objects.size()), [&](uint32_t start, uint32_t end) {
        for (uint32_t i{start}; i < end; ++i) {
            const PhysicObject& object = solver.objects.data[i];
            vertices.set(i, object.position);
            
//            node->draw_circle(object.position, 1.0, Color(1.0, 0.0, 0.0, 1.0));
//            const uint32_t idx = i << 2;
//            objects_va[idx + 0].position = object.position + Vec2{-radius, -radius};
//            objects_va[idx + 1].position = object.position + Vec2{ radius, -radius};
//            objects_va[idx + 2].position = object.position + Vec2{ radius,  radius};
//            objects_va[idx + 3].position = object.position + Vec2{-radius,  radius};
//            objects_va[idx + 0].texCoords = {0.0f        , 0.0f};
//            objects_va[idx + 1].texCoords = {texture_size, 0.0f};
//            objects_va[idx + 2].texCoords = {texture_size, texture_size};
//            objects_va[idx + 3].texCoords = {0.0f        , texture_size};
//
//            const sf::Color color = object.color;
//            objects_va[idx + 0].color = color;
//            objects_va[idx + 1].color = color;
//            objects_va[idx + 2].color = color;
//            objects_va[idx + 3].color = color;
        }
    });
    
    Ref<ArrayMesh> mesh = memnew(ArrayMesh);
    
    Array a;
    a.resize(Mesh::ARRAY_MAX);
    a[Mesh::ARRAY_VERTEX] = vertices;
    
    mesh->add_surface_from_arrays(Mesh::PRIMITIVE_POINTS, a);
    renderer->set_mesh(mesh);
}

void ZPhysics::bind_renderer(MeshInstance2D *mi) {
    renderer = mi;
}

void ZPhysics::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step", "dt", "node"), &ZPhysics::step);
    ClassDB::bind_method(D_METHOD("addObject", "pos"), &ZPhysics::addObject);
    ClassDB::bind_method(D_METHOD("getPosition", "_id"), &ZPhysics::getPosition);
    ClassDB::bind_method(D_METHOD("bind_renderer", "mi"), &ZPhysics::bind_renderer);
}

ZPhysics::ZPhysics() :solver{world_size, thread_pool} {
    
}
