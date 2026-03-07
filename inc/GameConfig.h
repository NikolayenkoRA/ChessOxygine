#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

extern Resources res;

const Vector2 PieceSize = Vector2(100, 100);
const Vector2 BoardSize = Vector2(800, 800);
const Vector2 Window = Vector2(1920, 1080);

void game_preinit();
void game_init();
void game_destroy();
void game_update();