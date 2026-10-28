#include "curl_context.h"
#include "http.h"
#include <stdexcept>
#include <string>

CURLContext::CURLContext()
    : handle_(curl_easy_init())
{
    if (not handle_)
        throw std::runtime_error("could not initialize CURL handle");

    curl_easy_setopt(handle_, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
}

CURLContext::~CURLContext()
{
    curl_easy_cleanup(handle_);
}

HTTPResponseCode CURLContext::request(const std::string &url)
{
    curl_easy_setopt(handle_, CURLOPT_NOBODY, 1l);
    curl_easy_setopt(handle_, CURLOPT_URL, url.c_str());

    result_ = curl_easy_perform(handle_);
    if (result_ != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(result_));

    curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &response_);
    return response_;
}