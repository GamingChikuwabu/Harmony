#pragma once
#include <asio.hpp>
#include <vector>
#include<iostream>
#include <string>
#include <thread>
#include <functional>
#include <deque>
#include"IProtocol.h"

// Boost.Asioを使用したTCPプロトコルの実装
using asio::ip::tcp;
namespace HARMONY
{
    class AsioTCPIP : public IProtocol {
    public:
        AsioTCPIP();

        ~AsioTCPIP()override;

        void connect(const char* ipad, int port) override;

        void send(std::vector<char>& data)override;

        std::vector<char> receive() override;

        void disconnect() override;

        void start_server(int port) override;

        void stop_server() override;

        void registerDataReceivedCallback(DataReceivedCallback callback) override;

        //サービスの開始
        void Running()override;

    private:
        void start_async_write();

        // サーバからのメッセージを非同期に読み取るためのハンドラ
        void read_handler(const asio::error_code& ec, std::size_t bytes_transferred);

        // サーバへのメッセージを非同期に書き込むためのハンドラ
        void write_handler(const asio::error_code& ec, std::size_t bytes_transferred);

        // 非同期接続のハンドラ
        void connect_handler(const asio::error_code& ec);

        std::vector<char> sendData;
        std::vector<char> data_;
        asio::io_context io_service;
        asio::io_context io_context_;
        asio::ip::tcp::acceptor acceptor_;
        tcp::socket socket;
        DataReceivedCallback dataReceivedCallback; // コールバック関数を保持
        std::deque<std::shared_ptr<std::vector<char>>> write_queue_; // 書き込みキュー
        std::mutex write_mutex_; // キュー操作用のミューテックス
        bool write_in_progress_ = false; // 書き込み進行中フラグ
        std::thread _netthred;
    };
}