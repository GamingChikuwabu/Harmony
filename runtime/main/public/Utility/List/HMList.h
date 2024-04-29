#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
		// ノードを表すクラス
		template<typename T>
		class Node {
		public:
			T data;         // データ
			Node<T>* prev;  // 前のノードへのポインタ
			Node<T>* next;  // 次のノードへのポインタ

			// コンストラクタ
			Node(T data) : data(data), prev(nullptr), next(nullptr) {}
		};
	}

	/// @brief リストクラス
	template<typename T>
	class HMList
	{
	public:
		void Add(T obj);
		void Remove(T obj);
		void Clear();
		/// @brief イテレータクラス
		class Iterator {
		private:
			DETAIL::Node<T>* node;
		public:
			Iterator(DETAIL::Node<T>* n) : node(n) {}

			T& operator*() const {
				return node->data;
			}

			Iterator& operator++() {
				node = node->next;
				return *this;
			}

			bool operator!=(const Iterator& other) const {
				return node != other.node;
			}
		};
		Iterator begin();
		const Iterator begin() const;
		Iterator end();
		const Iterator end() const;
	private:
		// 先頭ノード
		DETAIL::Node<T>* head;
		// 末尾ノード
		DETAIL::Node<T>* tail;
	};
}