//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#include "Nutmeg.h"
#include <memory>

//------------------------------------------------------------------------------

#include "Game.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	// ������ ��� ���������� �������� ��������� �� Entity
	// � ��������� ������
	// �����, ��� ����� ��� ����������������, ������ ���������� ������������� (��. ����)
	// ����� ��� ���������� ������� ��� ���� ����� � �������
	// �� 5�� ������� � ������� ��� ����� ���������� �������������
	// ����� ��� ����� ��������� �����, ������� ����� ������
	// � �������� ���� EntityNode � ������ ����������
	class EntityPlayer : public Entity {

		PhysicsNode *body;
		CameraNode *camera;
		Node *ground;
		bool jumping;
		Line ray;

	protected:

		// ���������� ��� �������� ���������� Entity.
		// ����� ��� ����� �������� ���� �� ����� ������ Entity
		virtual void onCreate() {

			// �������� ���������� ������
			body = node->getEntityNode <PhysicsNode> ("player_body");

			// �������� ������
			camera = node->getEntityNode <CameraNode> ("player_camera");
			camera->setTarget(body);

		}

		// ���������� ����� �������� ���� Entity ������
		// ����� �� ����� �������� ������ Entity ������, ����� � ���� �����������������.
		virtual void onAfterCreate() {

			// ������������� �������� Entity
			level->setActiveEntity(this);

		}

		// ���������� ��� ����������� ���������� Entity
		virtual void onDestroy() {

		}

		// ��� ������� ���������� ��� ��������� Entity (setActiveEntity)
		virtual void onActivate() {
			scene->setActiveCamera(camera);
		}

		// ���� �������� �������, ���� ������ �������
		// ��������, ���� ��� �������� �� ������� level->setActiveEntity(this)

		//virtual void onMouseDown(int x, int y, int b) { }
		//virtual void onMouseMove(int x, int y) { }
		virtual void onKeyDown(int key) {

			// ������������ ��������� ������� �� tab
			if (key == KEY_TAB) {
				int index = level->findEntity(this);
				index = (index + 1) % level->getEntitiesCount();
				level->setActiveEntity(&level->getEntity(index));
			}

			// ������
			if (key == KEY_W || key == KEY_UP) jump();

		}
		//virtual void onMouseUp(int x, int y, int b) { }
		//virtual void onKeyUp(int key) { }
		//virtual void onKeyRepeat(int key) { }
		//virtual void onKeyChar(char c) { }

		// ��� ������� ���������� ������ ���� ��� ��������� Entity
		virtual void onControl(AbstractPlatform *platform) {
			if (platform->keyHold(KEY_LEFT) || platform->keyHold(KEY_A)) moveLeft();
			if (platform->keyHold(KEY_RIGHT) || platform->keyHold(KEY_D)) moveRight();
		}

		// ��� ������� ���������� ������ ���� � ����� ����� ������ ���������
		// ��������, ��������� ������-������ Entity
		virtual bool onUpdate(float dt) {

			Node *old_ground = ground;
			TracePoint tp;
			ray.src = getPos();
			ray.dst = ray.src + vec3(0.0f, 0.0f, -1.0f) * body->getScale(true).z / 1.5f;
			ground = scene->trace(ray, tp, true, true, NODE_PHYSICS);
			if (old_ground == NULL && ground != NULL) jumping = false;

			return true;	// ���� ������� false ������ �����������
		}

		// ����� �� ����� �������� �� ������ ������ ���, ����������� � Entity.
		// ��������, ���������� �������� � ����� �������� ��� ������-��������
		// � �������� � ����� �������� ��� ������������� ��������.
		// ���������� ��� ��������� Entity
		virtual void onRender2d(AbstractRender *render) {
			render->drawText2d(render->getWidth() - 220, render->getHeight() - 40, format("entity index: %d", level->findEntity(this)));
			if (ground != NULL) {
				render->drawText2d(render->getWidth() - 220, render->getHeight() - 70, format("gnd: %s", ground->getName()));
			}
			render->drawText2d(render->getWidth() - 220, render->getHeight() - 100, format("jmp: %s", (jumping) ? "true" : "false"));
		}

		virtual void onRenderDebug(AbstractRender *render) {
			render->drawLine(ray);
		}

	public:

		EntityPlayer() {
			body = NULL;
			ground = NULL;
			camera = NULL;
			jumping = true;
		}

		~EntityPlayer() {

		}

		void moveLeft() {
			body->getBody().setForce(vec3(0.0, -30.0f, 0.0f));
			//body->getBody().setTorque(vec3(10.0, 0.0f, 0.0f));
		}

		void moveRight() {
			body->getBody().setForce(vec3(0.0, 30.0f, 0.0f));
			//body->getBody().setTorque(vec3(-10.0, 0.0f, 0.0f));
		}

		void jump() {
			if (ground == NULL || jumping == true) return;
			body->getBody().addVelocity(vec3(0.0, 0.0f, 7.0f));
			jumping = true;
		}

		vec3 getPos() const {
			return body->getPos(true);
		}

	};

	// ����������� �� Level
	// ������������ �� id
	// id ��������� � ����� �������� ������� xml_game
	class Level0 : public Level {


		Array <EntityPlayer> players;											// ��� ������ ������ (��. ����������� Level0)
		EntityPlayer *main_player;												// ������� �����

	protected:

		// ���������� ����� �������� ���� Entity
		virtual void onCreate() {

			// �������� �������� ������, ������������ � ���� � ��������� �� ������
			// �� ����� ���� ������ ��� ������ :)
			// �� ����� ���� ������ getEntity()
			main_player = get <EntityPlayer> ("main_player");

			// �������� �� ���� Entity
			for (int i=0; i<getEntitiesCount(); i++) {
				if (Str(getEntity(i).getName()) == "main_player") continue;		// ���� ������� ����� - ���� �����
				if (Str(getEntity(i).getType()) != "EntityPlayer") continue;	// ���� ��� ������ �� ����� - ���� �����
				EntityPlayer *player = &get <EntityPlayer> (i);					// �������� ������
				players.append(player);											// ��������� ������
			}

			setActiveEntity(main_player);										// ������ �������� ������ ��������

		}

		// ������
		virtual void onUpdate(float dt) {

			// �������� �� ���� �������
			for (int i=0; i<players.count(); i++) {

				// ����� ���������� �� �������� ������ �� �������� ���������
				if (distance(main_player->getPos(), players[i].getPos()) < 1.5f) {
					// ������� �������� ������
					players[i].jump();
				}
			}

			// ������, ��� �� ����� ���, ��� ���� ���������� ������� �������
			// � ������� - �� �� ������ ������� � ������

		}

	public:

		// ��� ����� �� ������� �������, ��� �� ������ ���� �������� ���������
		// �� ���� �� ������ ������������� ��������� ��� ��������
		Level0() : players(false) {

		}

	};

	//--------------------------------------------------------------------------
	//
	// class EntitySampleApp
	//
	//--------------------------------------------------------------------------

	class EntitySampleApp : public Application, ResourceEventListener {

		//----------------------------------------------------------------------
		// ����� ������������ ������� Entity, ����� ������� �������� ������ Game
		Game *game;

		bool debug;

		FontRef font;

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		EntitySampleApp() {

			debug = false;

		}

		//----------------------------------------------------------------------

		virtual void onResourceLoadDelayed(const ResourceItemBase &res, int loaded_count, int loaded_size, int total_count, int total_size) {
			//engine->redraw();
			console->message("%.2f %%", float(loaded_size) / float(total_size) * 100.0f);
		}

		//----------------------------------------------------------------------

		virtual void onResourceReload(const char *type, const char *name) {
			console->message(format("Reloading <%s> \"%s\"", type, name));
			console->echo(format("Reloading <%s> \"%s\"", type, name));
		}

		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv) {

			//------------------------------------------------------------------
			// common
			//------------------------------------------------------------------

			resource_manager->beginDelayedLoading();

			Log::open("engine.log");											// ��������� ������ � ���

			platform->setTitle("EntityTest");									// ������������� ���������
			platform->setUpdateFPS(0.0f);										// ������ ��� update 0 - ���������� ������ ����

			font.load("/Core/Fonts/ms_sans_serif_24.xml_font");					// ��������� �����
			render->bindFont(font);												// ������������ �����

			// ������ ������� ������ ���������� ������� �� ��������� ��������
			// (� ������� ����� ����� ������ �������� ��������)
			resource_manager->setEventListener(this);

			platform->setSystemCursor(false);									// ������������� ������ ������ ������ ����������

			engine->setResizingRedraw(true);										// ���������� ���������� ���� ��� ��������������

			//------------------------------------------------------------------
			// entities
			//------------------------------------------------------------------

			game = new Game(engine);											// ������� ��������� ����� ����
			game->addEntityLogic <EntityPlayer> ("EntityPlayer");				// ������������ ������ ��� Entity
			game->addLevelLogic <Level0> ("Level0");							// ������������ ������ ��� Level

			game->load("../Resource/Game/sample.xml_game");						// ��������� ������������ ������� �������
			game->startLevel(0);												// ��������� ������ �������

			//------------------------------------------------------------------

			resource_manager->beginDelayedLoading();

		}

		//----------------------------------------------------------------------

		virtual void onShutdown() {

		}

		//----------------------------------------------------------------------

		virtual void onRender() {


			render->begin();													// �������� ���������
			render->clear(true, true);											// ������� �����

			game->render(render);												// ������ ����

			render->bindMaterial(Material());
			game->renderDebug(render);

			render->begin2d(-1, -1);											// �������� ��������� 2d


			// ������ ���������� ����������
			int top = 0;
			if (console->isActive()) top = console->getHeight(render);

			render->bindFont(font);
			game->render2d(render);
			render->setFontSize(24);
			render->setColor(vec3(1.0f, 1.0f, 1.0f));
			render->drawText2d(10, 10 + top, format("framerate : %.2f fps", platform->getFPS()));
			render->drawText2d(10, 30 + top, format("update : %.2f ms", platform->getUpdateTime()));
			if (game->getActiveLevel() != NULL) render->drawText2d(10, 50 + top, format("scene nodes : %d", game->getActiveLevel()->getScene()->getNodesCount()));

			render->end2d();													// ����������� ��������� 2d

			render->end();														// ����������� ���������

		}

		//----------------------------------------------------------------------

		virtual void onUpdate(float dt) {

			game->update(dt);													// �������� update ����

		}

		//----------------------------------------------------------------------

		virtual void onResize(int w, int h) {

			render->setResolution(w, h);

			if (h <= 0) return;

		}

		//----------------------------------------------------------------------

		virtual void onKeyDown(int key) {

			if (platform->keyHold(KEY_CONTROL)) {

				switch(key) {
					case KEY_1: platform->setVideoMode(VideoMode(320, 240, 32), platform->isFullscreen()); break;
					case KEY_2: platform->setVideoMode(VideoMode(400, 300, 32), platform->isFullscreen()); break;
					case KEY_3: platform->setVideoMode(VideoMode(512, 384, 32), platform->isFullscreen()); break;
					case KEY_4: platform->setVideoMode(VideoMode(640, 480, 32), platform->isFullscreen()); break;
					case KEY_5: platform->setVideoMode(VideoMode(800, 600, 32), platform->isFullscreen()); break;
					case KEY_6: platform->setVideoMode(VideoMode(1024, 768, 32), platform->isFullscreen()); break;
					case KEY_7: platform->setVideoMode(VideoMode(1280, 1024, 32), platform->isFullscreen()); break;
					case KEY_8: platform->setVideoMode(VideoMode(1680, 1050, 32), platform->isFullscreen()); break;
					case KEY_9: platform->setVideoMode(VideoMode(1366, 768, 32), platform->isFullscreen()); break;
					case KEY_0: platform->setVideoMode(VideoMode(1920, 1080, 32), platform->isFullscreen()); break;
				}

				if (key == KEY_ENTER) {
					platform->setVideoMode(platform->getCurrentVideoMode(), !platform->isFullscreen());
				}

			} else {

				if (key == KEY_TAB) {
					profiler->setVisible(!profiler->isVisible());
				}

				if (key == KEY_L) {
//					use_fake_aa = !use_fake_aa;
				}

				if (key == KEY_BACKSPACE) {
					game->startLevel(game->getActiveLevelIndex());
					return;
				}

				game->keyDown(key);

			}

		}

		//----------------------------------------------------------------------

		virtual void onKeyUp(int key) {
			game->keyUp(key);
		}

		//----------------------------------------------------------------------

		virtual void onKeyRepeat(int key) {
			game->keyRepeat(key);
		}

		//----------------------------------------------------------------------

		virtual void onKeyChar(char c) {
			game->keyChar(c);
		}

		//----------------------------------------------------------------------

		virtual void onMouseDown(int x, int y, int b) {

			game->mouseDown(x, y, b);

		}

		//----------------------------------------------------------------------

		virtual void onMouseUp(int x, int y, int b) {
			game->mouseUp(x, y, b);
		}

		//----------------------------------------------------------------------

		virtual void onMouseMove(int x, int y) {
			if (platform->getWidth() == 0 || platform->getHeight() == 0) return;
			game->mouseMove(x, y);
		}

		//----------------------------------------------------------------------

		virtual void onError(const char *) {}

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	int engineMain(int argc, const char **argv) {

		Engine engine;
		engine.loadSubsystems();

		engine.selectSubsystemCoreId();
		engine.selectSubsystemRenderId();
		engine.selectSubsystemAudioId();
		engine.selectSubsystemPhysicsId();

		EntitySampleApp *application = new EntitySampleApp();

		return engine.execute(application, argc, argv);
	}
}

//------------------------------------------------------------------------------


