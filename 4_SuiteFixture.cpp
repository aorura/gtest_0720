
// 4_SuiteFixture.cpp

#include <string>

// SUT
class Terminal {
public:
	void Connect() {

	}

	void Disconnect() {

	}

	void Login(const std::string& id, const std::string& password) {

	}

	void Logout() {

	}

	bool IsLogin() {
		return true;
	}
};

//-----------------
#include <gtest/gtest.h>

#if 1
class TerminalTest : public testing::Test {
protected:
	Terminal* terminal;

	TerminalTest() : terminal(nullptr) {}

	void SetUp() override {
		terminal = new Terminal;
		terminal->Connect();
	}

	void TearDown() override {
		terminal->Disconnect();
		delete terminal;
	}
};

namespace {
	std::string test_id = "test_id";
	std::string test_password = "test_password";
};

TEST_F(TerminalTest, LoginTest) {
	terminal->Login(test_id, test_password);

	ASSERT_TRUE(terminal->IsLogin()) << "로그인하였을 때";
}

TEST_F(TerminalTest, LogoutTest) {
	terminal->Login(test_id, test_password);
	terminal->Logout();

	ASSERT_FALSE(terminal->IsLogin()) << "로그아웃하였을 때";
}
#endif

#if 0
class TerminalTest : public testing::Test {
};

TEST_F(TerminalTest, LoginTest) {
	Terminal* terminal = new Terminal;
	terminal->Connect();
	std::string test_id = "test_id";
	std::string test_password = "test_password";

	terminal->Login(test_id, test_password);

	// ASSERT_EQ(true, terminal->IsLogin());
	ASSERT_TRUE(terminal->IsLogin()) << "로그인하였을 때";

	terminal->Disconnect();
	delete terminal;
}

TEST_F(TerminalTest, LogoutTest) {
	Terminal* terminal = new Terminal;
	terminal->Connect();
	std::string test_id = "test_id";
	std::string test_password = "test_password";

	terminal->Login(test_id, test_password);
	terminal->Logout();

	ASSERT_FALSE(terminal->IsLogin()) << "로그아웃하였을 때";

	terminal->Disconnect();
	delete terminal;
}
#endif


































