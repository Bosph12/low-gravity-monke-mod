#include "LowGravityMonkeWatchView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/MonkeWatch.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "UnityEngine/Vector3.hpp"

DEFINE_TYPE(LowGravityMonke::LowGravityMonkeWatchView);

using namespace GorillaUI;
using namespace UnityEngine;

extern bool moddedRoom;

namespace LowGravityMonke
{
    void LowGravityMonkeWatchView::Awake()
    {
        toggleHandler = new UIToggleInputHandler(EKeyboardKey::Enter, EKeyboardKey::Enter, true);
    }

    void LowGravityMonkeWatchView::DidActivate(bool firstActivation)
    {
        std::function<void(bool)> fun = std::bind(&LowGravityMonkeWatchView::OnToggle, this, std::placeholders::_1);
        toggleHandler->toggleCallback = fun;
        Redraw();
    }

    void LowGravityMonkeWatchView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawBody();

        watch->Redraw();
    }

    void LowGravityMonkeWatchView::DrawHeader()
    {
        text += "<color=#136CFF>== <color=#FF2F3C>Low Gravity Monke</color> ==</color>\n";
    }

    void LowGravityMonkeWatchView::DrawBody()
    {
        text += "\nLow Gravity Monke is:\n\n  ";
        text += config.enabled ? "<color=#00ff00>> Enabled</color>" : "<color=#ff0000>> Disabled</color>";

        if (config.enabled && !moddedRoom)
        {
            text += "\n\nBut is disabled\ndue to not being in\na private room\n";
        }
    }

    void LowGravityMonkeWatchView::OnToggle(bool value)
    {
        config.enabled = value;

        SaveConfig();
    }

    void LowGravityMonkeWatchView::OnKeyPressed(int key)
    {
        toggleHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}