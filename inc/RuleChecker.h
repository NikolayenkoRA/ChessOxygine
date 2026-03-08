#pragma once
#include "oxygine-framework.h"
#include "Piece.h"

using namespace oxygine;

DECLARE_SMART(Piece, spPiece);

bool isValidMove(spPiece *selected, Point target, bool isAttack);
bool checkPawn(Point pPos, Point target, PieceColor pColor, Vector2 movingVector, bool isAttack);
bool checkKnight(Vector2 movingVector);
