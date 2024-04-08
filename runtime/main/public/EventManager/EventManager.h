#pragma once
#include <functional>
#include <any>
#include"Utility/String/HMString.h"
#include"Utility/Map/HMUnorderedMap.h"

namespace HARMONY {

    // Delegate と MulticastDelegate のテンプレート宣言
    template <typename... Args>
    using Delegate = std::function<void(Args...)>;

    // MulticastDelegate クラスの定義
    template <typename... Args>
    class MulticastDelegate {
    public:
        void Add(Delegate<Args...> delegate) {
            delegates.Add(delegate);
        }

        void Broadcast(Args... args) {
            for (auto& delegate : delegates) {
                delegate(args...);
            }
        }
    private:
        HMArray<Delegate<Args...>> delegates;
    };


    // EventManager クラスの宣言
    class UTILITY_API EventManager {
    public:
        template <typename... Args>
        static MulticastDelegate<Args...>& GetEvent(const HMString& eventType) {
            auto& event = events[eventType];
            if (!event.has_value()) {
                event = MulticastDelegate<Args...>();
            }
            return std::any_cast<MulticastDelegate<Args...>&>(event);
        }

    private:
        static inline HMUnorderedMap<HMString, std::any> events;
    };
} /// namespace HARMONY