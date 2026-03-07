#include "Piece.h"
#include "GameConfig.h"

Piece::Piece(PieceColor color, PieceType type) : _eaten(false), _eating(false), _moving(false), _color(color), _type(type)
{
    _view = new Sprite;

    char name[255];
    safe_sprintf(name, "Piece%d", _type);

    _view->setResAnim(res.getResAnim("ChessPieces"));

    // set pilot to center of sprite
    Vector2 center = _view->getSize() / 2;
    // round center to avoid blurred image
    center.x = int(center.x);
    center.y = int(center.y);
    _view->setAnchorInPixels(center);
}

void Piece::move(const Vector2 &pos)
{
    _moving = true; // Блокируем фигуру от повторных кликов

    // Создаем анимацию перемещения
    spTween tween = _view->addTween(Actor::TweenPosition(pos), 500, 1, false, 0, Tween::EASE::ease_outSin);

    // Когда доедет — вызываем метод завершения
    tween->setDoneCallback(CLOSURE(this, &Piece::moved));
}

void Piece::moved(Event *)
{
    _moved = true;
}

spActor Piece::getView() const
{
    return _view;
}

PieceType Piece::getType() const
{
    return _type;
}

void Piece::beingEaten()
{
    _eating = true;
    float alpha = 0;
    spTween tween = _view->addTween(Actor::TweenAlpha(alpha), 200);
    tween->setDoneCallback(CLOSURE(this, &Piece::eaten));
}

void Piece::eaten(Event *)
{
    _eaten = true;
    _view->detach();
}

void Piece::select()
{
    _view->addTween(Actor::TweenScale(1.1), 500, -1, true);
}

void Piece::unselect()
{
    _view->removeTweens(false);
    _view->addTween(Actor::TweenScale(1), 250);
}
