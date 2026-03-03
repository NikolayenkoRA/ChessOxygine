#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(ChessPiece, spChessPiece);

class ChessPiece : public Sprite {
public:
    enum Side { White, Black };
    enum Type { Pawn, Rook, Knight, Bishop, Queen, King };

    ChessPiece(Side side, Type type);

    // Логические координаты на доске (0-7)
    int cellX, cellY;
    Side side;
    Type type;

    // Плавное перемещение в новую клетку
    void moveTo(int x, int y);
    
    // Плавное исчезновение при поедании
    void die();
};
