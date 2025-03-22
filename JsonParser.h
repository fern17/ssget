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

	bool getProducts(bool supportedOnly, std::list<std::string> &products);
	bool getCurrentLTSVersion(std::string &version);
	bool getImageDiskSHA256(const std::string &version, const std::string &arch, const std::string &date, std::string &sha256Value);

private:
	Poco::JSON::Object::Ptr jsonObject;
};

#endif