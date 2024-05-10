#pragma once

class IModule
{
    /**
     * @brief 初期化段階で呼び出される関数
     * @return 初期化が成功したかどうか（true: 成功, false: 失敗）
     */
    virtual bool AwakeInitialize() = 0;

    /**
     * @brief 通常の初期化段階で呼び出される関数
     * @return 初期化が成功したかどうか（true: 成功, false: 失敗）
     */
    virtual bool Initialize() { return true; }

    /**
     * @brief 後段の初期化段階で呼び出される関数
     * @return 初期化が成功したかどうか（true: 成功, false: 失敗）
     */
    virtual bool LateInitialize() { return true; }

    /**
     * @brief ゲームループが開始する直前に呼び出される関数
     */
    virtual void Ready() {}

    /**
     * @brief ゲームループ中に呼び出される更新関数
     */
    virtual void Update() {}

    /// @brief 
    virtual void LateUpdate() {}

    /**
     * @brief シングルトンの終了処理を行う関数
     */
    virtual void Terminate() {}
};