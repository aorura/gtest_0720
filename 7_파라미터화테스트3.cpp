
#include <gtest/gtest.h>

const char* animals[] = { "Dog", "Cat" };
enum Color {
	BLACK, GRAY, WHITE,
};

class AnimalTest : public testing::TestWithParam<
						std::tuple<const char*, Color>> {
protected:
	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}
};

using testing::Combine;
using testing::ValuesIn;
using testing::Values;

INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest,
	Combine(ValuesIn(animals), Values(BLACK, GRAY, WHITE)));

TEST_P(AnimalTest, AnimalLookAndFeel) {
	std::tuple<const char*, Color> v = GetParam();
	// auto v = GetParam();
	
	const char* animal = std::get<0>(v);
	Color c = std::get<1>(v);

	printf("%s(%d)\n", animal, c);
}
