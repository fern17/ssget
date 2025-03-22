#ifndef WEBDOWNLOADER_H
#define WEBDOWNLOADER_H

#include <string>

class WebDownloader
{
public:
	WebDownloader(const std::string &url);
	bool fetchContents(std::string &contents);

private:
	std::string url;
};
#endif