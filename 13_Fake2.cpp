
#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};


class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* user) {
		// ...
		database->SaveUser(user->GetName(), user);
	}

	User* Load(const std::string& name) {
		// ...
		return database->LoadUser(name);
	}
};
//-----------------------------

#include <gmock/gmock.h>
#include <map>

using testing::_;

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;

public:
	FakeDatabase() {
		DelegateToFake();
	}

	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));

private:
	void DelegateToFake() {
		ON_CALL(*this, SaveUser).WillByDefault([this](const std::string& name, User* user) {
			data[name] = user;
		});

		ON_CALL(*this, LoadUser).WillByDefault([this](const std::string& name) {
			return data[name];
		});
	}
};

static bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}
static bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

// 객체를 문자열로 표현하는 함수
static std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age= " << user.GetAge() << ")";
}

using testing::NiceMock;

TEST(UserManagerTest, SaveLoadTest) {
	NiceMock<FakeDatabase> fake;
	// fake.DelegateToFake();
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	// ==
	EXPECT_EQ(expected, *actual) << "User를 저장하고 불러왔을 때";
	// EXPECT_NE(expected, *actual) << "User를 저장하고 불러왔을 때";
}
