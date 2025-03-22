#include "WebDownloader.h"

#include <iostream>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/HTTPSStreamFactory.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/URI.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/Exception.h>

WebDownloader::WebDownloader(const std::string& url) 
    : url(url)
{
}

bool WebDownloader::fetchContents(std::string &contents)
{
    bool success = false;
    contents.clear();
    try
    {
        Poco::Net::HTTPStreamFactory::registerFactory();
        Poco::Net::HTTPSStreamFactory::registerFactory();

        Poco::Net::initializeSSL();
        Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler(new Poco::Net::AcceptCertificateHandler(false));
        Poco::Net::Context::Ptr ptrContext(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, ""));
        Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);

        Poco::URI uri(url);
        std::unique_ptr<std::istream> is(Poco::URIStreamOpener::defaultOpener().open(uri));
        Poco::StreamCopier::copyToString(*is, contents);
        success = true;
    }
    catch (Poco::Exception &ex)
    {
        std::cerr << "Poco Exception: " << ex.displayText() << std::endl;
    }
    catch (std::exception &ex)
    {
        std::cerr << "Standard Exception: " << ex.what() << std::endl;
    }
    Poco::Net::uninitializeSSL();
    return success;
}