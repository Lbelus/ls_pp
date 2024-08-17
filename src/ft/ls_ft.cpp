#include <ls_pp.hpp>
#include <algorithm>
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
    std::vector<std::string> filelist;
    for (auto it = filenames.begin(); it != filenames.end(); ++it)
    {
        const std::filesystem::path user_path{*it};
        if (filenames.size() > 1 )
        {
            std::cout << *it << ":" << std::endl;
        }
        std::vector<std::string> files = get_files_info(user_path, all);
        filelist.insert(filelist.end(), files.begin(), files.end());
        time_sort(filelist, time);
        print_filelist(filelist);
        filelist.clear();
        if (it + 1 != filenames.end())
        {
            std::cout << std::endl;
        }
    }
}
	
std::vector<std::string> get_files_info(const std::filesystem::path& user_path, bool all)
{
    std::vector<std::string> result;
    std::string path;
    // std::filesystem does not include dot and dot-dot local and parent directories
    if (all)
    {
        result.push_back(user_path / ".");
        result.push_back(user_path / "..");
    }
    for (auto const& dir_entry : std::filesystem::directory_iterator{user_path})
    {
        path = dir_entry.path().string();;
        if (all)
        {
            result.push_back(path);
        }
        else
        {
            if (std::filesystem::is_regular_file(path) && dir_entry.path().filename().string()[0] != '.')
            {
                result.push_back(path);
            }
        }
    }
    return result;
}

void time_sort(std::vector<std::string>& filelist, bool time)
{
    if (time)
    {
        std::sort(filelist.begin(), filelist.end(),
            [](const std::string& a, const std::string& b) {
                try {
                    return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
                } catch (const std::filesystem::filesystem_error& e) {
                    std::cerr << "Error accessing file time: " << e.what() << '\n';
                    return false;
                }
            });
    }
}

void print_filelist(const std::vector<std::string>& filelist)
{
    for (const auto& filepath : filelist)
    {
        std::filesystem::path path_obj(filepath);
        std::cout << path_obj.filename().string() << std::endl;
    }
}
    