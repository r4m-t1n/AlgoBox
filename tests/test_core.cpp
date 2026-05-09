#include <gtest/gtest.h>
#include "algobox.hpp"

TEST(Core, EmptyCons){
    algobox::core<int> c;
    c.v.mode = SEARCH;

    EXPECT_TRUE(c.v.empty());
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 1.0f);
    EXPECT_EQ(c.loop, 0);
    EXPECT_EQ(algobox::empty_element, static_cast<size_t>(-1));
}

TEST(Core, TimeLoopCons){
    algobox::core<int> c(0.05);
    c.v.mode = SEARCH;

    EXPECT_TRUE(c.v.empty());
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 0.05f);
}

TEST(Core, InitializerCons){
    algobox::core<int> c({1,2,3,4,5,6,7,8});
    c.v.mode = SEARCH;

    EXPECT_EQ(c.v.size(), 8);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 1.0f);
}

TEST(Core, StdVecCons){
    std::vector<int> v(10);
    algobox::core<int> c(v);
    c.v.mode = SEARCH;
    
    c.v[5] = 6;
    
    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 1.0f);
}

TEST(Core, VecCons){
    algobox::vector<int> v(10);

    algobox::core<int> c(v);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 1.0f);
}

TEST(Core, VecTimeCons){
    algobox::vector<int> v(10);
    algobox::core<int> c(v, 5.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_TRUE(c.vars.data.empty());
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 5.0f);
}


TEST(Core, VecDictCons){
    algobox::vector<int> v(10);
    
    algobox::dict d;
    d["something"] = 10;

    algobox::core<int> c(v, d);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 1.0f);
}

TEST(Core, VecDictTimeCons){
    algobox::vector<int> v(10);
    algobox::dict d;
    d["something"] = 10;
    algobox::core<int> c(v, d, 6.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_width, 720.0f);
    EXPECT_EQ(c.screen_height, 720.0f);
    EXPECT_EQ(c.time, 6.0f);
}

TEST(Core, VecDictHWCons){
    algobox::vector<int> v(10);
    algobox::dict d;
    d["something"] = 10;
    algobox::core<int> c(v, d, 200.0f, 300.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_height, 200.0f);
    EXPECT_EQ(c.screen_width, 300.0f);
    EXPECT_EQ(c.time, 1.0f);
}


TEST(Core, VecFullCons){
    algobox::vector<int> v(10);
    algobox::dict d;
    d["something"] = 10;
    algobox::core<int> c(v, d, 200.0f, 300.0f, 4.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_height, 200.0f);
    EXPECT_EQ(c.screen_width, 300.0f);
    EXPECT_EQ(c.time, 4.0f);
}


TEST(Core, StdVecFullCons){
    std::vector<int> v(10, 0);
    algobox::dict d;
    d["something"] = 10;
    algobox::core<int> c(v, d, 200.0f, 300.0f, 4.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_height, 200.0f);
    EXPECT_EQ(c.screen_width, 300.0f);
    EXPECT_EQ(c.time, 4.0f);
}


TEST(Core, InitializerFullCons){
    algobox::dict d;
    d["something"] = 10;
    algobox::core<int> c({
            3,4,5,6,7,8,9,10,11,12
        }, d, 200.0f, 300.0f, 4.0f);
    c.v.mode = SEARCH;

    c.v[5] = 6;

    EXPECT_EQ(c.v.size(), 10);
    EXPECT_EQ(c.v.at(5), 6);
    EXPECT_FALSE(c.v.nodes.empty());
    EXPECT_FALSE(c.vars.data.empty());
    EXPECT_EQ(c.vars["something"], 10);
    EXPECT_EQ(c.screen_height, 200.0f);
    EXPECT_EQ(c.screen_width, 300.0f);
    EXPECT_EQ(c.time, 4.0f);
}


TEST(Core, Vars){
    algobox::core<int>c ({1,2,3,4,5});
    c.v.mode = SORT;

    c.vars["min"] = 10;
    EXPECT_EQ(c.vars.data["min"].front(), 10);
    EXPECT_EQ(c.vars.data["min"].back(), 10);

    c.vars["min"] = 20;
    EXPECT_EQ(c.vars.data["min"].front(), 20);
    EXPECT_EQ(c.vars.data["min"].back(), 20);

    c.vars++;
    c.vars["min"] = 30;
    EXPECT_EQ(c.vars.data["min"].front(), 20);
    EXPECT_EQ(c.vars.data["min"].back(), 30);

    c++;
    c.vars["min"] = 40;
    EXPECT_EQ(c.vars.data["min"].front(), 20);
    EXPECT_EQ(c.vars.data["min"].back(), 40);
    EXPECT_EQ(c.vars["min"], 40);
    c.vars.data["min"].pop();
    EXPECT_EQ(c.vars.data["min"].front(), 30);

}

TEST(Core, Vector){
    algobox::core<int>c ({1,2,3,4,5});
    c.v.mode = SEARCH;
    EXPECT_EQ(c.v.nodes.front(), algobox::empty_element);

    c.v[2];
    EXPECT_EQ(c.v.nodes.front(), 2);
    EXPECT_EQ(c.v.nodes.back(), 2);

    c.v[2];
    EXPECT_EQ(c.v.nodes.front(), 2);
    EXPECT_EQ(c.v.nodes.back(), 2);

    c.v++;
    c.v[2];
    EXPECT_EQ(c.v.nodes.front(), 2);
    EXPECT_EQ(c.v.nodes.back(), 2);

    c++;
    c.v[4];
    EXPECT_EQ(c.v.nodes.front(), 2);
    EXPECT_EQ(c.v.nodes.back(), 4);
    c.v.nodes.pop();
    c.v.nodes.pop();
    EXPECT_EQ(c.v.nodes.front(), 4);

}