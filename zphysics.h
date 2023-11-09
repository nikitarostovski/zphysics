/* zphysics.h */

#ifndef ZPHYSICS_H
#define ZPHYSICS_H

#include "core/object/ref_counted.h"
#include "src/physics/physics.hpp"
#include "src/thread_pool/thread_pool.hpp"
#include "scene/2d/mesh_instance_2d.h"

class ZPhysics : public RefCounted {
	GDCLASS(ZPhysics, RefCounted);

    IVec2 world_size;
    
    tp::ThreadPool thread_pool{10};
    PhysicSolver solver;
    
    MeshInstance2D *renderer;
    
    Vector<Vector2> vertices;
    Vector<Color> colors;
    
protected:
    static ZPhysics* singleton;
	static void _bind_methods();

public:
    ZPhysics();
    static ZPhysics* get_singleton();
    
    Vec2 get_position(int _id);
    int add_object(Vec2 pos, Color color, bool is_static, float radius, float damping_ratio);
    void object_accelerate(int _id, Vec2 ac);
    void step(float dt);
    void bind_renderer(MeshInstance2D *mi);
};

#endif // ZPHYSICS_H
