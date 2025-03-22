#include "SimplestreamsInterpreter.h"
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Exception.h>

constexpr std::string_view UBUNTU_VERSION_PREFIX = "com.ubuntu.cloud:server";

SimplestreamsInterpreter::SimplestreamsInterpreter(const std::string &jsonContents) 
{
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(jsonContents);
	jsonObject = result.extract<Poco::JSON::Object::Ptr>();
}

bool SimplestreamsInterpreter::getStringValue(const std::string &key, std::string &value)
{
	if (jsonObject)
	{
		try
		{
			value = jsonObject->getValue<std::string>(key);
			return true;
		}
		catch (...)
		{
			// silently fail
		}
	}
	return false;
}

bool SimplestreamsInterpreter::getProducts(bool supportedOnly, std::list<std::string> &productsList)
{
	if (jsonObject)
	{
		try
		{
			Poco::JSON::Object::Ptr productsObject = jsonObject->getObject("products");
			productsList.clear();
			if (!productsObject)
			{
				return false;
			}
			for (auto itProducts : *productsObject)
			{
				std::string productName = itProducts.first;
				Poco::JSON::Object::Ptr productData = itProducts.second.extract<Poco::JSON::Object::Ptr>();
				bool isSupported = productData->optValue<bool>("supported", false);
				if (!supportedOnly || (supportedOnly && isSupported))
				{
					productsList.push_back(productName);
				}
			}
			return true;
		}
		catch (...)
		{
			// silently fail
		}
	}
	return false;
}

bool SimplestreamsInterpreter::getCurrentLTSVersion(std::string &currentLTSVersion)
{
	if (jsonObject)
	{
		try
		{
			Poco::JSON::Object::Ptr productsObject = jsonObject->getObject("products");
			currentLTSVersion.clear();
			if (!productsObject)
			{
				return false;
			}
			std::list<std::string> supportedLTSVersions;
			for (auto itProducts : *productsObject)
			{
				std::string productName = itProducts.first;
				Poco::JSON::Object::Ptr productData = itProducts.second.extract<Poco::JSON::Object::Ptr>();
				std::string title = productData->optValue<std::string>("release_title", "");
				if (title.find("LTS") != std::string::npos)
				{
					bool isSupported = productData->optValue<bool>("supported", false);
					if (isSupported)
					{
						supportedLTSVersions.push_back(title);
					}
				}
			}
			if (!supportedLTSVersions.empty())
			{
				currentLTSVersion = supportedLTSVersions.back();
				return true;
			}
		}
		catch (...)
		{
			// silently fail
		}
	}
	return false;
}

bool SimplestreamsInterpreter::getImageDiskSHA256(const std::string &version,
									const std::string &arch,
									const std::string &date,
									std::string &sha256Value)
{
	if (jsonObject)
	{
		try
		{
			Poco::JSON::Object::Ptr productsObject = jsonObject->getObject("products");
			sha256Value.clear();
			if (!productsObject)
			{
				return false;
			}
			std::string fullVersionName = std::string(UBUNTU_VERSION_PREFIX) + ":" + version + ":" + arch;
			if (productsObject->has(fullVersionName))
			{
				Poco::JSON::Object::Ptr productData = productsObject->getObject(fullVersionName);
				if (productData->has("versions"))
				{
					Poco::JSON::Object::Ptr versionsData = productData->getObject("versions");
					if (versionsData->has(date))
					{
						Poco::JSON::Object::Ptr dateData = versionsData->getObject(date);
						if (dateData->has("items"))
						{
							Poco::JSON::Object::Ptr itemsData = dateData->getObject("items");
							if (itemsData->has("disk1.img"))
							{
								Poco::JSON::Object::Ptr diskImgData = itemsData->getObject("disk1.img");
								if (diskImgData->has("sha256"))
								{
									sha256Value = diskImgData->optValue<std::string>("sha256", "");
									return true;
								}
							}
						}
					}
				}
			}
		}
		catch (...)
		{
			// silently fail
		}
	}
	return false;
}
