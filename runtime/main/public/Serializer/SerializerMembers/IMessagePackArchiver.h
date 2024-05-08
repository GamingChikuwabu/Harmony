#pragma once
#include"IArchiver.h"
#define MSGPACK_NO_BOOST
#include<msgpack.hpp>

namespace HARMONY
{
	namespace SERIALIZER
	{
		class IMessagePackArchiver : public IArchiver
		{
		public:
			Archiver& operator&(int8_t data)override
			{
				return *this;
			}
			Archiver& operator&(uint8_t data)override
			{
				return *this;
			}
			Archiver& operator&(int16_t data)override
			{
				return *this;
			}
			Archiver& operator&(uint16_t data)override
			{
				return *this;
			}
			Archiver& operator&(int32_t data)override
			{
				return *this;
			}
			Archiver& operator&(uint32_t data)override
			{
				return *this;
			}
			Archiver& operator&(int64_t data)override
			{
				return *this;
			}
			Archiver& operator&(uint64_t data)override
			{
				return *this;
			}
			Archiver& operator&(float data)override
			{
				return *this;
			}
			Archiver& operator&(double data)override
			{
				return *this;
			}
			Archiver& operator&(bool data)override
			{
				return *this;
			}
		private:

		};
	}
}