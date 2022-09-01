#pragma once

#include "scheme.hpp"

#include <map>
#include <list>
#include <string>
#include <string_view>
#include <vector>

//----------------------------------------------------------------------------
//
using path_type = std::vector<std::string>;

class FileSystemContext {
public:
	virtual ~FileSystemContext() = default;
	virtual void onDir(long level, std::string_view name);
	virtual void onFile(long level, std::string_view name);

	[[nodiscard]] static bool isFile(std::string_view name);
	[[nodiscard]] static std::string path_to_string(const path_type& path);

private:
	path_type path_;
	std::map<std::string, std::list<std::unique_ptr<Scheme>>> files_;
};
