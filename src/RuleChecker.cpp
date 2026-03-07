#include "RuleChecker.h"

bool isValidMove(spPiece *selected, Point target, bool isAttack)
{
    Point pPos = selected->get()->getPos();
    PieceColor pColor = selected->get()->getColor();
    PieceType pType = selected->get()->getType();
    Vector2 movingVector = target - pPos;
    if (pColor == PieceColor::white)
        movingVector.y *= (-1);
    logs::messageln("Pos: (%d; %d)", pPos.x, pPos.y);
    logs::messageln("Target: (%d; %d)", target.x, target.y);
    logs::messageln("Vector: (%f; %f)", movingVector.x, movingVector.y);

    switch (pType)
    {
    case PieceType::pawn:
        return checkPawn(pPos, target, pColor, movingVector, isAttack);
    default:
        return false;
    }
}

bool checkPawn(Point pPos, Point target, PieceColor pColor, Vector2 movingVector, bool isAttack)
{
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
