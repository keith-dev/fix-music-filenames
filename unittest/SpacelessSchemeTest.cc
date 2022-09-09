#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(SpacelessSchemeTest, decode) {
	std::vector<std::string_view> names{
		"B0089B7CZS_(disc_1)_01_-_Two_Sevens_Clash.mp3",
		"B0089B7D8Y_(disc_1)_02_-_Money_In_My_Pocket___Cool_Runnings.mp3",
		"B0089B7DHU_(disc_1)_03_-_Officially___One_X_One.mp3",
		"B0089B7DRA_(disc_1)_04_-_Babylon_Too_Rough.mp3",
		"B0089B7DZM_(disc_1)_05_-_Cool_Out_Son.mp3",
		"B0089B7E7E_(disc_1)_06_-_Boxing_Around.mp3",
		"B0089B7EJM_(disc_1)_07_-_I'm_Still_In_Love_With_You.mp3",
		"B0089B7EQU_(disc_1)_08_-_Loving_Pauper___Judgement_Time.mp3",
		"B0089B7F6O_(disc_1)_09_-_Just_Like_A_River.mp3",
		"B0089B7FDW_(disc_1)_10_-_No_Competition.mp3"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, "-");
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " rootname.has_space=" << std::boolalpha << has_space(rootname)
			<< " token=" << "\'-\'" << " strings.size=" << strings.size();

		std::string newroot = replace_with_spaces(rootname, '_');
		ASSERT_TRUE(rootname.size() == newroot.size());

		strings = count_separators(newroot, "-");
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\'-\'" << " strings.size=" << strings.size();

		auto firsts = count_separators(strings[0], " ");
		ASSERT_TRUE(firsts.size() > 1 && is_numeric(trim_trailing(firsts.back(), ' ')))
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " token=" << "\' \'" << " firsts.size=" << firsts.size();

		auto scheme = std::make_unique<SpacelessScheme>(firsts[firsts.size() - 1], strings[1]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
