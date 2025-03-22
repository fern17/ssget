#ifndef SIMPLESTREAMSINTERPRETER_H
#define SIMPLESTREAMSINTERPRETER_H

#include <string>
#include <Poco/JSON/Object.h>

/* class SimplestreamsInterpreter
* This class takes a string that represents a JSON file
* and allows the client to retrieve specific data from the file
* The file is supposed to be in the SimpleStreams schema
* https://canonical-simplestreams.readthedocs-hosted.com/en/latest/reference/streams-product-jsonschema/#jsonschema-product
*/
class SimplestreamsInterpreter
{
public:
	/* SimplestreamsInterpreter constructor
	* jsonContents: string representing the json file contents
	*/
	SimplestreamsInterpreter(const std::string &jsonContents);

	/* getStringValue: get the value of a global key
	* key: the key to retrieve its value
	* value: the value of the key, if found (output)
	* Return true if successfull, false otherwise
	*/
	bool getStringValue(const std::string &key, std::string &value);

	/* getProducts: get the list of products
	* supportedOnly: if true, get only the current supported products
	* products: list of products in the same order as in the file (output)
	* Return true if successfull, false otherwise
	*/
	bool getProducts(bool supportedOnly, std::list<std::string> &products);

	/* getCurrentLTSVersion: get the current LTS supported version (latest one)
	* version: the version in format "YY.MM LTS" (output)
	* Return true if successfull, false otherwise
	*/
	bool getCurrentLTSVersion(std::string &version);

	/* getImageDiskSHA256: get the SHA256 from the image disk (disk1.img) for the given version, architecture and date
	* version: the release version, in format YY.MM
	* arch: the release architecture (amd64, i386, etc)
	* date: the release date, in format YYYYMMDD[.X]
	* sha256Value: the SHA256 value  (output)
	* Return true if successfull, false otherwise
	*/
	bool getImageDiskSHA256(const std::string &version, const std::string &arch, const std::string &date, std::string &sha256Value);

private:
	/* jsonObject: JSON structure read from the input string
	*/
	Poco::JSON::Object::Ptr jsonObject;
};

#endif