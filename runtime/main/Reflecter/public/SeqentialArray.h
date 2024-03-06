#pragma once
#include<type_traits>
#include<vector>
#include<list>
#include<deque>
#include<array>
#include"Value.h"

namespace HARMONY
{
	template<typename T,typename E = void>
	struct SeqentialArray:std::false_type
	{};

	template<typename T>
	struct SequentialArray<std::vector<T>> : std::true_type {
		// サイズを取得
		static size_t Size(void* container) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			return temp->size();
		}

		// サイズを変更
		static void Resize(void* container, size_t size) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			temp->resize(size);
		}

		// 特定の位置の値を取得
		static T At(void* container, size_t index) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container); 
			return temp->at(index);
		}

		// 動的サイズかを返す
		static bool IsDynamic() {
			return true;
		}

		// イテレータを取得するメソッドの例
		static typename std::vector<T>::iterator Begin(void* container) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			return temp->begin();
		}

		static typename std::vector<T>::iterator End(void* container) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			return temp->end();
		}

		// イテレータを使用して要素を挿入
		static void Insert(void* container, typename std::vector<T>::iterator pos, const T& value) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			temp->insert(pos, value);
		}

		// イテレータを使用して要素を削除
		static void Erase(void* container, typename std::vector<T>::iterator pos) {
			auto* temp = reinterpret_cast<std::vector<T>*>(container);
			temp->erase(pos);
		}
	};


	template<typename T>
	struct SeqentialArray<std::deque<T>> :std::true_type
	{
		static size_t Size(void* container)
		{
			std::deque<T> temp = *reinterpret_cast<std::deque<T>>(container);
			return temp.size();
		}
		static bool IsDynamic() { return true; }
	};

	template<typename T>
	struct SeqentialArray<std::list<T>> :std::true_type
	{
		static size_t Size(void* container)
		{
			std::list<T> tempVec = *reinterpret_cast<std::list<T>>(container);
			return tempVec.size();
		}
		static bool IsDynamic() { return true; }
	};

	template<typename T, size_t N>
	struct SeqentialArray<std::array<T,N>> :std::true_type
	{
		static size_t Size(void* container) 
		{
			return N;
		}
		static bool IsDynamic() { return false; }
	};

	template<typename T,size_t N>
	struct SeqentialArray<T[N]> :std::true_type
	{
		static size_t GetSize(void* container)
		{
			return N;
		}
		static bool IsDynamic() { return false; }
	};

}