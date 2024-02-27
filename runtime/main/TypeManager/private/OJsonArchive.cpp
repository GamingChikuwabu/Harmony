#include "archive/json/OJsonArchive.h"
#include"rapidjson/document.h"
#include"rapidjson/prettywriter.h"
#include"variant.h"
#include"type.h"

namespace HARMONY
{
	namespace ARCHIVE
	{
		void to_json_recursively(const variant& obj2, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);
		OJsonArchive::OJsonArchive(const std::ostream& os)
		{

		}

		OJsonArchive::~OJsonArchive()
		{
		}

		const char* OJsonArchive::ToString() const
		{
			return nullptr;
		}

		void OJsonArchive::Archive(variant var) const
		{
			rapidjson::StringBuffer sb;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb); 

		}

		void to_json_recursively(const variant& obj2, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
		{
			writer.StartObject(); 
			if (0)
			{

			}
			writer.EndObject();
		}
	}
}