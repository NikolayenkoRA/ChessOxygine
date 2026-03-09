#include "UI.h"

SceneUI::SceneUI()
{
}

void SceneUI::showFloatingMessage(const std::string &text, oxygine::Color color)
{
    if (!_hasUI)
    {
        _hasUI = true;

        // background
        _statusBg = new ColorRectSprite();

        _statusBg->setColor(Color(0, 0, 0, 150));

        _statusBg->setSize(getStage()->getWidth(), _fontSize * 2);

        _statusBg->setPosition(0, getStage()->getHeight() / 2 - _fontSize * 2);

        _statusBg->setTouchEnabled(false);
        _statusBg->setTouchChildrenEnabled(false);

        getStage()->addChild(_statusBg);

        // text
        _statusText = new TextField();

        TextStyle style;
        style.font = res.getResFont("main");
        style.color = color;
        style.vAlign = TextStyle::VALIGN_MIDDLE;
        style.hAlign = TextStyle::HALIGN_MIDDLE;
        style.multiline = true;
        style.fontSize = _fontSize;

        _statusText->setStyle(style);
        _statusText->setText(text);

        _statusText->setPosition(_statusBg->getWidth() / 2, _statusBg->getHeight() / 2);

        _statusBg->addChild(_statusText);

        spTween tween = _statusBg->addTween(Actor::TweenAlpha(0), 500, 1, false, 1000);

        tween->setDoneCallback(CLOSURE(this, &SceneUI::tweenFinished));
    }
}

void SceneUI::tweenFinished(Event *)
{
    _hasUI = false;
    _statusBg->detach();
}