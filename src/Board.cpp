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

void Board::placePiece(PieceColor pColor, PieceType pType, Point pos)
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

    // Центрируем точку привязки фигуры (чтобы координаты указывали на центр картинки, а не на левый верхний угол)
    newPiece->setAnchor(Vector2(0.5f, 0.5f));

    // Вычисляем позицию в пикселях.
    // Центр клетки: индекс * размер_клетки + половина_клетки
    newPiece->setPosition(pos.x * PieceSize.x + (PieceSize.x / 2), pos.y * PieceSize.y + (PieceSize.y / 2));

    newPiece->setPos(pos);

    // Добавляем фигуру как дочерний элемент ДОСКИ (важно: координаты будут считаться от угла доски)
    _view->addChild(newPiece);

    // Записываем фигуру в нашу логическую сетку
    _field[(int)pos.x][(int)pos.y] = newPiece;
}

void Board::SetupBoard()
{
    _field.assign(8, std::vector<spPiece>(8, nullptr));

    // Очищаем логический массив (на всякий случай)
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            _field[x][y] = nullptr;
        }
    }

    // Расставляем ПЕШКИ циклом
    for (int x = 0; x < 8; ++x)
    {
        placePiece(PieceColor::black, PieceType::pawn, Point(x, 1));
        placePiece(PieceColor::white, PieceType::pawn, Point(x, 6));
    }

    // Расставляем ЧЕРНЫХ офицеров (Y = 0)
    placePiece(PieceColor::white, PieceType::rook, Point(0, 7));
    placePiece(PieceColor::white, PieceType::knight, Point(1, 7));
    placePiece(PieceColor::white, PieceType::bishop, Point(2, 7));
    placePiece(PieceColor::white, PieceType::queen, Point(3, 7));
    placePiece(PieceColor::white, PieceType::king, Point(4, 7));
    placePiece(PieceColor::white, PieceType::bishop, Point(5, 7));
    placePiece(PieceColor::white, PieceType::knight, Point(6, 7));
    placePiece(PieceColor::white, PieceType::rook, Point(7, 7));

    // Расставляем БЕЛЫХ офицеров (Y = 7));
    placePiece(PieceColor::black, PieceType::rook, Point(0, 0));
    placePiece(PieceColor::black, PieceType::knight, Point(1, 0));
    placePiece(PieceColor::black, PieceType::bishop, Point(2, 0));
    placePiece(PieceColor::black, PieceType::queen, Point(3, 0));
    placePiece(PieceColor::black, PieceType::king, Point(4, 0));
    placePiece(PieceColor::black, PieceType::bishop, Point(5, 0));
    placePiece(PieceColor::black, PieceType::knight, Point(6, 0));
    placePiece(PieceColor::black, PieceType::rook, Point(7, 0));
}

void Board::init()
{
    placeBoard();

    _view = new Sprite;

    _view->setSize(_board->getSize());

    _view->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Board::touched));
    _view->setTouchChildrenEnabled(true);

    _view->setCallbackDoUpdate(CLOSURE(this, &Board::update));

    getStage()->addChild(_view);

    SetupBoard();
}

void Board::update(const UpdateState &us)
{
}

void Board::makeMove(Point target, bool isAttack)
{
    Point curPos = selectedPiece->get()->getPos();
    if (isAttack)
    {
        _field[target.x][target.y].get()->beingEaten();
    }
    selectedPiece->get()->move(target);
    _field[target.x][target.y] = *selectedPiece;
    _field[curPos.x][curPos.y] = nullptr;
    selectedPiece = nullptr;
    _hasSelectedPiece = false;
}

void Board::touched(Event *event)
{
    TouchEvent *te = safeCast<TouchEvent *>(event);
    Vector2 pos = te->localPosition;
    Point clickPos;
    clickPos.x = (int)(pos.x / PieceSize.x);
    clickPos.y = (int)(pos.y / PieceSize.y);
    spPiece *clickPiece = &(_field[clickPos.x][clickPos.y]);

    if (_hasSelectedPiece)
    {
        if (selectedPiece == clickPiece)
        {
            // logs::messageln("Second Click!");
            clickPiece->get()->unselect();
            _hasSelectedPiece = false;
        }
        else
        {
            bool makeAnAttack = clickPiece->get() != nullptr;
            logs::messageln("Attack: %d!", makeAnAttack);
            if (isValidMove(selectedPiece, clickPos, makeAnAttack))
            {
                logs::messageln("VALID Move!");
                makeMove(clickPos, makeAnAttack);
            }
            else
            {
                logs::messageln("Invalid Move!");
            }
        }
    }
    else
    {
        if (*clickPiece)
        {
            _hasSelectedPiece = true;
            selectedPiece = clickPiece;
            clickPiece->get()->select();
        }
        else
        {
            logs::messageln("Empty Cell");
        }
    }

    if (*clickPiece)
        logs::messageln("%d - %d: %d", clickPos.x, clickPos.y, (int)clickPiece->get()->getType());

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
}

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