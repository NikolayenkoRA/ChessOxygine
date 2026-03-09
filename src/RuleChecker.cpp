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
    default:
        return false;
    }
}

bool checkRook(std::vector<std::vector<spPiece>> &field, Point pPos, Point target, Vector2 movingVector, bool isAttack)
{
    int shift = 0;
    int nextCellPos = 0;
    spPiece *nextCell = nullptr;
    if (movingVector.y == 0)
    {
        logs::messageln("Rook: moving X!");
        movingVector.x > 0 ? shift = 1 : shift = -1;
        nextCellPos = pPos.x + shift;
        // Check obstacles
        while (nextCellPos != (target.x + shift))
        {
            logs::messageln("Rook: moving X: cur: %d target: %d!", nextCellPos, target.x);
            nextCell = &(field[nextCellPos][pPos.y]);
            if (nextCell->get() != nullptr)
            {
                if (nextCellPos == (target.x) && isAttack)
                    return true;
                else
                {
                    logs::messageln("Obstacle!");
                    return false;
                }
            }
            else
            {
                logs::messageln("No obstacle at (%d;%d)!", pPos.x, nextCellPos);
                nextCellPos += shift;
            }
        }
        return true;
    }
    else if (movingVector.x == 0)
    {
        logs::messageln("Rook: moving Y!");
        movingVector.y > 0 ? shift = 1 : shift = -1;
        nextCellPos = pPos.y + shift;
        // Check obstacles
        while (nextCellPos != (target.y + shift))
        {
            logs::messageln("Rook: moving Y: cur: %d target: %d!", nextCellPos, target.y);
            nextCell = &(field[pPos.x][nextCellPos]);
            if (nextCell->get() != nullptr)
            {
                if (nextCellPos == (target.y) && isAttack)
                    return true;
                else
                {
                    logs::messageln("Obstacle!");
                    return false;
                }
            }
            else
            {
                logs::messageln("No obstacle at (%d;%d)!", nextCellPos, pPos.y);
                nextCellPos += shift;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
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
