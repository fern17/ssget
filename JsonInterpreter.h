#ifndef JSONINTERPRETER_H
#define JSONINTERPRETER_H

#include <string>
#include <Poco/JSON/Object.h>

/* class JsonInterpreter
* This class takes a string that represents a JSON file
* and constructs an object that allows to inspect the JSON file
* This class is meant to be inherited and define custom getters for the desired data
*/
class JsonInterpreter
{
public:
	JsonInterpreter(const std::string &jsonContents);

protected:
	/* jsonObject: JSON structure read from the input string */
	Poco::JSON::Object::Ptr jsonObject;
};
#endif
