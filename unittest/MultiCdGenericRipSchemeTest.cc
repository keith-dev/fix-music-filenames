#include "scheme.hpp"
#include "utils.hpp"

#include <gtest/gtest.h>

TEST(MultiCdGenericRipSchemeTest, decode) {
	std::vector<std::string_view> names{
		"101-stephen_marley_ft_damian_jr_gong_marley_and_buju_banton-jah_army.mp3",
		"102-i-octane-nuh_ramp_wid_we.mp3",
		"103-assassin-how_mi_feel.mp3",
		"104-mavado-peppa.mp3",
		"105-shabba_ranks-none_ah_dem.mp3",
		"106-cham_ft_mykal_rose_and_rodney_price-stronger.mp3",
		"107-shaggy_and_alaine-for_yur_eyez_only.mp3",
		"108-vybz_kartel-whine_(wine).mp3",
		"109-gyptian-duggu_duggu.mp3",
		"110-richie_spice-black_woman.mp3",
		"111-stevie_face-cant_go_round_it.mp3",
		"112-tarrus_riley-groovy_little_thing.mp3",
		"113-beres_hammond-pull_up.mp3",
		"114-courtney_john-everyday.mp3",
		"115-queen_ifrica-times_like_these.mp3",
		"116-alborosie_ft_camilla-one_draw.mp3"
	};

	// run thru individual steps, the call the creator
	for (auto name : names) {
		auto basename = strip_path(name);
		auto rootname = strip_extension(basename);

		ASSERT_FALSE(has_space(rootname))
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n";

		std::string newroot = replace_with_spaces(rootname, '_');
		auto strings = count_separators(newroot, "-");
		ASSERT_TRUE(strings.size() > 2 && is_numeric(strings[0]))
			<< " rootname=\'" << rootname << "\' len=" << rootname.size() << "\n"
			<< " newname=\'" << newroot << "\' len=" << newroot.size() << "\n"
			<< " strings.size=" << strings.size() << "\n"
			<< " is_numeic(" << strings[0] << ")=" << std::boolalpha << is_numeric(strings[0]) << "\n";

		auto scheme = MultiCdGenericRipScheme::create(rootname);
		ASSERT_TRUE(scheme.get() != nullptr);
	}
}
