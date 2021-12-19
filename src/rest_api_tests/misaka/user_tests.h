#ifndef USERTESTS_H
#define USERTESTS_H

#include <string>

class UserTests
{
public:
    UserTests();
    bool runTest();

private:
    bool create_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    std::string m_userName = "tsurugi";
    std::string m_password = "new password";
    bool m_isAdmin = true;
    std::string m_roles = "tester";
    std::string m_projects = "tester";
};

#endif // USERTESTS_H
