#include "scheme.hpp"

#include <spdlog/spdlog.h>

#include <vector>
#include <utility>

namespace {
	// tokenize by " - "
	std::vector<std::string_view> n_dashes(std::string_view name) {
		static const std::string_view token = " - ";
		static constexpr std::size_t max_tokens = 3;
		std::vector<std::string_view> strings;

		if (name.size() < token.size()) {
			// can't be smaller than " - "
			return strings;
		}

		auto match = [](std::string_view token, std::string_view str) -> bool {
			if (str.size() < token.size()) {
				return false;
			}
			for (std::size_t i = 0; i != token.size(); ++i) {
				if (str[i] != token[i]) {
					return false;
				}
			}
			return true;
		};
		std::size_t start_pos = 0;
		std::size_t i = 0;
		const std::size_t mx = name.size() - token.size();
		while (i < mx) {
			if (match(token, {name.data() + i, name.size() - i})) {
				strings.emplace_back(name.data() + start_pos, i - start_pos);
				start_pos = i + 3;
				i += 3;
				if (strings.size() < max_tokens - 1) {
					// a name may also contain " - ", so we pick the first 3
					continue;
				}
				break;
			}
			++i;
		}
		strings.emplace_back(name.data() + start_pos, name.size() - start_pos);
		return strings;
	}

	std::string_view strip_extension(std::string_view name) {
		std::size_t i;
		for (i = name.size(); i; --i) {
			if (name[i - 1] == '/') {
				return {name.data() + i, i - 1};
			}
		}
		return name;
	}

	bool is_numeric(std::string_view str) {
		for (auto ch : str) {
			if (!std::isdigit(ch)) {
				return false;
			}
		}
		return true;
/*
		return std::ranges::all_of(str.cbegin(), str.cend(),
				                   [](auto ch){ return std::isdigit(ch); });
 */
	}
}  // namespace

std::unique_ptr<Scheme> Scheme::create(std::string_view name) {
	auto basename = strip_extension(name);
	const auto strings = n_dashes(basename);
	switch (strings.size()) {
	case 3:
		if (!is_numeric(strings[0]) && is_numeric(strings[1]) && !is_numeric(strings[2])) {
//			spdlog::info("studio: {}", name);
			return std::make_unique<StudioScheme>(strings[0], strings[1], strings[2]);
		}
		break;
	}
//	spdlog::warn("cannot determine scheme: {}", name);
	return {};
}
