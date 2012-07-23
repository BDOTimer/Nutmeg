//------------------------------------------------------------------------------
#include "Debug.h"
//------------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	Sprite *Sprite::loadResource(const char *name) {
		Sprite *sprite = new Sprite();
		sprite->load(name);
		return sprite;
	}


		const Sprite::Animation *new_animation = sprite->getAnimation(id);

		speed = speed_;
		if (current_animation == new_animation) return;
		current_animation = new_animation;
