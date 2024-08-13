#include <gtest/gtest.h>



TEST(ls_ppTest, test01)
{
    int fd = open("GoogleTestLog.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);
    std::cout << "\n\nStream has been redirected!\n" << std::endl;
    printf("test log on file01:\n");
    // EXPECT_EQ(test_file("../tests/test01.txt"), EXIT_SUCCESS);
    printf("End of test01 \n\n\n");
    close(fd);
}
