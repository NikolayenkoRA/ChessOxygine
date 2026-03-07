#include "Board.h"
#include "GameConfig.h"
#include "RuleChecker.h"

Board::Board()
{
}

Vector2 getPos(const Point &p)
{
    Vector2 pos;
    pos.x = p.x * PieceSize.x;
    pos.y = p.y * PieceSize.y;
    pos += PieceSize / 2;

    return pos;
}

void Board::placeBoard()
{
    _board = new Sprite;

    _board->setSize(BoardSize.x, BoardSize.y);
    _board->setResAnim(res.getResAnim("board"));
    _board->attachTo(getStage());

    // set pilot to center of sprite
    Vector2 center = _board->getSize() / 2;
    // round center to avoid blurred image
    center.x = int(center.x);
    center.y = int(center.y);
    _board->setAnchorInPixels(center);
    _board->setPosition(Vector2(Window.x / 2, Window.y / 2));
}

spPiece Board::placePiece(PieceColor pColor, PieceType pType, cell pos)
{
    spPiece newPiece = new Piece(pColor, pType);
    // Формируем имя ресурса для запроса из XML (например, "white_rook")
    std::string sideStr = (pColor == PieceColor::white) ? "white" : "black";
    std::string typeStr;
    switch (pType)
    {
    case PieceType::pawn:
        typeStr = "pawn";
        break;
    case PieceType::rook:
        typeStr = "rook";
        break;
    case PieceType::knight:
        typeStr = "knight";
        break;
    case PieceType::bishop:
        typeStr = "bishop";
        break;
    case PieceType::queen:
        typeStr = "queen";
        break;
    case PieceType::king:
        typeStr = "king";
        break;
    }

    // Применяем картинку из атласа
    newPiece->setResAnim(res.getResAnim(sideStr + "_" + typeStr));
}

void Board::SetupBoard()
{
}

void Board::init()
{
    placeBoard();

    _view = new Sprite;

    _field.resize(64);

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            _field[x + y * 8].coordinate = Point(x, y);
        }
    }

    _view->setSize(8 * PieceSize.x, 8 * PieceSize.y);

    _view->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Board::touched));
    _view->setTouchChildrenEnabled(false);

    _view->setCallbackDoUpdate(CLOSURE(this, &Board::update));

    SetupBoard();
}

void Board::update(const UpdateState &us)
{
}

void Board::touched(Event *event)
{
}
// void Board::touched(Event *event)
// {
//     TouchEvent *te = safeCast<TouchEvent *>(event);
//     Vector2 pos = te->localPosition;
//     // logs::messageln("%d - %d: %.2f, %.2f", event->target->getObjectID(), event->currentTarget->getObjectID(), pos.x, pos.y);
//     Point spacePos;
//     spacePos.x = (int)(pos.x / PieceSize.x);
//     spacePos.y = (int)(pos.y / PieceSize.y);

//     space *sp = getSpace(spacePos);

//     if (_selected)
//     {
//         _selected->piece->unselect();
//         if (sp)
//         {
//             if (isValidMove(_selected, sp))
//             {
//                 spTween tween = makeMove(*_selected, *sp);
//                 tween->setDoneCallback(CLOSURE(this, &Board::swapped));
//             }
//         }

//         _selected = 0;
//     }
//     else
//     {
//         _selected = sp;
//         if (sp)
//             sp->piece->select();
//     }
// }

spActor Board::getView()
{
    return _view;
}

void Board::free()
{
    _field.clear();
    _view->detach();
    _view = 0;
}