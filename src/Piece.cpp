#include "Piece.h"
#include "GameConfig.h"

Piece::Piece(PieceColor color, PieceType type) : _eating(false), _moving(false), _color(color), _type(type)
{
    _view = this;

    // set pilot to center of sprite
    Vector2 center = _view->getSize() / 2;
    // round center to avoid blurred image
    center.x = int(center.x);
    center.y = int(center.y);
    _view->setAnchorInPixels(center);
}

void Piece::move(const Point &pos)
{
    unselect();
    _moving = true; // Блокируем фигуру от повторных кликов

    // Создаем анимацию перемещения
    Point viewPos = Point(pos.x * PieceSize.x + (PieceSize.x / 2), pos.y * PieceSize.y + (PieceSize.y / 2));
    spTween tween = _view->addTween(Actor::TweenPosition(viewPos), 500, 1, false, 0, Tween::EASE::ease_outSin);

    // Когда доедет — вызываем метод завершения
    tween->setDoneCallback(CLOSURE(this, &Piece::moved));
    _pos = pos;
}

void Piece::moved(Event *)
{
    _moving = false;
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
    _view->detach();
}

void Piece::select()
{
    _view->addTween(Actor::TweenScale(1.1), 1000, -1, true);
    _view->setColor(Color(150, 255, 150, 255));
}

void Piece::unselect()
{
    _view->removeTweens();
    _view->setScale(1);
    _view->setColor(Color());
}
