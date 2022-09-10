#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(AbcdeSchemeTest, decode) {
	std::vector<std::string_view> names{
		"01. Lodge.mp3",
		"02. Blackboard.mp3",
		"03. Toast.mp3",
		"04. Big Big (Explicit).mp3",
		"05. First Class Flight (feat. Prince S.mp3",
		"06. Dumpling (feat. Sean Paul and Spic.mp3",
		"07. Spend 'Nuff Money (Explicit).mp3",
		"08. Different Rankin (Explicit).mp3"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

/*
		auto strings = count_separators(rootname, " ", 2);
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\' \'" << " strings.size=" << strings.size();
		ASSERT_TRUE(strings[0] == "Track" && is_numeric(strings[1]))
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1].is_numeric=" << std::boolalpha << is_numeric(strings[1]);

 */
		auto strings = count_separators(rootname, ".", 1);
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\'.\'" << " strings.size=" << strings.size();
		ASSERT_TRUE(is_numeric(strings[0]))
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1].is_numeric=" << std::boolalpha << is_numeric(strings[1]);

		auto scheme = std::make_unique<AbcdeScheme>(strings[0], trim(strings[1]));
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
