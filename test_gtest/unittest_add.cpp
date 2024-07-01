#include "gtest/gtest.h"
#include "add.h"

class Add_Test : public testing::Test
{
public:
    virtual void SetUp() override
    {}
    virtual void TearDown() override
    {}
};

TEST_F(Add_Test, positive)
{
    int r = add(10, 20);
    EXPECT_EQ(r, 30);
}

TEST(Add, positive)
{
    int r = add(10, 20);
    EXPECT_EQ(r, 30);
}

// int main(int argc, char** argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }