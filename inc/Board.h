#pragma once
#include <vector>
#include "oxygine-framework.h"
#include "Piece.h"

using namespace oxygine;

extern const Vector2 BoardSize;

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
    void placePiece(PieceColor pColor, PieceType pType, Point pos);
    void SetupBoard();
    void makeMove(Point target, bool isAttack);

    bool _hasSelectedPiece;
    bool _isWhiteTurn;

    spPiece *_selectedPiece;

    std::vector<std::vector<spPiece>> _field;
};