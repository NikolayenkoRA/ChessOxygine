#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

enum class PieceColor : bool
{
    white,
    black
};

enum class PieceType : int
{
    rook,
    knight,
    bishop,
    queen,
    king,
    pawn
};

DECLARE_SMART(Piece, spPiece);

class Piece : public Sprite
{
public:
    Piece(PieceColor color, PieceType type);

    spActor getView() const { return _view; }
    PieceType getType() const { return _type; }
    PieceColor getColor() const { return _color; }

    bool isMoving() const { return _moving; }
    bool isEating() const { return _eating; }

    void move(const Point &pos);
    void beingEaten();
    void select();
    void unselect();
    void setPos(Point newPos) { _pos = newPos; }
    Point getPos() { return _pos; }

private:
    void eaten(Event *);
    void moved(Event *);

    bool _moving;
    bool _eating;
    spSprite _view;

    Point _pos;

    PieceColor _color;
    PieceType _type;
};