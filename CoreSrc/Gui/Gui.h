//------------------------------------------------------------------------------

#include "Resource.h"
#include "AbstractRender.h"

	class GuiNode;
	class Engine;
			struct {
				int x;
			};

			struct {
				int v[2];
				int s[2];
			};

		};


		bool isInclude(int px, int py) const {
			return px >= x && py >= y && px < x + width && py < y + height;
		}

		Rect operator+ (const Rect &o) const {
			return Rect(x + o.x, y + o.y, width + o.width, height + o.height);
		}

	//--------------------------------------------------------------------------

		TextureRef image;
		GuiSkin() {
		}

	//--------------------------------------------------------------------------

		GUI_ALIGN_NONE			= 0x00,

		GUI_ALIGN_LEFT			= 0x01,
		GUI_ALIGN_RIGHT			= 0x02,

		GUI_ALIGN_TOP			= GUI_ALIGN_LEFT,
		GUI_ALIGN_BOTTOM		= GUI_ALIGN_RIGHT,

		GUI_ALIGN_CENTER		= 0x03,
		GUI_ALIGN_EXPAND		= 0x04,

		GUI_ALIGN_COUNT,

	//int align(int x, const Rect &target, GuiAlignType align, int width = 0);
	struct GuiAlign {

		union {
			struct {
				GuiAlignType horizontal;
				GuiAlignType vertical;
			};
			struct {
				GuiAlignType v[2];
			};
		};

		GuiAlign(GuiAlignType horiz = GUI_ALIGN_NONE, GuiAlignType vert = GUI_ALIGN_NONE) {
			horizontal = horiz;
			vertical = vert;
		}

		Rect makeAlignedRect(const Rect &rect, const Rect &target) const;
		static int makeAlignedCoord(int coord, int size, int target_coord, int target_size, GuiAlignType align);
		static int makeLocalAlignedCoord(int coord, int size, int target_size, GuiAlignType align);
		static int makeAlignedSize(int size, int target_size, GuiAlignType align);

	};

	class GuiRender {
		Engine *engine;
		Rect viewport;

		AbstractRender *getRender() { return render; }
		void setViewport(int x, int y, int width, int height, bool clip = false);

		Rect getClientRect(const Rect &rect, GuiRectType type);

		void drawRect(const Rect &rect, GuiRectType type);

		void drawText(const Rect &rect, const char *text, const GuiAlign &align = GUI_ALIGN_NONE);
		Rect getTextRect(const char *text, int start = 0, int count = -1);

		void drawImage(const Rect &rect, const TextureRef &image, const GuiAlign &align = GUI_ALIGN_NONE, int w_frames = 1, int h_frames = 1, int image_index = 0);

		void setColor(const vec3 &color, float alpha = 1.0f);


		GuiNode *focus;
		Engine *engine;
		template <class T>
		Engine *getEngine();

		void addChild(GuiNode *child);

		void render() const;
		void update(float dt);
		void redraw();

		virtual void onMouseMove(int x, int y, int b);
		virtual void onResize(int w, int h);

		virtual void onKeyDown(int key);
		virtual void onKeyRepeat(int key);
		virtual void onKeyUp(int key);
		virtual void onKeyChar(char key);

		GuiNode *getFocus();
		void setFocus(GuiNode *node);
//------------------------------------------------------------------------------