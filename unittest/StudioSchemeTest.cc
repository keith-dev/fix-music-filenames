#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(StudioSchemeTest, decode) {
	std::vector<std::string_view> names{
		"Rufus with Chaka Khan - 01 - Better Together.flac",
		"Rufus with Chaka Khan - 02 - Jigsaw.flac",
		"Rufus with Chaka Khan - 03 - Secret Friend.flac",
		"Rufus with Chaka Khan - 04 - Music Man (The DJ Song).flac",
		"Rufus with Chaka Khan - 05 - True Love.flac",
		"Rufus with Chaka Khan - 06 - Sharing The Love.flac",
		"Rufus with Chaka Khan - 07 - Quandary.flac",
		"Rufus with Chaka Khan - 08 - Lilah.flac",
		"Rufus with Chaka Khan - 09 - Losers in Love.flac",
		"Rufus with Chaka Khan - 10 - Highlight.flac"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, " - ", 3);
		ASSERT_TRUE(static_cast<std::size_t>(3) == strings.size() &&
		            static_cast<std::size_t>(2) == strings[1].size() && is_numeric(strings[1]))
			<< " rootname=\'" << rootname << "\' len=" << rootname.size()
			<< " token=" << "\'-\'" << " strings.size=" << strings.size();

		auto scheme = std::make_unique<StudioScheme>(strings[0], strings[1], strings[2]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
