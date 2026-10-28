#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <string>
#include <vector>

class Wordlist {
public:
    Wordlist(const std::string &pathname);
    Wordlist(const Wordlist &) = delete;
    Wordlist(Wordlist &&) = delete;

    const auto &path() const
    {
        return path_;
    }

    const auto &words() const
    {
        return words_;
    }

    auto word_count() const
    {
        return words_.size();
    }

    bool empty() const
    {
        return words_.empty();
    }

    Wordlist &operator =(const Wordlist &) = delete;
    Wordlist &operator = (Wordlist &&) = delete;

private:
    std::string path_;
    std::vector<std::string> words_;
};

#endif // WORDLIST_H_