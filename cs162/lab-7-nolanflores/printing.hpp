#ifndef PRINTING_HPP
#define PRINTING_HPP

#include "page.hpp"
#include "book.hpp"
#include "textbook.hpp"

// Print a page to the terminal in a nice format
void print_page(const page& page_to_print);

// Print a book to the terminal in a nice format
void print_book(const book& book_to_print);

// TODO Part 2: Prototype print_textbook
void print_textbook(const textbook& book_to_print);

#endif
