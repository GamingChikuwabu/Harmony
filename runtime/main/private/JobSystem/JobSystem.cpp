#include "JobSystem.h"

namespace HARMONY
{
	JobHandle HMModJobSystem::schedule(const std::function<void()>& job)
	{
		// packaged_task と shared_future を作成
		std::packaged_task<void()> task(job);
		auto future = task.get_future().share();
		{
			std::lock_guard<std::mutex> lock(jobQueueMutex);
			// ジョブをキューにプッシュ
			jobCounter.fetch_add(1); // インクリメント 
			completeFlag.store(false); // 未完了にする 
			jobQueue.push(std::move(task));
		}
		// 待機中のワーカースレッドをひとつ起こす
		condition.notify_one();
		return future;
	}

	JobHandle HMModJobSystem::schedule(const std::function<void()>& job, const std::vector<JobHandle>& dependencies)
	{
		auto wrapper = [job, dependencies]() {
			// 全ての依存ジョブが終わるまで待機する
			for (auto& dep : dependencies) {
				if (dep.valid()) {
					dep.wait();
				}
			}

			job();
			};
		return schedule(wrapper);
	}

	void HMModJobSystem::waitForAll()
	{
		// trueになるまで待機する
		completeFlag.wait(false);
	}

	void HMModJobSystem::Terminate()
	{
		// 全てのワーカースレッドに停止信号を送る
		stopFlag.store(true);
		// 全てのワーカースレッドを起こす
		condition.notify_all();
		// 全てのワーカースレッドが終了するのを待つ
		for (auto& worker : workerThread) {
			if (worker.joinable()) {
				worker.join();
			}
		}
	}

	void HMModJobSystem::workerThreadFunction()
	{
		// 無限ループで待機と実行を繰り返す
		while (true) {
			std::packaged_task<void()> job;
			{
				std::unique_lock<std::mutex> lock(jobQueueMutex);
				condition.wait(lock, [] {
					return !jobQueue.empty() || stopFlag;
					});

				if (stopFlag && jobQueue.empty()) {
					break;
				}

				job = std::move(jobQueue.front());
				jobQueue.pop();
			} // ロックを解放

		// ジョブを実行する
			job();
			// デクリメント	    
			if (jobCounter.fetch_sub(1) == 1) {
				// カウントが0になったら完了フラグを立てて通知
				completeFlag.store(true);
				completeFlag.notify_all();
			}
		}
	}
}