#ifndef CURL_CONTEXT_H_
#define CURL_CONTEXT_H_

#include "http.h"
#include <curl/curl.h>
#include <string>

class CURLContext {
public:
    CURLContext();
    CURLContext(const CURLContext &) = delete;
    CURLContext(CURLContext &&) = delete;

    ~CURLContext();

    // HEAD request
    HTTPResponseCode request(const std::string &url);

    CURLContext &operator =(const CURLContext &) = delete;
    CURLContext &operator =(CURLContext &&) = delete;

private:
    CURL *handle_;
    CURLcode result_;
    HTTPResponseCode response_;
};

#endif // CURL_CONTEXT_H_