#include"HMString.h"
#include"HMString_impl.h"
#include"gc/gc.h"
#include<new>

namespace HARMONY
{
	HMString::HMString()
	{
		pImpl = static_cast<HMStringImpl*>(GC_MALLOC(sizeof(HMStringImpl)));
	}

	HMString::HMString(const TCHAR* str)
	{
		pImpl = static_cast<HMStringImpl*>(GC_MALLOC(sizeof(HMStringImpl)));
		new (pImpl) HMStringImpl(str);
	}

	HMString::~HMString()
	{
		
	}

	HMString::HMString(const HMString& other) {
		if (other.pImpl != nullptr) {
			pImpl = static_cast<HMStringImpl*>(GC_MALLOC(sizeof(HMStringImpl)));
			new (pImpl) HMStringImpl(*other.pImpl); // プレースメントnewを使用
		}
		else {
			pImpl = nullptr;
		}
	}

	HMString& HMString::operator=(const HMString& other)
	{
		if (this != &other) {
			*pImpl = *other.pImpl;
		}
		return *this;
	}

	HMString HMString::operator+(const HMString& other)const
	{
		size_t newLength = pImpl->length + other.pImpl->length;
		// GC_MALLOCを使用して新しいメモリを確保
		TCHAR* newData = static_cast<TCHAR*>(GC_MALLOC((newLength + 1) * sizeof(TCHAR)));

		TSTRCPY(newData, pImpl->data);
		TSTRCAT(newData, other.pImpl->data);

		HMString result;
		// 新しいHMStringImplインスタンスのメモリをBDWGCで確保
		result.pImpl = static_cast<HMStringImpl*>(GC_MALLOC(sizeof(HMStringImpl)));
		new (result.pImpl) HMStringImpl(); // プレースメントnewを使用して初期化
		result.pImpl->data = newData;
		result.pImpl->length = newLength;

		return result;
	}

	bool HMString::operator==(const HMString& other) const
	{
		return TSTRCMP(pImpl->data, other.pImpl->data) == 0;
	}

	bool HMString::operator!=(const HMString& other) const
	{
		return !(*this == other);
	}

	TCHAR& HMString::operator[](size_t index)
	{
		return pImpl->data[index];
	}

	const TCHAR& HMString::operator[](size_t index) const
	{
		return pImpl->data[index];
	}

	size_t HMString::Length() const
	{
		return pImpl->length;
	}

	TCHAR* HMString::GetRaw()const
	{
		return pImpl->data;
	}
}