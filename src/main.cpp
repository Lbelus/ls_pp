#include <ls_pp.hpp>


int main(int argc, char* argv[])
{
    cxxopts::Options options("ls_pp", "A simple cpp implementation of ls");
	cxxopts::ParseResult opt = set_opt(options, argc, argv);
    if (opt.count("help"))
    {
      std::cout << options.help() << std::endl;
      return EXIT_SUCCESS;
    }
    std::vector<std::string> filenames = opt["filenames"].as<std::vector<std::string>>();
	temp_test_flag(opt);
	sort_and_display(filenames, opt["all"].as<bool>(), opt["time"].as<bool>());

    return EXIT_SUCCESS;
}
