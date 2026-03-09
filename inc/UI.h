#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

extern Resources res;
extern const int fontSize;

class SceneUI
{
private:
    bool _hasUI;
    spTextField _statusText;
    spColorRectSprite _statusBg;
    int _fontSize = fontSize;

public:
    SceneUI();
    void showFloatingMessage(const std::string &text, oxygine::Color color);
    void tweenFinished(Event *);
};