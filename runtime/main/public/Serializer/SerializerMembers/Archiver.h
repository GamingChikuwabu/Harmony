#pragma once
#include<inttypes.h>


namespace HARMONY
{
	namespace SERIALIZER
	{
		class Archiver
		{
		public:
			Archiver() {};
			~Archiver() {};
			virtual Archiver& operator&(const TCHAR* data) {}
			virtual Archiver& operator&(int8_t data){}
			virtual Archiver& operator&(uint8_t data){}
			virtual Archiver& operator&(int16_t data){}
			virtual Archiver& operator&(uint16_t data){}
			virtual Archiver& operator&(int32_t data){}
			virtual Archiver& operator&(uint32_t data){}
			virtual Archiver& operator&(int64_t data){}
			virtual Archiver& operator&(uint64_t data){}
			virtual Archiver& operator&(float data){}
			virtual Archiver& operator&(double data){}
			virtual Archiver& operator&(bool data){}
			virtual bool IsSave() = 0;
			virtual void StartObject(const TCHAR* name) {};
			virtual void EndObject() {};
			virtual void StartArray() {};
			virtual void EndArray() {};
			virtual void SetKey(const TCHAR* key) {};//JsonXMLなどで使用
		};
	}
}