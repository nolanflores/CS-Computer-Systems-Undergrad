#ifndef TEXTBOOK_HPP
#define TEXTBOOK_HPP

#include "book.hpp"

class textbook : public book{
private:
    int num_coauthors = 0;
    std::string* coauthors = nullptr;

public:
    textbook(const std::string& name, const std::string& author, int num_pages, int num_coauthors);

    int get_num_coauthors() const;

    std::string get_coauthor(int index) const;

    void set_coauthor(int index, const std::string& coauthor);

    textbook(const textbook& t);

    void operator=(const textbook& t);

    ~textbook();
};

#endif