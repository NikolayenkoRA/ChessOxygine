#include "RuleChecker.h"

bool isValidMove(std::vector<std::vector<spPiece>> &field, spPiece *selected, Point target, bool isAttack)
{
    Point pPos = selected->get()->getPos();
    PieceColor pColor = selected->get()->getColor();
    PieceType pType = selected->get()->getType();
    Vector2 movingVector = target - pPos;
    logs::messageln("Pos: (%d; %d)", pPos.x, pPos.y);
    logs::messageln("Target: (%d; %d)", target.x, target.y);
    logs::messageln("Vector: (%f; %f)", movingVector.x, movingVector.y);

    switch (pType)
    {
    case PieceType::pawn:
        return checkPawn(pPos, target, pColor, movingVector, isAttack);
    case PieceType::knight:
        return checkKnight(movingVector);
    case PieceType::rook:
        return checkRook(field, pPos, target, movingVector, isAttack);
    case PieceType::bishop:
        return checkBishop(field, pPos, target, movingVector, isAttack);
    case PieceType::queen:
        return checkQueen(field, pPos, target, movingVector, isAttack);
    case PieceType::king:
        return checkKing(field, pPos, target, movingVector, isAttack);
    default:
        return false;
    }
}

bool checkKing(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack)
{
    if (movingVector.sqlength() <= 2)
    {
        return checkGeneralMove(field, pPos, target, movingVector, isAttack);
    }
    else
        return false;
}

bool checkQueen(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack)
{
    return checkGeneralMove(field, pPos, target, movingVector, isAttack);
}

bool checkBishop(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack)
{
    if (abs(movingVector.x) == abs(movingVector.y))
    {
        return checkGeneralMove(field, pPos, target, movingVector, isAttack);
    }
    else
        return false;
}

bool checkRook(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack)
{
    if (movingVector.y == 0 || movingVector.x == 0)
    {
        return checkGeneralMove(field, pPos, target, movingVector, isAttack);
    }
    else
        return false;
}

bool checkGeneralMove(std::vector<std::vector<spPiece>> &field, Point &pPos, Point &target, Vector2 &movingVector, bool &isAttack)
{
    Point shift;
    Point nextCellPos;
    spPiece *nextCell = nullptr;
    movingVector.x >= 0 ? movingVector.x > 0 ? shift.x = 1 : shift.x = 0 : shift.x = -1;
    movingVector.y >= 0 ? movingVector.y > 0 ? shift.y = 1 : shift.y = 0 : shift.y = -1;
    nextCellPos = pPos + shift;
    // Check obstacles
    while (nextCellPos != (target + shift))
    {
        logs::messageln("GM: cur: (%d, %d) target: (%d, %d)!", nextCellPos.x, nextCellPos.y, target.x, target.y);
        nextCell = &(field[nextCellPos.x][nextCellPos.y]);
        if (nextCell->get() != nullptr)
        {
            if (nextCellPos == (target) && isAttack)
                return true;
            else
            {
                logs::messageln("Obstacle!");
                return false;
            }
        }
        else
        {
            logs::messageln("No obstacle at (%d;%d)!", nextCellPos.x, nextCellPos.y);
            nextCellPos += shift;
        }
    }
    return true;
}

bool checkKnight(Vector2 movingVector)
{
    if (movingVector.sqlength() == 5)
        return true;
    else
        return false;
}

bool checkPawn(Point pPos, Point target, PieceColor pColor, Vector2 movingVector, bool isAttack)
{

    if (pColor == PieceColor::white)
        movingVector.y *= (-1);

    if (movingVector.x != 0)
    {
        if (isAttack)
        {
            if (movingVector.sqlength() == 2)
                return true;
            else
                return false;
        }
        else
        {
            logs::messageln("Not Attack!");
            return false;
        }
    }
    if (!(movingVector.y <= 2 && movingVector.y > 0))
    {
        logs::messageln("Wrong Y");
        return false;
    }
    if (movingVector.x == 0)
    {
        if (movingVector.y == 2)
        {
            if ((pPos.y == 1 && pColor == PieceColor::black) || (pPos.y == 6 && pColor == PieceColor::white))
                if (isAttack)
                    return false;
                else
                    return true;
            else
            {
                logs::messageln("Long Move");
                return false;
            }
        }
        else
        {
            if (isAttack)
                return false;
            else
                return true;
        }
    }
    else
        return false;
}
