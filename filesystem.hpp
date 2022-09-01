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
	[[nodiscard]] virtual bool isFile(std::string_view name) const;
	[[nodiscard]] std::string path_to_string() const;

private:
	path_type path_;
	std::map<path_type, std::list<std::unique_ptr<Scheme>>> files_;
//	std::vector<path_type> paths_;
};
