#ifndef _LS_PP_HEADER_
#define _LS_PP_HEADER_

#include <iostream>
#include <cxxopts.hpp>
#include <chrono>
#include <filesystem>

cxxopts::ParseResult set_opt(cxxopts::Options& options,const int& argc, char**& argv);
void temp_test_flag(const cxxopts::ParseResult& opt);
void sort_and_display(std::vector<std::string>& filenames, bool all, bool time);

#endif 
