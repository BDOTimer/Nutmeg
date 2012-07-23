//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef SpriteH#define SpriteH//------------------------------------------------------------------------------#include "LibApi.h"#include "AbstractRender.h"#include "Resource.h"#include "MathCore.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------	//	// class Sprite	//	//--------------------------------------------------------------------------	class NUTMEG_API Sprite {	public:		//----------------------------------------------------------------------		// class Image		//----------------------------------------------------------------------		struct Image {			TextureRef texture;			int width_frames;			int height_frames;			vec3 anchor;			Image();		};		//----------------------------------------------------------------------		// class Imposter		//----------------------------------------------------------------------		struct Imposter {			int image;			int start;			int end;			Array <int> frames;			Imposter();		};		//----------------------------------------------------------------------		// class Animation		//----------------------------------------------------------------------		struct Animation {			Str name;			float speed;			int yaw_count;			int pitch_count;			Array < Array <Imposter> > imposters;			Animation();		};	private:		Map <Str, Image> images;		Map <Str, Animation> animations;		Str name;	public:		//----------------------------------------------------------------------		// sprite		//----------------------------------------------------------------------		Sprite();		~Sprite();		//----------------------------------------------------------------------		// animations		//----------------------------------------------------------------------		int getAnimationsCount() const;		Animation &getAnimation(int index);		const Animation &getAnimation(int index) const;		Animation *getAnimation(const char *id);		const Animation *getAnimation(const char *id) const;		//----------------------------------------------------------------------		// images		//----------------------------------------------------------------------		int getImagessCount() const;		Image &getImage(int index);		const Image &getImage(int index) const;		Image *getImage(const char *id);		const Image *getImage(const char *id) const;		//----------------------------------------------------------------------		//		//----------------------------------------------------------------------		const char *getName() const;		void readXml(const Xml *xml);		//----------------------------------------------------------------------		// resource		//----------------------------------------------------------------------		void load(const char *name);		Sprite *loadResource(const char *name);
		virtual bool isExternal() const;		//----------------------------------------------------------------------	};	//--------------------------------------------------------------------------	//	// class SpriteState	//	//--------------------------------------------------------------------------	class NUTMEG_API SpriteState {		SpriteRef sprite;		const Sprite::Animation *current_animation;		float frame_phase;		float speed;		void init();	public:		SpriteState();		int getYawIndex(float yaw) const;		int getPitchIndex(float pitch) const;		const Sprite::Imposter *getImposter(float yaw, float pitch) const;		const Sprite::Image *getImage(float yaw, float pitch) const;		int getAtlasIndex(float yaw, float pitch) const;		int getNextAtlasIndex(float yaw, float pitch) const;		float getFramePhase(float yaw, float pitch) const;		void setAnimation(const char *id, float speed_ = 1.0f);		void update(float dt);		void writeXml(Xml *xml) const;		void readXml(const Xml *xml);		void load(const char *name);		const char *getFileName() const;	};	//--------------------------------------------------------------------------}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------