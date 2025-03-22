#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <string>
#include <Poco/JSON/Object.h>
#include <Poco/Exception.h>

class JsonParser
{
public:
	JsonParser(const std::string &jsonContents);
	
	template<typename T>
	bool get(const std::string &key, T &value)
	{
		if (jsonObject)
		{
			try
			{
				value = jsonObject->getValue<T>(key);
				return true;
			}
			catch (...)
			{
				// silently fail
			}
		}
		return false;
	}

private:
	Poco::JSON::Object::Ptr jsonObject;
};

#endif