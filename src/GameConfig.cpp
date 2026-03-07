#include "GameConfig.h"
#include "Board.h"

Board board;
core::init_desc desc;

void game_preinit()
{
    desc.title = "Oxygine Application";

    // The initial window size can be set up here on SDL builds, ignored on Mobile devices
    desc.w = Window.x;
    desc.h = Window.y;
}

void game_init()
{
    core::init(&desc);

    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage();
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();

    // load xml file with resources definition
    res.loadXML("resources.xml");

    spSprite bg = new Sprite;
    bg->setResAnim(res.getResAnim("bg"));
    bg->attachTo(getStage());
    bg->setSize(getStage()->getSize());

    board.init();

    spActor view = board.getView();
    view->setPosition(getStage()->getSize() / 2 - view->getScaledSize() / 2);
    getStage()->addChild(view);
}

void game_destroy()
{
}

void game_update()
{
}