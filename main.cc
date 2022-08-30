#include "scheme.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>

#include <spdlog/spdlog.h>

#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

//----------------------------------------------------------------------------
//

using path_type = std::vector<std::string>;

class Ctx {
public:
	void onDir(long level, std::string_view name);
	void onFile(long level, std::string_view name);
	[[nodiscard]] std::string path_to_string() const;

private:
	path_type path;
	std::vector<path_type> paths;
};

void scan(Ctx& ctx, char* path_argv[]) {
	auto flags = FTS_COMFOLLOW | FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV;
	if (auto* fs = fts_open(path_argv, flags, nullptr)) {
		while (auto* node = fts_read(fs)) {
			switch (node->fts_info) {
			case FTS_F:
				ctx.onFile(node->fts_level, {node->fts_name, node->fts_namelen});
				break;
			case FTS_D:
				ctx.onDir(node->fts_level, {node->fts_name, node->fts_namelen});
				break;
			default:
				;
			}
		}
		fts_close(fs);
	}
}

void Ctx::onFile(long level, std::string_view name) {
	static auto last_path = path;
	if (last_path != path) {
		last_path = path;
//		spdlog::info("level={} path={}", level, path_to_string());
	}
//	spdlog::info("file: {}{}", std::string(2*static_cast<std::size_t>(level), '-'), name);
	auto scheme = Scheme::create(name);
	if (!scheme) {
		throw std::domain_error{fmt::format("unknown format: {}", name)};
	}
}

void Ctx::onDir(long level, std::string_view name) {
	if (path.empty()) {
		path.emplace_back(name);
	} else if (static_cast<std::size_t>(level) == path.size()) {
		path.emplace_back(name);
	} else if (static_cast<std::size_t>(level + 1) < path.size()) {
		path.resize(static_cast<std::size_t>(level + 1));
		path.back() = name;
	} else {
	}
}

std::string Ctx::path_to_string() const {
	std::string fullpath;
	if (path.size()) {
		for (std::size_t i = 0; i < (path.size() - 1); ++i) {
			fullpath += path[i] + "/";
		}
		fullpath += path[path.size() - 1];
	}
	return fullpath;
}

int main(int argc, char* argv[])
try {
	spdlog::default_logger().get()->set_level(spdlog::level::debug);
	Ctx ctx;
	scan(ctx, argv + 1);
}
catch (const std::exception& e) {
	spdlog::error("fatal: {}", e.what());
}
