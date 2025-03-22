#ifndef WEBDOWNLOADER_H
#define WEBDOWNLOADER_H

#include <string>
/* class WebDownloader
* This class downloads the contents from the given url into a string, using HTTPS and SSL
*/
class WebDownloader
{
public:
	/* Constructor
	* url: the url to download from
	*/
	WebDownloader(const std::string &url);

	/* fetchContents: get the contents of the url and store them in a string
	* contents: output string
	* Return true if successfull, false otherwise
	*/
	bool fetchContents(std::string &contents);

private:
	std::string url;
};
#endif