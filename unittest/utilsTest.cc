#include "utils.hpp"

#include <gtest/gtest.h>

namespace {
	std::string_view name{" + + Hello World - -  "};
}

TEST(utilsTest, CharTrimLeading) {
	EXPECT_EQ(name, trim_leading(name, '+'));
	EXPECT_EQ(name, trim_leading(name, '-'));
	EXPECT_EQ(name.size(), trim_leading(name, ' ').size() + 1);
}

TEST(utilsTest, CharTrimTrailing) {
	EXPECT_EQ(name, trim_trailing(name, '+'));
	EXPECT_EQ(name, trim_trailing(name, '-'));
	EXPECT_EQ(name.size(), trim_trailing(name, ' ').size() + 2);
}

TEST(utilsTest, StringViewTrimLeading) {
	EXPECT_EQ(name, trim_leading(name, "0123456789"))
		<< "strings should match";
	EXPECT_EQ(name.data(), trim_leading(name, "0123456789").data())
		<< "strings should be the same memory locations";

	EXPECT_EQ(name.size(), trim_leading(name, "+ ").size() + 5);
	EXPECT_EQ(name.size(), trim_leading(name, "- ").size() + 1);
	EXPECT_EQ(static_cast<std::size_t>(0), trim_leading(name, " +-HelloWorld").size());
}

TEST(utilsTest, StringViewTrimTrailing) {
	EXPECT_EQ(name, trim_trailing(name, "0123456789"))
		<< "strings should match";
	EXPECT_EQ(name.data(), trim_trailing(name, "0123456789").data())
		<< "strings should be the same memory locations";
	EXPECT_EQ(name.data(), trim_trailing(name, " -").data())
		<< "strings should be the same memory locations";

	EXPECT_EQ(name.size(), trim_trailing(name, "+ ").size() + 2);
	EXPECT_EQ(name.size(), trim_trailing(name, "- ").size() + 6);
	EXPECT_EQ(static_cast<std::size_t>(0), trim_trailing(name, " +-HelloWorld").size());
}
