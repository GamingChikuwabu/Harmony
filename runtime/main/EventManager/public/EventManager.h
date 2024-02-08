#pragma once

#include <map>
#include <vector>
#include <functional>
#include <any>
#include <string>

namespace HARMONY {

    // Delegate と MulticastDelegate のテンプレート宣言
    template <typename... Args>
    using Delegate = std::function<void(Args...)>;

    // MulticastDelegate クラスの定義
    template <typename... Args>
    class MulticastDelegate {
    public:
        void Add(Delegate<Args...> delegate) {
            delegates.push_back(delegate);
        }

        void Broadcast(Args... args) {
            for (auto& delegate : delegates) {
                delegate(args...);
            }
        }
    private:
        std::vector<Delegate<Args...>> delegates;
    };

    // EventManager クラスの宣言
    class EVENTMANAGER_API EventManager {
    public:
        template <typename... Args>
        static MulticastDelegate<Args...>& GetEvent(const std::string& eventType) {
            auto& event = events[eventType];
            if (!event.has_value()) {
                event = MulticastDelegate<Args...>();
            }
            return std::any_cast<MulticastDelegate<Args...>&>(event);
        }

    private:
        static inline std::map<std::string, std::any> events;
    };
} /// namespace HARMONY