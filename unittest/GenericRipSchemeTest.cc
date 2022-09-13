#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(GenericRipSchemeTest, decode) {
	std::vector<std::string_view> names{
		"01 Temperature (Repack).mp3",
		"02 Step Out (Repack).mp3",
		"03 Toppa Tings (Repack).mp3",
		"04 Bun Him (Repack).mp3",
		"05 Gangster Rock (Repack).mp3",
		"06 Badman Forward Badman Pull Up (Re.mp3",
		"07 Ring Ding Ding (Repack).mp3",
		"08 Dance (Repack).mp3"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, " ", 1);
		ASSERT_TRUE(strings.size() > 1)
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\'.\'" << " strings.size=" << strings.size();
		ASSERT_TRUE(strings[0].size() == 2 && is_numeric(strings[0]))
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[0].size() << "\n"
			<< " strings[0].is_numeric=" << std::boolalpha << is_numeric(strings[0]);

		auto scheme = std::make_unique<GenericRipScheme>(strings[0], strings[1]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
