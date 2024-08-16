#include <common_header.hpp>
#include <cxxopts.hpp>

int main(int argc, char* argv[])
{
    cxxopts::Options options("ls_pp", "A simple cpp implementation of ls");

    options.add_options()
        ("a,all", "do not ignore entries starting with .", cxxopts::value<bool>()->default_value("false"))
        ("t,time", "Sort by time, newest first, --time does not makes use the usuals options", cxxopts::value<bool>()->default_value("false"))
        ("filenames", "The filename(s) to process", cxxopts::value<std::vector<std::string>>())
        ("h,help", "Print usage");

    options.parse_positional({"filenames"});

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(EXIT_SUCCESS);
    }
    std::vector<std::string> filenames = result["filenames"].as<std::vector<std::string>>();
	if (filenames.size() < 1)
	{
      std::cout << options.help() << std::endl;
      exit(EXIT_SUCCESS);
	}
	bool time = result["time"].as<bool>();
	if (time)
	{
		std::cout << "time option is activated" << std::endl;
	}
	
	bool all = result["all"].as<bool>();
	if (all)
	{
		std::cout << "all option is activated" << std::endl;
	}

	for (std::vector<std::string>::iterator it = filenames.begin(); it != filenames.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

    return EXIT_SUCCESS;
}
