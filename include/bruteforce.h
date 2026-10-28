#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_

#include "curl_context.h"
#include "wordlist.h"
#include <string>

void bruteforce(CURLContext &curl, const Wordlist &wordlist, const std::string &url);

#endif // BRUTEFORCE_H_