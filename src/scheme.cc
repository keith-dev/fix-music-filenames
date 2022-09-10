#include "scheme.hpp"
#include "utils.hpp"

#include <spdlog/spdlog.h>

//----------------------------------------------------------------------------
//

// PurchasedStudioScheme
// artist - track. name
// Various Artists - 02. Life.mp3
std::unique_ptr<Scheme> PurchasedStudioScheme::create(std::string_view rootname) {
	auto strings = count_separators(rootname, " - ", 1);
	if (strings.size() == 2) {
		auto second = count_separators(strings[1], ". ", 1);
		if (second.size() == 2 && second[0].size() == 2 && is_numeric(second[0])) {
			return std::make_unique<PurchasedStudioScheme>(strings[0], second[0], second[1]);
		}
	}
	return {};
}

// SpacelessScheme
// artist_-_track_-_name
// B00G7PONRI_(disc_1)_01_-_You_Ain't_Livin'.mp3
std::unique_ptr<Scheme> SpacelessScheme::create(std::string_view rootname) {
	auto strings = count_separators(rootname, "-");
	if (strings.size() == 2 && !has_space(rootname)) {
		std::string newroot = replace_with_spaces(rootname, '_');

		strings = count_separators(newroot, "-");
		if (strings.size() == 2) {
			auto firsts = count_separators(strings[0], " ");
			if (firsts.size() > 1 && is_numeric(trim_trailing(firsts.back(), ' '))) {
				firsts.back() = trim_trailing(firsts.back(), ' ');
				return std::make_unique<SpacelessScheme>(firsts.back(), strings[1]);
			}
		}
	}
	return {};
}

// StudioScheme
// artist - track - name
// Rufus with Chaka Khan - 04 - Music Man (The DJ Song).flac
std::unique_ptr<Scheme> StudioScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, " - ", 3);
	if (strings.size() == 3 && strings[1].size() == 2 && is_numeric(strings[1])) {
		return std::make_unique<StudioScheme>(strings[0], strings[1], strings[2]);
	}
	return {};
}

// DefaultScheme
// lazy: Track 01.mp3
std::unique_ptr<Scheme> DefaultScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, " ", 2);
	if (strings.size() == 2 &&
	    (strings[0] == "Track") && is_numeric(strings[1])) {
		return std::make_unique<DefaultScheme>(strings[1]);
	}
	return {};
}

// AbcdeScheme
std::unique_ptr<Scheme> AbcdeScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, ".", 1);
	if (strings.size() == 2 && is_numeric(strings[0])) {
		return std::make_unique<AbcdeScheme>(strings[0], trim(strings[1]));
	}
	return {};
}

#ifdef HIDE
// ClassicFMScheme
std::unique_ptr<Scheme> ClassicFMScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, " - ", 4);
	if (strings.size() == 4 && strings[2].size() == 2 && is_numeric(strings[2])) {
		std::string_view artist{ strings[0].data(), strings[0].size() + 3 + strings[1].size() };
		return std::make_unique<ClassicFMScheme>(artist, strings[2], strings[2]);
	}
	return {};
}

// GenericRipScheme
std::unique_ptr<Scheme> GenericRipScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, " ", 1);
	if (strings.size() > 1 && strings[0].size() == 2 && is_numeric(strings[0])) {
		return std::make_unique<GenericRipScheme>(strings[0], strings[1]);
	}
	return {};
}

// MultiCdGenericRipScheme
std::unique_ptr<Scheme> MultiCdGenericRipScheme::create(std::string_view rootname) {
	const auto strings = count_separators(rootname, " ", 1);
	if (strings.size() == 2 && strings[0].size() == 4) {
		auto ids = count_separators(strings[0], "-");
		if (ids.size() == 2 && is_numeric(ids[0]) && is_numeric(ids[1])) {
			return std::make_unique<MultiCdGenericRipScheme>(strings[0], strings[1]);
		}
	}
	return {};
}

// MultiCdGenericRipScheme2
// 1-07.Shes_strange.flac
std::unique_ptr<Scheme> MultiCdGenericRipScheme2::create(std::string_view rootname) {
	if (count_separators(rootname, " ").size() == 1) {
		std::string rootstr = replace_with_spaces(rootname, '_');

		const auto strings = count_separators(rootstr, ".", 2);
		if (strings.size() == 2 && strings[0].size() == 4) {
			auto ids = count_separators(strings[0], "-");

			if (ids.size() == 2 && is_numeric(ids[0]) && is_numeric(ids[1])) {
				return std::make_unique<MultiCdGenericRipScheme2>(strings[0], strings[1]);
			}
		}
	}
	return {};
}

// SpacelessScheme2
// Chic-08-Take_It_Off.flac
std::unique_ptr<Scheme> SpacelessScheme2::create(std::string_view rootname) {
	if (count_separators(rootname, " ").size() == 1) {
		std::string newroot = replace_with_spaces(rootname, '_');
		const auto strings = count_separators(newroot, "-", 3);
		if (strings.size() == 3) {
			return std::make_unique<SpacelessScheme2>(strings[0], strings[1], strings[2]);
		}
	}
	return {};
}
#endif // HIDE

std::unique_ptr<Scheme> Scheme::create(std::string_view name) {
	auto basename = strip_path(name);
	auto rootname = strip_extension(basename);

	if (auto p = PurchasedStudioScheme::create(rootname)) {
		spdlog::info("{}: {}", "PurchasedStudioScheme", rootname);
		return p;
	}
	if (auto p = SpacelessScheme::create(rootname)) {
		spdlog::info("{}: {}", "SpacelessScheme", rootname);
		return p;
	}
	if (auto p = StudioScheme::create(rootname)) {
		spdlog::info("{}: {}", "", rootname);
		return p;
	}
	if (auto p = DefaultScheme::create(rootname)) {
		spdlog::info("{}: {}", "DefaultScheme", rootname);
		return p;
	}
	if (auto p = AbcdeScheme::create(rootname)) {
		spdlog::info("{}: {}", "AbcdeScheme", rootname);
		return p;
	}

#ifdef HIDE
	if (auto p = ClassicFMScheme::create(rootname)) {
		spdlog::info("{}: {}", "ClassicFSchemeM", rootname);
		return p;
	}
	if (auto p = GenericRipScheme::create(rootname)) {
		spdlog::info("{}: {}", "GenericRipScheme", rootname);
		return p;
	}
	if (auto p = MultiCdGenericRipScheme::create(rootname)) {
		spdlog::info("{}: {}", "MultiCdGenericRipScheme", rootname);
		return p;
	}
	if (auto p = MultiCdGenericRipScheme2::create(rootname)) {
		spdlog::info("{}: {}", "MultiCdGenericRipScheme2", rootname);
		return p;
	}
	if (auto p = SpacelessScheme2::create(rootname)) {
		spdlog::info("{}: {}", "SpacelessScheme2", rootname);
		return p;
	}
#endif // HIDE
//	spdlog::debug("cannot determine scheme: {}", name);
	return {};
}
