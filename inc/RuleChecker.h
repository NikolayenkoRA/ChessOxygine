#pragma once
#include "oxygine-framework.h"
#include "Piece.h"

using namespace oxygine;

DECLARE_SMART(Piece, spPiece);

bool isValidMove(std::vector<std::vector<spPiece>> &field, spPiece *selected, Point target, bool isAttack);
bool checkPawn(Point pPos, Point target, PieceColor pColor, Vector2 movingVector, bool isAttack);
bool checkKnight(Vector2 movingVector);
bool checkRook(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack);
bool checkBishop(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack);
bool checkGeneralMove(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack);
bool checkQueen(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack);
bool checkKing(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack);