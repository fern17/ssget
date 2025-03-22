#include "JsonParser.h"
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Array.h>

JsonParser::JsonParser(const std::string &jsonContents) 
{
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(jsonContents);
	jsonObject = result.extract<Poco::JSON::Object::Ptr>();
}

bool JsonParser::getProducts(bool supportedOnly, std::list<std::string> &productsList)
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

bool JsonParser::getCurrentLTSVersion(std::string &currentLTSVersion)
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
