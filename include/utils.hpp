#pragma once

#include <cstring>
#include <limits>
#include <string>
#include <string_view>
#include <vector>
#include <utility>

//----------------------------------------------------------------------------
//
inline
std::string_view trim_leading(std::string_view in, char token) {
	for (std::size_t i = 0; i != in.size(); ++i) {
		if (in[i] != token) {
			return {in.data() + i, in.size() - i};
		}
	}
	return {};
}

inline
std::string_view trim_trailing(std::string_view in, char token) {
	for (std::size_t i = in.size(); i; --i) {
		if (in[i - 1] != token) {
			return {in.data(), i};
		}
	}
	return {};
}

inline
std::string_view trim(std::string_view in, char token = ' ') {
	return trim_leading(trim_trailing(in, token), token);
}

inline
std::string_view trim_leading(std::string_view in, std::string_view token) {
	if (in.size() < token.size()) {
		return in;
	}
	std::size_t i = 0;
	std::size_t mx = in.size() - token.size();
	while (i != mx) {
		if (std::memcmp(in.data() + i, token.data(), token.size()) == 0) {
			i += token.size();
		} else {
			return {in.data() + i, in.size() - 1};
		}
	}
	return {};
}

inline
std::string_view trim_trailing(std::string_view in, std::string_view token) {
	if (in.size() < token.size()) {
		return in;
	}
	std::size_t i = in.size() - token.size();
	while (i) {
		if (std::memcmp(in.data() + i - 1, token.data(), token.size()) == 0) {
			i -= token.size();;
		} else {
			return {in.data(), i};
		}
	}
	return {};
}

inline
std::string_view trim(std::string_view in, std::string_view token = "\t ") {
	return trim_leading(trim_trailing(in, token), token);
}

// tokenize
inline
std::vector<std::string_view>
count_separators(std::string_view in, std::string_view token,
                 std::size_t max_tokens = std::numeric_limits<std::size_t>::max()) {
	std::vector<std::string_view> strings;

//	auto name = trim(in, token);
	auto name = in;
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
				// a name may also contain token, so we pick the first max_tokens
				continue;
			}
			break;
		}
		++i;
	}
	strings.emplace_back(name.data() + start_pos, name.size() - start_pos);
	return strings;
}

inline
std::string_view strip_extension(std::string_view name) {
	std::size_t i;
	for (i = name.size(); i; --i) {
		if (name[i - 1] == '.') {
			return {name.data(), i - 1};
		}
	}
	return name;
}

inline
std::string_view strip_path(std::string_view name) {
	std::size_t i;
	for (i = name.size(); i; --i) {
		if (name[i - 1] == '/') {
			return {name.data() + i, i - 1};
		}
	}
	return name;
}

inline
std::string replace_with_spaces(std::string_view in, char token) {
	std::string str(in.size(), ' ');
	for (std::size_t i = 0; i != in.size(); ++i) {
		if (in[i] != token) {
			str[i] = in[i];
		}
	}
	return str;
}

inline
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

inline
bool has_space(std::string_view str) {
	for (auto ch : str) {
		if (std::isspace(ch)) {
			return true;
		}
	}
	return false;
/*
	return std::ranges::one_of(str.cbegin(), str.cend(),
			                   [](auto ch){ return std::isspace(ch); });
 */
}
