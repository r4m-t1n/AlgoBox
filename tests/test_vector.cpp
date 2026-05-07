#include <gtest/gtest.h>
#include "algobox.hpp"

TEST(VectorTest, NoModeException){
    algobox::core<int> c({10, 20});

    EXPECT_THROW(c.v[0], algobox::NoAlgoModeSelected);

}

TEST(VectorTest, EmptyCons){
    algobox::vector<int> v;
    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, SizeCons){
    algobox::vector<int> v(10);
    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 13);
    EXPECT_EQ(v[4], 0);
    EXPECT_EQ(v[12], 3);
    EXPECT_THROW(v.at(13), algobox::OutOfRange);
}

TEST(VectorTest, InitializerCons){
    algobox::vector<int> v({1,2,3,4,5,6});
    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v[8], 3);
    EXPECT_THROW(v.at(10), algobox::OutOfRange);
}

TEST(VectorTest, StdVecCons){
    std::vector<int> v_std = {1,2,3,4,5,6};
    algobox::vector<int> v(v_std);

    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v[8], 3);
    EXPECT_THROW(v.at(10), algobox::OutOfRange);
}

TEST(VectorTest, ArrayCons){
    int a[] = {1,2,3,4,5,6};
    algobox::vector<int> v(a, 6);

    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v[8], 3);
    EXPECT_THROW(v.at(10), algobox::OutOfRange);
}

TEST(VectorTest, BaseCons){
    int a[] = {1,2,3,4,5,6};
    algobox::vector<int> v(a, 6, 6, 360);

    v.mode = SEARCH;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v[8], 3);
    EXPECT_THROW(v.at(10), algobox::OutOfRange);
}

TEST(VectorTest, CopyCons_Assignment){
    algobox::vector<int> v1 ({1,2,3,4,5});

    {
        algobox::vector<int> v2(v1);
        v1.mode = SEARCH;

        EXPECT_THROW(v2[2], algobox::NoAlgoModeSelected);
    }

    v1.mode = SEARCH;

    algobox::vector<int> v2 (v1);

    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_NE(v1.get_data_ptr(), v2.get_data_ptr());

    v2 = v1;

    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v2[3], 4);

    v1.push_back(6);

    EXPECT_EQ(v1.size(), 6);
    EXPECT_EQ(v2.size(), 5);
}

TEST(VectorTest, MoveCons_Assignment){
    int a[] = {1,2,3,4,5,6};
    algobox::vector<int> v1 (a, 5, 5, 5);

    const int* p = v1.get_data_ptr();

    algobox::vector<int> v2(std::move(v1));
    v1.mode = SEARCH;

    EXPECT_THROW(v2[2], algobox::NoAlgoModeSelected);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_EQ(v1.width_limit(), 5);
    EXPECT_EQ(v1.get_data_ptr(), nullptr);

    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 5);
    EXPECT_EQ(v2.width_limit(), 5);
    EXPECT_EQ(v2.get_data_ptr(), p);

    algobox::vector<int> v3 = std::move(v2);

    EXPECT_EQ(v2.get_data_ptr(), nullptr);
    EXPECT_EQ(v3.get_data_ptr(), p);
}

TEST(VectorTest, Capacity){
    int a[] = {1,2};
    algobox::vector<int> v(a, 2, 2, 360);

    v.mode = SEARCH;

    EXPECT_EQ(v.capacity(), 2);

    v.push_back(1);
    EXPECT_EQ(v.capacity(), 4);

    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.capacity(), 8);
    EXPECT_EQ(v.size(), 5);
}

TEST(VectorTest, WidthLimit){
    int a[] = {1,2};
    algobox::vector<int> v(a, 2, 2, 5);

    v.mode = SEARCH;

    EXPECT_EQ(v.capacity(), 2);

    v.push_back(1);
    EXPECT_EQ(v.capacity(), 4);

    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.capacity(), 5);
    EXPECT_EQ(v.width_limit(), 5);

    EXPECT_THROW(v.push_back(1), algobox::SizeLimitException);
}

TEST(VectorTest, Maximum_Minimum){
    algobox::vector<int> v ({-100, -10, 0, 10, 20, 20, 40});
    v.mode = SEARCH;

    EXPECT_EQ(v.get_max(), 40);
    EXPECT_EQ(v.get_min(), -100);

    v.clear();

    EXPECT_EQ(v.get_max(), 0);
    EXPECT_EQ(v.get_min(), 0);
}


TEST(VectorTest, Brackets){
    algobox::core<int> c({10, 20});
    c.v.mode = SEARCH;

    int x = c.v[0];
    c++;
    int y = c.v[1];
    c++;
    int z = c.v[1];
    c++;

    EXPECT_EQ(c.v.nodes.front(), 0);
    c.v.nodes.pop();
    EXPECT_EQ(c.v.nodes.front(), 1);
    c.v.nodes.pop();
    EXPECT_EQ(c.v.nodes.front(), 1);
    c.v.nodes.pop();

}