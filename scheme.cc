#include "scheme.hpp"

#include <spdlog/spdlog.h>

#include <vector>
#include <utility>

namespace {
	// tokenize by " - "
	std::vector<std::string_view> count_separators(std::string_view name, std::string_view token, std::size_t max_tokens) {
		std::vector<std::string_view> strings;

		if (name.size() < token.size()) {
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
				start_pos = i + token.size();
				i += token.size();
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
			if (name[i - 1] == '.') {
				return {name.data(), i - 1};
			}
		}
		return name;
	}

	std::string_view strip_path(std::string_view name) {
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
	auto basename = strip_path(name);
	auto rootname = strip_extension(basename);
	// StudioScheme
	{
		const auto strings = count_separators(rootname, " - ", 3);
		if (strings.size() == 3 && is_numeric(strings[1])) {
//			spdlog::info("studio: {}", name);
			return std::make_unique<StudioScheme>(strings[0], strings[1], strings[2]);
		}
	}
	// DefaultScheme
	{
		const auto strings = count_separators(rootname, " ", 2);
//		spdlog::debug("strings.size={} {} {}", strings.size(), strings[0], strings[1]);
		if (strings.size() == 2 &&
		    (strings[0] == "Track") && is_numeric(strings[1])) {
			return std::make_unique<DefaultScheme>(strings[1]);
		}
	}
//	spdlog::warn("cannot determine scheme: {}", name);
	return {};
}
