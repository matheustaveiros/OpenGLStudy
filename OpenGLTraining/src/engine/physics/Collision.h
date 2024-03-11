#pragma once
#include "GameObject.h"

class Collision
{
public:
    static bool IsColliding(GameObject* a, GameObject* b)
    {
        auto aPos = a->GetTransform()->GetPosition();
        auto bPos = b->GetTransform()->GetPosition();
        auto aSize = a->GetTransform()->GetScale() * a->GetSpriteRenderer()->GetSpriteSize();
        auto bSize = b->GetTransform()->GetScale() * b->GetSpriteRenderer()->GetSpriteSize();

        const float wholeXA = aPos.x + aSize.x;
        const float wholeXB = bPos.x + bSize.x;
        const bool collisionX = wholeXA >= bPos.x && wholeXB >= aPos.x;

        const float wholeYA = aPos.y + aSize.y;
        const float wholeYB = bPos.y + bSize.y;
        const bool collisionY = wholeYA >= bPos.y && wholeYB >= aPos.y;

        return collisionX && collisionY;
    }
};