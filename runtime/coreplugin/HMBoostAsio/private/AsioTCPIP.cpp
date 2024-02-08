#include"AsioTCPIP.h"
#include"LogManager.h"

namespace HARMONY
{
	AsioTCPIP::AsioTCPIP():acceptor_(io_context_), socket(io_context_)
	{

	}
	AsioTCPIP::~AsioTCPIP()
	{
	}
	void AsioTCPIP::connect(const char* ipad, int port)
	{
		tcp::resolver resolver(io_context_);
		tcp::resolver::results_type endpoints = resolver.resolve(ipad, std::to_string(port)); 
		tcp::socket socket(io_context_);
		try {
			// 同期接続を試みる
			auto er = asio::connect(socket, endpoints); 
		}
		catch (const std::exception& e) {
			// 例外が発生した場合の処理
			std::cerr << "Exception: " << e.what() << std::endl;
			HM_ASSERT(false, "接続エラー: ,%d,%s", port, ec.message().c_str());
		}
	}

	void AsioTCPIP::send(std::vector<char>& data)
	{
		auto data_ptr = std::make_shared<std::vector<char>>(std::move(data));
		// データのサイズをデバッグ出力
		// ストランドを使用して非同期書き込みを順序付ける
		asio::async_write(socket,asio::buffer(*data_ptr),
				[this, data_ptr](const asio::error_code& error, std::size_t bytes_transferred) {
					// エラーチェックとハンドリングをここで行う
					this->write_handler(error, bytes_transferred);
				}
		);
	}

	std::vector<char> AsioTCPIP::receive()
	{
		data_.resize(1024);
		asio::async_read(
			socket,
			asio::buffer(data_),
			asio::transfer_at_least(1),
			[this](const asio::error_code& error, std::size_t bytes_transferred) {
				read_handler(error, bytes_transferred);
			});
		return data_;
	}

	void AsioTCPIP::disconnect()
	{
		io_service.stop();
		if (_netthred.joinable()) {
			_netthred.join();
		};
		if (socket.is_open()) {
			socket.close();
		}
	}
	void AsioTCPIP::start_server(int port)
	{

	}
	void AsioTCPIP::stop_server()
	{

	}
	void AsioTCPIP::registerDataReceivedCallback(DataReceivedCallback callback)
	{
		this->dataReceivedCallback = std::move(callback);
	}
	void AsioTCPIP::start_async_write()
	{
		std::lock_guard<std::mutex> lock(write_mutex_);
		if (!write_in_progress_ && !write_queue_.empty()) {
			write_in_progress_ = true;
			auto data_ptr = write_queue_.front();
			socket.async_write_some(
				asio::buffer(*data_ptr),
				[this, data_ptr](const asio::error_code& error, std::size_t bytes_transferred) {
					write_queue_.pop_front();
					write_in_progress_ = false;
					if (!error) {
						// 次のデータがあれば送信を続ける
						start_async_write();
					}
					else {
						// エラーハンドリング
					}
				}
			);
		}
	}
	void AsioTCPIP::read_handler(const asio::error_code& ec, std::size_t bytes_transferred)
	{
		if (!ec) {

			data_.resize(bytes_transferred); // 実際のデータサイズにリサイズ
			dataReceivedCallback(data_);
			this->receive();
			// ここにデータ処理のコードを書く
		}
		else {
			if (ec.message() == "既存の接続はリモートホストに強制的に切断されました")
			{

			}
			std::cerr << "読み取りエラー: " << ec.message() << std::endl;
		}
	}
	void AsioTCPIP::write_handler(const asio::error_code& ec, std::size_t bytes_transferred)
	{
		if (!ec) {
			printf("成功");
			printf("データサイズ: %zu\n", bytes_transferred);
			sendData.clear();
		}
		else {
			std::cerr << "書き込みエラー: " << ec.message() << std::endl;
		}
	}
	void AsioTCPIP::connect_handler(const asio::error_code& ec)
	{
		if (!ec) {

			this->receive();
		}
		else {
			std::cerr << "接続エラー: " << ec.message() << std::endl;
		}
	}
	void AsioTCPIP::Running()
	{
		io_service.run();
	}
}