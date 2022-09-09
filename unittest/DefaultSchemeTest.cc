#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(DefaultSchemeTest, decode) {
	std::vector<std::string_view> names{
		"Track 02.flac",
		"Track 03.flac",
		"Track 04.flac",
		"Track 05.flac",
		"Track 06.flac",
		"Track 07.flac",
		"Track 08.flac",
		"Track 09.flac",
		"Track 10.flac"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, " ", 2);
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\' \'" << " strings.size=" << strings.size();
		ASSERT_TRUE(strings[0] == "Track" && is_numeric(strings[1]))
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1].is_numeric=" << std::boolalpha << is_numeric(strings[1]);

		auto scheme = std::make_unique<DefaultScheme>(strings[1]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
