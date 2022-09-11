#pragma once

#include <limits>
#include <string>
#include <string_view>
#include <vector>

//----------------------------------------------------------------------------
//

// remove all instances of token from the beginning of string_view
inline
std::string_view trim_leading(std::string_view in, char token) {
	for (std::size_t i = 0; i != in.size(); ++i) {
		if (in[i] != token) {
			return {in.data() + i, in.size() - i};
		}
	}
	return {};
}

// remove all instances of token from the end of string_view
inline
std::string_view trim_trailing(std::string_view in, char token) {
	for (std::size_t i = in.size(); i; --i) {
		if (in[i - 1] != token) {
			return {in.data(), i};
		}
	}
	return {};
}

// remove all instances of token from the beginning and end of string_view
inline
std::string_view trim(std::string_view in, char token) {
	return trim_leading(trim_trailing(in, token), token);
}

// remove all instances of any token in tokens from the beginning of string_view
inline
std::string_view trim_leading(std::string_view in, std::string_view token) {
	for (std::size_t i = 0; i != in.size(); ) {
		bool found{};
		for (std::size_t j = 0; i != in.size() && j != token.size(); ++j) {
			if (in[i] == token[j]) {
				++i;
				found = true;
				break;
			}
		}

		if (!found) {
			return {in.data() + i, in.size() - i};
		}
	}
	return {};
}

// remove all instances of any token in tokens from the end of string_view
inline
std::string_view trim_trailing(std::string_view in, std::string_view token) {
	for (std::size_t i = in.size(); i > 0; ) {
		bool found{};
		for (std::size_t j = 0; i > 0 && j != token.size(); ++j) {
			if (in[i - 1] == token[j]) {
				--i;
				found = true;
				break;
			}
		}

		if (!found) {
			return {in.data(), i};
		}
	}
	return {};
}

// remove all instances of any token in tokens from the beginning and end of string_view
inline
std::string_view trim(std::string_view in, std::string_view token = "\t ") {
	return trim_leading(trim_trailing(in, token), token);
}

// tokenize
// return a vector of string_views separated by entire token
inline
std::vector<std::string_view>
count_separators(std::string_view in, std::string_view token,
                 std::size_t max_tokens = std::numeric_limits<std::size_t>::max()) {
	std::vector<std::string_view> strings;

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

// strip extension if present
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
std::string_view extension(std::string_view name) {
	if (name.empty()) {
		return name;
	}
	// linear search for last .
	std::size_t i = name.size();
	while (i > 0 && name[i] != '.') {
		--i;
	}

	if (name[i] == '.') {
		return {name.data() + i, name.size() - i};
	}
	return {};
}

// string path if present
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

// replace token with space, return a new string
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
