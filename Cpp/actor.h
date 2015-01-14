#ifndef ARCUS_ACTOR_H
#define ARCUS_ACTOR_H

#include <string>
#include "environment.h"

namespace arcus {
	class Actor {
	public:
		const std::string type() const;
		const std::string name() const;
		void action();
		bool go(arcus::direction_t direction);
		void talk_to(Actor other) const;
	};


}

#endif