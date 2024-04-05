#pragma once
#pragma warning(disable:4251)

#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>


namespace HARMONY
{
    using JobHandle = std::shared_future<void>;
    class UTILITY_API HMModJobSystem
    {
    public: 
        static JobHandle schedule(const std::function<void()>& job);
        static JobHandle schedule(const std::function<void()>& job, const std::vector<JobHandle>& dependencies);
        static void waitForAll();
        static void Terminate();
    private:
        //スレッドの数
        static inline const size_t num_workers = std::thread::hardware_concurrency();
        //ワーカースレッド
        static inline std::vector<std::thread> workerThread;
        //JobQueue
        static inline std::queue<std::packaged_task<void()>> jobQueue;

        //mutex
        static inline std::mutex jobQueueMutex;
        //依存関係などの調節用コンディション
        static inline std::condition_variable condition;
        static inline std::atomic<int> jobCounter = 0;
        static inline std::atomic<bool> completeFlag = false;
        static inline std::atomic<bool> stopFlag = false;
        static inline int test = 0;
        //ワーカスレッド内で呼び出される関数 
        static void workerThreadFunction();
    };
} 