
// 4_SuiteFixture.cpp

#include <unistd.h>  // sleep
#include <string>

// SUT
// 가정: Connect / Disconnect 느리다면..
class Terminal {
public:
	void Connect() {
		printf("Connecting...\n");
		sleep(2);
	}

	void Disconnect() {
		printf("Disconnecting...\n");
		sleep(1);
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

// 픽스쳐의 설치/해체로 인해서 테스트에서 "느린 테스트"의 문제가 발생한다.
//  - Slow Test
//   : 테스트가 너무 느려서, 개발자들이 코드가 변경되어도 테스트를 수행하지 않는다.
//     테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//    => Suite Fixture SetUp / TearDown
//    => xUnit Test Framework이 제공하는 기능입니다.

// Suite SetUp(); - static
// TestSuite* ts = new TestSuite;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;

// TestSuite* ts = new TestSuite;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;

// TestSuite* ts = new TestSuite;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;
// Suite TearDown(); - static


#if 1
class TerminalTest : public testing::Test {
protected:
	static Terminal* terminal;

	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
		terminal = new Terminal;
		terminal->Connect();
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
		terminal->Disconnect();
		delete terminal;
	}

	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}
};

Terminal* TerminalTest::terminal = nullptr;

namespace {
	std::string test_id = "test_id";
	std::string test_password = "test_password";
};

TEST_F(TerminalTest, foo) {

}

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
protected:
	Terminal* terminal;

	TerminalTest() : terminal(nullptr) {}

	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
	}

	void SetUp() override {
		printf("SetUp()\n");
		terminal = new Terminal;
		terminal->Connect();
	}

	void TearDown() override {
		printf("TearDown()\n");
		terminal->Disconnect();
		delete terminal;
	}
};

namespace {
	std::string test_id = "test_id";
	std::string test_password = "test_password";
};

TEST_F(TerminalTest, foo) {

}

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


































