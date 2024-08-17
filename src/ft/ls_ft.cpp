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
    for (std::vector<std::string>::iterator it = filenames.begin(); it != filenames.end(); ++it)
	{
		std::cout << *it << std::endl;
		const std::filesystem::path user_path{*it};
		std::cout << "directory_iterator:\n";
		// directory_iterator can be iterated using a range-for loop
		for (auto const& dir_entry : std::filesystem::directory_iterator{user_path})
		{
			if (all)
			{
    			auto ftime = std::filesystem::last_write_time(dir_entry.path());
    			auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    ftime - std::filesystem::file_time_type::clock::now() +
                    std::chrono::system_clock::now());

			    // Convert to seconds since epoch
    			double seconds_since_epoch = std::chrono::duration<double>(sctp.time_since_epoch()).count();
				std::cout << dir_entry.path() << ", time :" << seconds_since_epoch << std::endl;

			}
			else
			{
				std::string path = dir_entry.path(); 
				if (path[2] != '.')
				{
					std::cout << dir_entry.path() << '\n';
				}
			}
		} 
	}
}
	
