#pragma once

#include <logger.h>

namespace logging {

    const uintptr_t CHAT_FUNC_OFFSET = 0x6B060;

    const typedef int (__cdecl* _chatLog)(char* format, ...);

    class ACChatLogger : public Logger {

    public:

        explicit ACChatLogger(const uintptr_t& baseAddress) : baseAddress{ baseAddress } {
            chatLog = (_chatLog) (baseAddress + CHAT_FUNC_OFFSET);
        }

        ~ACChatLogger() override = default;

        void debug_log(const TCHAR* formatString, ...) const override;

    private:
        const uintptr_t& baseAddress;
        _chatLog chatLog;
    };

}