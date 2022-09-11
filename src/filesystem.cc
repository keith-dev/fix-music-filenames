#include "filesystem.hpp"
#include "utils.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#include <spdlog/spdlog.h>

#include <stdexcept>

//----------------------------------------------------------------------------
//

namespace {
template <typename COLLECTION, typename T>
inline
bool any_of(const COLLECTION &set, const T &value) {
	for (auto entry : set) {
		if (value == entry) {
			return true;
		}
	}
	return false;
}
} // namespace

void FileSystemContext::onFile(long level, std::string_view name) {
	if (!any_of(known_extensions_, extension(name))) {
		return;
	}

	static auto last_path = path_;
	if (last_path != path_) {
		last_path = path_;
		spdlog::info("level={} path={}", level, path_to_string(path_));
	}

	auto scheme = Scheme::create(name);
	if (scheme) {
		const auto key = path_to_string(path_);
		files_[key].emplace_back(std::move(scheme));
	} else {
//		throw std::domain_error{fmt::format("unknown format: {}", name)};
		spdlog::error("unknown format: {}", name);
	}
}

void FileSystemContext::onDir(long level, std::string_view name) {
	path_.resize(level + 1);
	path_.back() = name;
}

bool FileSystemContext::isFile(std::string_view name) {
	struct stat info;
	int rc = ::stat(name.data(), &info); // assume null terminated after name.size()
	return (rc == 0) && (info.st_mode & S_IFREG);
}

std::string FileSystemContext::path_to_string(const path_type& path) {
	std::string fullpath;
	if (!path.empty()) {
		for (std::size_t i = 0; i < (path.size() - 1); ++i) {
			fullpath += path[i] + "/";
		}
		fullpath += path.back();
	}
	return fullpath;
}
