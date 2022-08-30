#include <memory>
#include <string>
#include <string_view>

/*
#include <spdlog/spdlog.h>

#include <cctype>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
 */

struct Scheme {
	virtual ~Scheme() = 0;
	virtual std::string_view name() const = 0;
	virtual std::string_view artist() const = 0;
	virtual std::string_view track() const = 0;
	static std::unique_ptr<Scheme> create(std::string_view name);
};

struct StudioScheme : public Scheme {
	std::string artist_, track_, name_;
	StudioScheme(std::string_view artist, std::string_view track, std::string_view name) :
		artist_(artist),
		track_(track),
		name_(name) {
	}
	std::string_view name() const override {
		return name_;
	}
	std::string_view artist() const override {
		return artist_;
	}
	std::string_view track() const override {
		return track_;
	}
};

struct UnnamedScheme : public Scheme {
	std::string_view name() const override {
		return "Track";
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	std::string_view track() const override {
		return "01";
	}
};

/*
namespace {
	std::pair<int, std::vector<std::string_view>> n_dashes(const std::string& name) {
		int count{};
		std::vector<std::string_view> strings;

		if (name.size() < 3) {
			return {count, strings};
		}
		static const char token[] = { ' ', '-', ' ' };
		std::size_t start_pos{};
		std::size_t i;
		for (i = 0; i < name.size() - 3; ++i) {
			if (name[i] == token[0] && name[i + 1] == token[1] && name[i + 2] == token[2]) {
				++count;
				strings.emplace_back(name.data() + start_pos, i - start_pos);
				start_pos = i + 3;
				i += 2;
			}
		}
		strings.emplace_back(name.data() + start_pos, i - start_pos);

		return {count, strings};
	}

	std::string strip_extension(const std::string& name) {
		if (const char* p = std::strrchr(name.c_str(), '/')) {
			return {name.c_str(), p};
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
	}
}

Scheme::~Scheme() {
}

std::unique_ptr<Scheme> Scheme::create(const std::string& name) {
	auto basename = strip_extension(name);
	auto [nspaces, strings] = n_dashes(basename);
	switch (nspaces) {
	case 2:
		if (strings.size() == 3 &&
		    !is_numeric(strings[0]) && is_numeric(strings[1]) && !is_numeric(strings[2])) {
			spdlog::info("studio: {}", name);
			return std::make_unique<StudioScheme>(strings[0], strings[1], strings[2]);
		}
		break;
	}
	spdlog::warn("cannot determine scheme: {}", name);
	return {};
}

std::vector<std::string> read(const char* name) {
	std::vector<std::string> lines;
	std::string line;
	std::ifstream is(name);
	while (std::getline(is, line)) {
		if (const char* p = std::strrchr(line.c_str(), '/')) {
			lines.emplace_back(p + 1, line.c_str() + line.size() - p - 1);
		} else {
			lines.emplace_back(std::move(line));
		}
	}
	return lines;
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		const auto files{ read(argv[i]) };
		for (const auto& file : files) {
			auto scheme = Scheme::create(file);
			if (!scheme) std::exit(1);
		}
	}
}
 */
