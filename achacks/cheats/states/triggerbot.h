#pragma once

#include "../../reclass/playerent.h"
#include <list>
#include <state/statemachine.h>
#include <state/state.h>

namespace cheats::states {

    class TriggerBotState : public state::State {

    public:

        typedef playerent* (__cdecl* _traceline)();

        TriggerBotState(const uintptr_t& baseAddress, playerent* pPlayer, const mem::Mem& mem, const logging::Logger& logger) :
                State(_T("TriggerBot")),
                baseAddress{ baseAddress },
                pPlayer{ pPlayer },
                logger{ logger },
                mem{ mem } {
            traceline = (_traceline) (baseAddress + TRACELINE_FUNC_OFFSET);
            lastTracelineResult = nullptr;
            lastStateWasFiring = false;
        }

        ~TriggerBotState() override {
            delete lastTracelineResult;
        };

        [[nodiscard]] bool condition() override;

        bool reach() override;

        bool reached() override;

    private:
        const uintptr_t baseAddress;
        playerent* pPlayer;
        const mem::Mem& mem;
        const logging::Logger& logger;
        playerent* lastTracelineResult;
        _traceline traceline;
        bool lastStateWasFiring;

    };

}
