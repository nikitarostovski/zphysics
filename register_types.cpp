/* register_types.cpp */

#include "register_types.h"
#include "core/config/engine.h"
#include "core/object/class_db.h"
#include "zphysics.h"

static ZPhysics* ZPhysicsPtr = NULL;

void initialize_zphysics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
	}
    ClassDB::register_class<ZPhysics>();
    
    ZPhysicsPtr = memnew(ZPhysics);
    Engine::get_singleton()->add_singleton(Engine::Singleton("ZPhysics", ZPhysics::get_singleton()));
}

void uninitialize_zphysics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
	}
    memdelete(ZPhysicsPtr);
}
