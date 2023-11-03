/* zphysics.h */

#ifndef ZPHYSICS_H
#define ZPHYSICS_H

#include "core/object/ref_counted.h"

class ZPhysics : public RefCounted {
	GDCLASS(ZPhysics, RefCounted);

	int count;

protected:
	static void _bind_methods();

public:
	void add(int p_value);
	void reset();
	int get_total() const;

	ZPhysics();
};

#endif // ZPHYSICS_H