//------------------------------------------------------------------------------

	typedef Functor1 <void, AbstractRender *> GuiRenderEvent;



	class GuiViewport : public GuiNode {

		AbstractRender *r;

		GuiRenderEvent on_render;

	protected:

		virtual void onRender(GuiRender *gui_render) const {
			gui_render->setViewport(getClientRect(true), true);
			r->end2d();
			on_render.invoke(r);
			r->begin2d(-1, -1);
		}

		virtual void onMouseDown(int x, int y, int b) {
			if (gui->getFocus() != this) {
				gui->setFocus(this);
				return;
			}
			on_mouse_down->invoke(this, x, y, b);
		}

	public:

		GuiViewport(Gui *gui) : GuiNode(gui) {
			name = "viewport";
			r = gui->getEngine()->getRender();
		}

		void setRenderEvent(const GuiRenderEvent &event) {
			on_render = event;
		}

	};