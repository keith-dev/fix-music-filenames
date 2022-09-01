#include "filesystem.hpp"

//#include <sys/types.h>
//#include <sys/stat.h>
#include <fts.h>

#include <spdlog/spdlog.h>

#include <exception>

//----------------------------------------------------------------------------
//

void scan(FileSystemContext* ctx, char* path_argv[]) {
	for (int i = 0; path_argv[i]; ++i) {
		if (ctx->isFile(path_argv[i])) {
			ctx->onFile(0, path_argv[i]);
		}
	}
	auto flags = FTS_COMFOLLOW | FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV;
	if (auto* fs = fts_open(path_argv, flags, nullptr)) {
		while (auto* node = fts_read(fs)) {
			switch (node->fts_info) {
			case FTS_F:
				ctx->onFile(node->fts_level, {node->fts_name, node->fts_namelen});
				break;
			case FTS_D:
				ctx->onDir(node->fts_level, {node->fts_name, node->fts_namelen});
				break;
			default:
				;
			}
		}
		fts_close(fs);
	}
}

int main(int argc, char* argv[])
try {
	spdlog::default_logger()->set_level(spdlog::level::debug);
	auto ctx = std::make_unique<FileSystemContext>();
	scan(ctx.get(), argv + 1);
}
catch (const std::exception& e) {
	spdlog::error("fatal: {}", e.what());
}
