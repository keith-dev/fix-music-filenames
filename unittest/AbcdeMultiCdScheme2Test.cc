#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(AbcdeMultiCdScheme2Test, decode) {
	std::vector<std::string_view> names{
		"2-02.The Family Stand–Ghetto Heaven (Remix Edit)-The Family Stand–Ghetto Heaven (Remix Edit).flac",
//		"2-03.-.flac",
		"2-04.The Blackbyrds–Rock Creek Park-The Blackbyrds–Rock Creek Park.flac",
		"2-05.Cheryl Lynn–Encore-Cheryl Lynn–Encore.flac",
		"2-06.Fat Larrys Band–Act Like You Know-Fat Larrys Band–Act Like You Know.flac",
		"2-07.Roy Ayers–Love Will Bring Us Back Together-Roy Ayers–Love Will Bring Us Back Together.flac",
		"2-08.Teena Marie–Behind The Groove-Teena Marie–Behind The Groove.flac",
		"2-09.The Gap Band–Outstanding-The Gap Band–Outstanding.flac",
		"2-10.Howard Johnson–So Fine-Howard Johnson–So Fine.flac",
		"2-11.Midnight Star–Curious-Midnight Star–Curious.flac",
		"2-12.Keni Burke–Risin To The Top (Give It All You Got)-Keni Burke–Risin To The Top (Give It All You Got).flac",
		"2-13.Mac Band Featuring The McCampbell Brothers–Roses Are Red-Mac Band Featuring The McCampbell Brothers–Roses Are Red.flac",
		"2-14.Patrice Rushen–Forget Me Nots-Patrice Rushen–Forget Me Nots.flac",
		"2-15.Brass Construction–Movin-Brass Construction–Movin.flac",
		"2-16.Melisa Morgan–Fools Paradise-Melisa Morgan–Fools Paradise.flac",
		"2-17.Heatwave Featuring Jocelyn Brown–Feel Like Making Love-Heatwave Featuring Jocelyn Brown–Feel Like Making Love.flac",
		"2-18.Light Of The World–London Town-Light Of The World–London Town.flac"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		// peel off track info
		auto strings = count_separators(rootname, ".", 1);
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\'.\'" << " strings.size=" << strings.size();

		// check if we have dup artist-name
		auto expected_len = strings[1].size() / 2;
		std::vector<std::string_view> part{
				{ strings[1].data(), expected_len },
				{ strings[1].data() + expected_len + 1, expected_len },
			};
		EXPECT_EQ(part[0], part[1])
			<< " parts[0]=\'" << part[0] << "\" len=" << part[0].size() << '\n'
			<< " parts[1]=\'" << part[1] << "\" len=" << part[1].size() << '\n';

		// separate artist-name
		auto coded_name = count_separators(part[0], "–"); // node: not "-"
		ASSERT_EQ(coded_name.size(), 2)
			<< " part[0]=\'" << part[0] << "\' len=" << part[0].size() << '\n'
			<< " coded_name.size=" << coded_name.size() << '\n';

		auto scheme = std::make_unique<AbcdeMultiCdScheme2>(coded_name[0], strings[0], coded_name[1]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
