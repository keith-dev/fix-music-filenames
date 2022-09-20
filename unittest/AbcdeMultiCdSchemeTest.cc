#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(AbcdeMultiCdSchemeTest, decode) {
	std::vector<std::string_view> names{
		"1-01.Sister Sledge  Thinking of You-Sister Sledge  Thinking of You.flac",
		"1-02.Chaka Khan  I’m Every Woman-Chaka Khan  I’m Every Woman.flac",
		"1-03.Chic  Good Times-Chic  Good Times.flac",
		"1-04.Change  Change of Heart-Change  Change of Heart.flac",
		"1-05.Juicy  Sugar Free-Juicy  Sugar Free.flac",
		"1-06.The Isley Brothers  Between the Sheets-The Isley Brothers  Between the Sheets.flac",
		"1-07.Marvin Gaye  Sexual Healing-Marvin Gaye  Sexual Healing.flac",
		"1-08.Maze  Twilight-Maze  Twilight.flac",
		"1-09.Lonnie Liston Smith  Expansions-Lonnie Liston Smith  Expansions.flac",
		"1-10.Rocker’s Revenge  Walking on Sunshine-Rocker’s Revenge  Walking on Sunshine.flac",
		"1-11.Royalle Delite  (I’ll Be a) Freak for You-Royalle Delite  (I’ll Be a) Freak for You.flac",
		"1-12.Evelyn “Champagne” King  Love Come Down-Evelyn “Champagne” King  Love Come Down.flac",
		"1-13.McFadden & Whitehead  Ain’t No Stoppin’ Us Now-McFadden & Whitehead  Ain’t No Stoppin’ Us Now.flac",
		"1-14.Dayton  The Sound of Music-Dayton  The Sound of Music.flac",
		"1-15.Surface  Happy-Surface  Happy.flac",
		"1-16.The Controllers  Stay-The Controllers  Stay.flac",
		"1-17.Luther Vandross  I Really Didn’t Mean It-Luther Vandross  I Really Didn’t Mean It.flac",
		"2-01.Cheryl Lynn  Got to Be Real-Cheryl Lynn  Got to Be Real.flac",
		"2-02.Archie Bell & The Drells  Don’t Let Love Get You Down-Archie Bell & The Drells  Don’t Let Love Get You Down.flac",
		"2-03.The B.B. & Q. Band  Dreamer-The B.B. & Q. Band  Dreamer.flac",
		"2-04.Kashif  I Just Gotta Have You (Lover Turn Me on)-Kashif  I Just Gotta Have You (Lover Turn Me on).flac",
		"2-05.Jean Carn  Don’t Let It Go to Your Head-Jean Carn  Don’t Let It Go to Your Head.flac",
		"2-06.Breakwater  Say You Love Me Girl-Breakwater  Say You Love Me Girl.flac",
		"2-07.The Jones Girls  Nights Over Egypt-The Jones Girls  Nights Over Egypt.flac",
		"2-08.Precious Wilson  I’ll Be Your Friend-Precious Wilson  I’ll Be Your Friend.flac",
		"2-09.Donald Byrd  Places and Spaces-Donald Byrd  Places and Spaces.flac",
		"2-10.Fatback Band  Is This the Future-Fatback Band  Is This the Future.flac",
		"2-11.Paul Laurence  There Ain’t Nothing (Like Your Loving)-Paul Laurence  There Ain’t Nothing (Like Your Loving).flac",
		"2-12.Sahara  Love So Fine-Sahara  Love So Fine.flac",
		"2-13.Windjammer  Tossing and Turning-Windjammer  Tossing and Turning.flac",
		"2-14.Glenn Jones  Finesse-Glenn Jones  Finesse.flac",
		"2-15.Thelma Houston  You Used to Hold Me So Tight-Thelma Houston  You Used to Hold Me So Tight.flac",
		"2-16.Kleeer  Intimate Connection-Kleeer  Intimate Connection.flac",
		"2-17.Atmosfear  Dancing in Outer Space-Atmosfear  Dancing in Outer Space.flac"
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

		auto track = count_separators(strings[0], "-");
		ASSERT_TRUE(static_cast<std::size_t>(2) == track.size())
			<< " strings[0]=\'" << strings[0] << "\' len=" << strings[0].size() << "\n"
			<< " track.size=" << track.size();

		auto name_part = count_separators(strings[1], "-");
		ASSERT_TRUE(static_cast<std::size_t>(2) == name_part.size())
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[1].size() << "\n"
			<< " name_part.size=" << name_part.size();

		EXPECT_EQ(name_part[0], name_part[1])
			<< " name_part[0]\'" << name_part[0] << "\' len=" << name_part[0].size() << "\n"
			<< " name_part[1]\'" << name_part[1] << "\' len=" << name_part[1].size() << "\n";

		auto coded_name = count_separators(name_part[0], "  ");
		ASSERT_TRUE(static_cast<std::size_t>(2) == coded_name.size())
			<< " coded_name.size=" << coded_name.size();

		auto scheme = std::make_unique<AbcdeMultiCdScheme>(coded_name[0], strings[0], coded_name[1]);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
