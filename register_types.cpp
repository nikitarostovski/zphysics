/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "zphysics.h"

void initialize_zphysics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
	}
	ClassDB::register_class<ZPhysics>();
}

void uninitialize_zphysics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
	}
   // Nothing to do here in this example.
}