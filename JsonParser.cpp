#include "JsonParser.h"
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

JsonParser::JsonParser(const std::string &jsonContents) 
{
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(jsonContents);
	jsonObject = result.extract<Poco::JSON::Object::Ptr>();
}