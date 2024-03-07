#pragma once
#include<type_traits>
#include<vector>
#include<list>
#include<deque>
#include<array>
#include"Value.h"

namespace HARMONY
{
	template<typename T>
	struct SeqentialArrayWrapper
	{

	};


	template<typename T,typename E = void>
	struct SeqentialArray:std::false_type
	{};



	template<typename T>
	struct SequentialArray<std::vector<T>> : std::true_type {
		using ContainerType = std::vector<T>;
		using Itereter_t = std::vector<T>::iterator;
		using Const_Itereter_t = std::vector<T>::const_iterator;

		// サイズを取得
		static size_t Size(ContainerType& container) {
			return container.size();
		}

		// サイズを変更
		static void Resize(ContainerType& container, size_t size) {
			container.resize(size); 
		}

		// 特定の位置の値を取得
		static T At(ContainerType& container, size_t index) { 
			return container[index];
		}

		// 動的サイズかを返す
		static bool IsDynamic() {
			return true;
		}

		// イテレータを取得するメソッドの例
		static Itereter_t Begin(ContainerType& container) { 
			return container.begin();
		} 

		static Itereter_t End(ContainerType& container) {
			return container.end();
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