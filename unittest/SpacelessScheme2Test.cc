#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(SpacelessSchemeTest2, decode) {
	std::vector<std::string_view> names{
		"Alexander_O’Neal-1-A_Broken_Heart_Can_Mend.flac",
		"Alexander_O’Neal-2-If_You_Were_Here_Tonight.flac",
		"Alexander_O’Neal-3-Do_You_Wanna_Like_I_Do.flac",
		"Alexander_O’Neal-4-Look_at_Us_Now.flac",
		"Alexander_O’Neal-5-Medley_Innocent__Alex_9000__Innocent_II.flac",
		"Alexander_O’Neal-6-Whats_Missing.flac",
		"Alexander_O’Neal-7-You_Were_Meant_to_Be_My_Lady_(Not_My_Girl).flac"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, "-");
		ASSERT_TRUE(!has_space(rootname) && static_cast<std::size_t>(3) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " rootname.has_space=" << std::boolalpha << has_space(rootname)
			<< " token=" << "\'-\'" << " strings.size=" << strings.size();

		std::string newroot = replace_with_spaces(rootname, '_');
		ASSERT_TRUE(rootname.size() == newroot.size());

		strings = count_separators(newroot, "-");
		ASSERT_TRUE(static_cast<std::size_t>(3) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\'-\'" << " strings.size=" << strings.size();

		auto scheme = std::make_unique<SpacelessScheme2>(strings[0], strings[1], strings[2]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
