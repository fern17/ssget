#include "JsonInterpreter.h"
#include <Poco/JSON/Parser.h>

JsonInterpreter::JsonInterpreter(const std::string &jsonContents)
{
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(jsonContents);
	jsonObject = result.extract<Poco::JSON::Object::Ptr>();
}
