/* zphysics.h */

#ifndef ZPHYSICS_H
#define ZPHYSICS_H

#include "core/object/ref_counted.h"
#include "src/physics/physics.hpp"
#include "src/thread_pool/thread_pool.hpp"

#include "scene/main/canvas_item.h"

#include "scene/2d/mesh_instance_2d.h"

class ZPhysics : public RefCounted {
	GDCLASS(ZPhysics, RefCounted);

    const IVec2 world_size{300, 300};
    tp::ThreadPool thread_pool{10};
    PhysicSolver solver;
    
    MeshInstance2D *renderer;
    
    Vector<Vector2> vertices;
    
protected:
	static void _bind_methods();

public:
    Vec2 getPosition(int _id);
    
    int addObject(Vec2 pos);
    
    void step(float dt, CanvasItem *node);
    
    void bind_renderer(MeshInstance2D *mi);
    
	ZPhysics();
};

#endif // ZPHYSICS_H
