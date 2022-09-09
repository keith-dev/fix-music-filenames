#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(PurchasedStudioSchemeTest, decode) {
	std::vector<std::string_view> names{
		"Various Artists - 01. Touch Down (feat. Nicki Minaj & Vy.mp3",
		"Various Artists - 02. Life.mp3",
		"Various Artists - 03. One Way.mp3",
		"Various Artists - 04. Government.mp3",
		"Various Artists - 05. Hurtin' Me.mp3",
		"Various Artists - 06. Never Die.mp3",
		"Various Artists - 07. JuJu.mp3",
		"Various Artists - 08. Paradise Plum.mp3",
		"Various Artists - 09. Lights Out.mp3",
		"Various Artists - 10. Made To Fall In Love.mp3",
		"Various Artists - 11. Marijuana (feat. Damian 'Jr. Gong'.mp3",
		"Various Artists - 11. Marijuana (feat. Damian Marley).mp3",
		"Various Artists - 12. Banks Of The Hope (feat. Popcaan) .mp3",
		"Various Artists - 13. Keep The Same Energy.mp3",
		"Various Artists - 14. Owna Lane.mp3",
		"Various Artists - 15. Land Of Sunshine.mp3",
		"Various Artists - 16. To See.mp3",
		"Various Artists - 17. Heaven (Ready Fi Di Feeling).mp3",
		"Various Artists - 18. Guess Who_ (feat. Mykal Rose).mp3",
		"Various Artists - 19. The Unforgiven (feat. Raging Fyah).mp3"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		auto strings = count_separators(rootname, " - ", 1);
		ASSERT_TRUE(static_cast<std::size_t>(2) == strings.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " token=" << "\' - \'" << " strings.size=" << strings.size();

		auto second = count_separators(strings[1], ". ", 1);
		ASSERT_TRUE(static_cast<std::size_t>(2) == second.size())
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " strings[1]=\'" << strings[1] << "\' len=" << strings[1].size()
			<< " token=" << "\'. \'" << " second,size=" << second.size();
		ASSERT_TRUE(static_cast<std::size_t>(2) == second[0].size()) << second[0];
		ASSERT_TRUE(is_numeric(second[0])) << second[0];
		ASSERT_TRUE(second.size() == 2 && second[0].size() == 2 && is_numeric(second[0]));

		auto scheme = PurchasedStudioScheme::create(name);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
