#include "utils.hpp"
#include "scheme.hpp"

#include "PurchasedStudioSchemeTest.hpp"

#include <gtest/gtest.h>

TEST(PurchasedStudioTest, decode) {
#ifdef HIDE
	for (auto [title, tmp] : titles) {
		auto scheme = PurchasedStudioScheme::create(title);
		EXPECT_NE(scheme.get(), nullptr) << title;
	}
#endif // HIDE
}

