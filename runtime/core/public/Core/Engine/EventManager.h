#pragma once
#include <functional>
#include <any>
#include<stdexcept>
#include<future>
#include"Utility/collections/containers.h"
#include"Utility/collections/strings.h"

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

    /// @brief 同期的にイベントをブロードキャストする
    /// @param ...args 引数
    void Broadcast(Args... args) {
        for (auto& delegate : delegates) {
            delegate(args...);
        }
    }

    /// @brief 非同期でイベントをブロードキャストする
    /// @param ...args 引数
    void AsyncBroadcast(Args... args) {
        for (auto& delegate : delegates) {
            std::async(std::launch::async, delegate, args...);
        }
    }

    void Clear() {
        delegates.clear();
    }

    void Remove(Delegate<Args...> delegate) {
        delegates.erase(delegate);
    }

private:
    HMArray<Delegate<Args...>> delegates;
};

// イベントマネージャクラスの定義
class CORE_API EventManager
{
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