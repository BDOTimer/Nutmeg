//------------------------------------------------------------------------------
	int GuiAlign::makeLocalAlignedCoord(int coord, int size, int target_size, GuiAlignType align) {

		switch (align) {
			case GUI_ALIGN_CENTER:	return (target_size - size) / 2;
			case GUI_ALIGN_LEFT:	return 0;
			case GUI_ALIGN_RIGHT:	return target_size - size;
			case GUI_ALIGN_EXPAND:	return 0;
			default:				return coord;
		}

		return coord;
	}
	//--------------------------------------------------------------------------
	int GuiAlign::makeAlignedCoord(int coord, int size, int target_coord, int target_size, GuiAlignType align) {
		return target_coord + makeLocalAlignedCoord(coord, size, target_size, align);
	}
	//--------------------------------------------------------------------------
	int GuiAlign::makeAlignedSize(int size, int target_size, GuiAlignType align) {
		if (align == GUI_ALIGN_EXPAND) {
			return target_size;
		}
		return size;
	}
	//--------------------------------------------------------------------------
	Rect GuiAlign::makeAlignedRect(const Rect &rect, const Rect &target) const {

		Rect result;

		result.x = makeAlignedCoord(rect.x, rect.width, target.x, target.width, horizontal);
		result.y = makeAlignedCoord(rect.y, rect.height, target.y, target.height, vertical);

		result.width = makeAlignedSize(rect.width, target.width, horizontal);
		result.height = makeAlignedSize(rect.height, target.height, vertical);

		return result;

	}
	//--------------------------------------------------------------------------
	Rect GuiAlign::makeLocalAlignedRect(const Rect &rect, const Rect &target) const {

		Rect result;

		result.x = makeLocalAlignedCoord(rect.x, rect.width, target.width, horizontal);
		result.y = makeLocalAlignedCoord(rect.y, rect.height, target.height, vertical);

		result.width = makeAlignedSize(rect.width, target.width, horizontal);
		result.height = makeAlignedSize(rect.height, target.height, vertical);

		return result;

	}
	//--------------------------------------------------------------------------
		engine = engine_;
	}
	void GuiRender::begin() {
		setViewport(0, 0, engine->getPlatform()->getWidth(), engine->getPlatform()->getHeight());
	void GuiRender::end() {
		render->setViewport(0, 0, engine->getPlatform()->getWidth(), engine->getPlatform()->getHeight());
	void GuiRender::setSkin(const GuiSkin &skin_) {
	void GuiRender::setViewport(int x, int y, int width, int height, bool clip) {
		//if (clip == true) {
			render->setViewport(x, engine->getPlatform()->getHeight() - y - height, width, height);
			viewport.x = x;
			render->setViewport(0, 0, engine->getPlatform()->getWidth(), engine->getPlatform()->getHeight());
	}

	//--------------------------------------------------------------------------
	void GuiRender::setViewport(const Rect &rect, bool clip) {
		setViewport(rect.x, rect.y, rect.width, rect.height, clip);


	const Rect &GuiRender::getViewport() const {
		return viewport;
	}

	//--------------------------------------------------------------------------

	Rect GuiRender::getClientRect(const Rect &rect, GuiRectType type) {
		return Rect(rect.x + 8, rect.y + 8, rect.width - 16, rect.height - 16);
	}

	void GuiRender::drawRect(const Rect &rect, GuiRectType type) {

		Rect r = rect;
		render->bindTexture(texture, 0);

		int s = 0;

		switch (type) {
			case GUI_RECT_FRAME:
				render->drawRect(rect.x, rect.y, rect.width, rect.height);
				return;
			case GUI_RECT_SOLID:
				render->drawFillRect(rect.x, rect.y, rect.width, rect.height);
				return;
			case GUI_RECT_BUTTON_DOWN: s = 3; break;
			case GUI_RECT_WINDOW: s = 24; break;
			default:;
		}


	//--------------------------------------------------------------------------
	void GuiRender::drawText(const Rect &rect, const char *text, const GuiAlign &align) {

		const FontRef &font = skin->getFont();
		render->bindFont(font, true);
		//render->setFontSize(36);

		Rect text_rect = align.makeAlignedRect(getTextRect(text), rect);
		render->drawText2d(text_rect.x + viewport.x, text_rect.y + viewport.y, text);

	}

	//--------------------------------------------------------------------------
	Rect GuiRender::getTextRect(const char *text, int start, int count) {
		const FontRef &font = skin->getFont();
		render->bindFont(font);

		return Rect(0, 0, render->getTextWidth(text, start, count), render->getTextHeight());
	}
	//--------------------------------------------------------------------------
	void GuiRender::drawImage(const Rect &rect, const TextureRef &image, const GuiAlign &align, int w_frames, int h_frames, int image_index) {
		if (w_frames > 1 || h_frames > 1) {
			render->setTextureMatrixFrame(image_index, w_frames, h_frames);
		}

		Rect image_rect = align.makeAlignedRect(getImageRect(image, w_frames, h_frames), rect);
		render->drawImageScaled(image_rect.x + viewport.x, image_rect.y + viewport.y, image_rect.width, image_rect.height, image);

		if (w_frames > 1 || h_frames > 1) {
			render->setTextureMatrix(mat4());
		}
	}
	//--------------------------------------------------------------------------
	Rect GuiRender::getImageRect(const TextureRef &image, int w_frames, int h_frames) const {
		return Rect(0, 0, floor(float(image->getWidth()) / float(w_frames)), floor(float(image->getHeight()) / float(h_frames)));
	}
	//--------------------------------------------------------------------------
		render->setColor(color, alpha);
	}
	//--------------------------------------------------------------------------

		engine = engine_;
		assert(engine != NULL);

		root = create("root");
		assert(root != NULL);
		gui_render = new GuiRender(engine);

		skin.image.load("GUI/gui_button.png");
		skin.font.load("Core/Fonts/ms_sans_serif_8.xml_font");
		//skin.font.load("/Core/Fonts/fixed_sys.xml_font");
		//skin.font.load("/Core/Fonts/ms_sans_serif_24.xml_font");

		focus = NULL;


	Gui::~Gui() {

	GuiSkin &Gui::getSkin() {

	const GuiSkin &Gui::getSkin() const {

	GuiNode *Gui::create(const char *id) {

	GuiRender *Gui::getRender() {
	//--------------------------------------------------------------------------

	Engine *Gui::getEngine() {
	//--------------------------------------------------------------------------

	void Gui::addChild(GuiNode *child) {
		root->addChild(child);
	}

	//--------------------------------------------------------------------------

	void Gui::render() const {

		if (root == NULL) return;
		gui_render->begin();
		gui_render->setSkin(skin);
		root->setRect(gui_render->getViewport());
		root->render();
		gui_render->end();
	}

	void Gui::update(float dt) {

		if (root == NULL) return;

		root->update(dt);

	void Gui::redraw() {

		if (root == NULL) return;

		root->redraw(true);

	void Gui::onMouseMove(int x, int y, int b) {
		root->mouseMove(x, y, b);
	}
	//--------------------------------------------------------------------------

	void Gui::onMouseDown(int x, int y, int b) {
		root->mouseDown(x, y, b);
	}
	//--------------------------------------------------------------------------

		root->mouseDoubleClick(x, y, b);
	}
	//--------------------------------------------------------------------------

	void Gui::onMouseUp(int x, int y, int b) {
		root->mouseUp(x, y, b);
	}
	//--------------------------------------------------------------------------

	void Gui::onResize(int w, int h) {
		root->setRect(Rect(0, 0, w, h));
	}

	//--------------------------------------------------------------------------

	void Gui::onKeyDown(int key) {
		if (focus == NULL) return;
		focus->keyDown(key);
	}

	//--------------------------------------------------------------------------

	void Gui::onKeyRepeat(int key) {
		if (focus == NULL) return;
		focus->keyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void Gui::onKeyUp(int key) {
		if (focus == NULL) return;
		focus->keyUp(key);
	}

	//--------------------------------------------------------------------------

	void Gui::onKeyChar(char key) {
		if (focus == NULL) return;
		focus->keyChar(key);
	}

	//--------------------------------------------------------------------------

	GuiNode *Gui::getFocus() {
		return focus;
	}

	//--------------------------------------------------------------------------

	void Gui::setFocus(GuiNode *node) {
		focus = node;
	}
	//--------------------------------------------------------------------------
