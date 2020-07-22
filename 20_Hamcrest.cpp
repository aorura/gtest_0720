
#include <gmock/gmock.h>

// Hamcrest
//  : 단언문을 사용할 때, 좀더 문장에 가까운 표현할 수 있도록 하는
//    비교 표현의 확장 라이브러리
//
//    => Matcher를 단언문에서 사용할 수 있도록 해줍니다.

class User {
public:
	std::string name;                             // Field
	User() : name("Bob") {}

	int GetAge() const { return 420; }

	std::string GetName() const { return "Tom"; } // Getter - Property(접근자 메소드)

	std::vector<int> GetArray() const {
		std::vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);

		return v;
	}
};

using testing::AllOf;
using testing::Lt;
using testing::Gt;
using testing::MatchesRegex;
using testing::ElementsAre;
using testing::UnorderedElementsAre;
using testing::Le;
using testing::Ge;
using testing::Eq;

using testing::Field;
using testing::Property;

TEST(UserTest, HamcrestTest) {
	User user;

	EXPECT_THAT(user.GetArray(), ElementsAre(10, 20, 30));
	EXPECT_THAT(user.GetArray(), UnorderedElementsAre(20, 10, 30));
	EXPECT_THAT(user.GetArray(), ElementsAre(Le(10), Ge(20), Eq(30)));

	EXPECT_EQ(42, user.GetAge()) << "Reason 1";

	// GetAge의 반환값이 1보다 크고 100보다 작은지를 검증하고 싶다.
	int age = user.GetAge();
	EXPECT_TRUE(age > 0 && age < 100);

	// Hamcrest - Google Mock
	EXPECT_THAT(user.GetAge(), AllOf(Gt(0), Lt(100)));
	EXPECT_THAT(user.GetName(), MatchesRegex("Tom"));

	EXPECT_THAT(Property(
}





