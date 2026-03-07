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

    spActor getView() const;
    PieceType getType() const;

    bool isMoving() const { return _moving; }
    bool isEating() const { return _eating; }

    void move(const Vector2 &pos);
    void beingEaten();
    void select();
    void unselect();

private:
    void eaten(Event *);
    void moved(Event *);

    bool _moving;
    bool _moved;
    bool _eating;
    bool _eaten;
    spSprite _view;

    PieceColor _color;
    PieceType _type;
};