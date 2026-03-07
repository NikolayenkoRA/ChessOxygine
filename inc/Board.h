#pragma once
#include <vector>
#include "oxygine-framework.h"
#include "Piece.h"

using namespace oxygine;

extern const Vector2 BoardSize;

struct cell
{
    Vector2 coordinate;
};

class Board
{
public:
    Board();

    void init();
    void free();
    spActor getView();

private:
    spSprite _view;
    spSprite _board;

    void touched(Event *event);
    void update(const UpdateState &us);
    void placeBoard();
    spPiece placePiece(PieceColor pColor, PieceType pType, cell pos);
    void SetupBoard();

    std::vector<cell> _field;
};