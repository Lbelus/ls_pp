#include <ls_pp.hpp>

cxxopts::ParseResult set_opt(cxxopts::Options& options,const int& argc, char**& argv)
{
    options.add_options()
        ("a,all", "do not ignore entries starting with .", cxxopts::value<bool>()->default_value("false"))
        ("t,time", "Sort by time, newest first, --time does not makes use the usuals options", cxxopts::value<bool>()->default_value("false"))
        ("filenames", "The filename(s) to process", cxxopts::value<std::vector<std::string>>()->default_value("."))
        ("h,help", "Print usage");

    options.parse_positional({"filenames"});
    cxxopts::ParseResult result = options.parse(argc, argv);
    return result;
}

void temp_test_flag(const cxxopts::ParseResult& opt)
{
    bool time = opt["time"].as<bool>();
	if (time)
	{
		std::cout << "time option is activated" << std::endl;
	}
	bool all = opt["all"].as<bool>();
	if (all)
	{
		std::cout << "all option is activated" << std::endl;
	}
}

void sort_and_display(std::vector<std::string>& filenames, bool all, bool time)
{
    std::vector<std::string> result;
    std::string path;
    for (std::vector<std::string>::iterator it = filenames.begin(); it != filenames.end(); ++it)
	{
        const std::filesystem::path user_path{*it};
		std::cout << *it << ":" << std::endl;
        get_regular_files(user_path, all);
	}
}
	
std::vector<std::string> get_regular_files(const std::filesystem::path& user_path, bool all)
{
    std::vector<std::string> result;
    std::string path;
    // std::filesystem does not include dot and dot-dot local and parent directories ?? what ? why ?
    if (all)
    {
        result.push_back(std::string("."));
        result.push_back(std::string(".."));
    }
    for (auto const& dir_entry : std::filesystem::directory_iterator{user_path})
    {
        path = dir_entry.path().lexically_relative(user_path).string();;
        if (all)
        {
            result.push_back(path);
        }
        else
        {
            if (std::filesystem::is_regular_file(path) && path[0] != '.')
            {
                std::cout << path << std::endl;
            }
        }
    }
    std::cout << std::endl;
    return result;
}


