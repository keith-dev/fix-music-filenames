#include "filesystem.hpp"
#include "scheme.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#include <spdlog/spdlog.h>

#include <stdexcept>

//----------------------------------------------------------------------------
//

void FileSystemContext::onFile(long level, std::string_view name) {
	static auto last_path = path_;
	if (last_path != path_) {
		last_path = path_;
		spdlog::info("level={} path={}", level, path_to_string());
	}
//	spdlog::info("file: {}{}", std::string(2*static_cast<std::size_t>(level), '-'), name);
	auto scheme = Scheme::create(name);
	if (!scheme) {
//		throw std::domain_error{fmt::format("unknown format: {}", name)};
		spdlog::error("unknown format: {}", name);
	}
}

void FileSystemContext::onDir(long level, std::string_view name) {
	path_.resize(level + 1);
	path_.back() = name;
}

bool FileSystemContext::isFile(std::string_view name) const {
	struct stat info;
	int rc = ::stat(name.data(), &info); // assume null terminated after name.size()
	return (rc == 0) && (info.st_mode & S_IFREG);
}

std::string FileSystemContext::path_to_string() const {
	std::string fullpath;
	if (!path_.empty()) {
		for (std::size_t i = 0; i < (path_.size() - 1); ++i) {
			fullpath += path_[i] + "/";
		}
		fullpath += path_.back();
	}
	return fullpath;
}
