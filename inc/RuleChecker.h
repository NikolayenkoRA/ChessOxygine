#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Piece, spPiece);

bool isValidMove(spPiece *selected, spPiece *target);
