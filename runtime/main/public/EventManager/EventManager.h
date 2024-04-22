#pragma once
#include <functional>
#include <any>
#include<stdexcept>
#include"Utility/String/HMString.h"
#include"Utility/Map/HMUnorderedMap.h"

namespace HARMONY 
{
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

        void Clear() {
            delegates.Clear();
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

            auto type1 = event.type().name();
            auto type2 = typeid(MulticastDelegate<Args...>).name();
            if (event.type() == typeid(MulticastDelegate<Args...>)) {
                return std::any_cast<MulticastDelegate<Args...>&>(event);
            }
            else {
                throw std::runtime_error("Event type mismatch");
            }
        }

    private:
        static inline HMUnorderedMap<HMString, std::any> events;
    };
} /// namespace HARMONY