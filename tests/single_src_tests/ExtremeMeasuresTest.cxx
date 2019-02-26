/*
    This file is part of EJD.

    Copyright © 2019
              Michael Chiu <chiu@cs.toronto.edu>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "ExtremeMeasures.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
// std lib
#include <vector>
#include <numeric>

struct LatticePointTest : public ::testing::Test 
{
    std::vector<int> normal_vec {1,2,3,4,5,6};
    std::vector<int> shorter_vec {1,2,3,4};
};

// comparison operators
TEST_F(LatticePointTest, Comparison_Op_1) {
    ejd::LatticePoint p1(normal_vec);
    ejd::LatticePoint p2(shorter_vec);

    EXPECT_EQ(p1==p2, false);
    EXPECT_EQ(p1<p2, false);
}

// test apply_cumsum functionality
TEST_F(LatticePointTest, CUM_SUM) {
    auto d = normal_vec;
    std::vector<int> want {1,3,6,10,15,21};
    ejd::apply_cumsum(&d);
    EXPECT_EQ(d,want);
}

// test flatten helper function
TEST_F(LatticePointTest, FLATTEN) {
    // construct vec of vec
    std::vector<std::vector<int>> vec_of_vec;
    vec_of_vec.push_back(normal_vec);
    vec_of_vec.push_back(shorter_vec);

    // construct our result
    std::vector<int> vec_result;
    vec_result.insert(vec_result.begin(),shorter_vec.begin(), shorter_vec.end());
    vec_result.insert(vec_result.begin(),normal_vec.begin(), normal_vec.end());

    auto flattened_vec = ejd::flatten(vec_of_vec);

    EXPECT_THAT(flattened_vec,vec_result);
}

TEST_F(LatticePointTest, ADJACENT_DIFFS) {
    
    std::vector<int> result_differences {1,1,1,1,1,1};
    auto differences = normal_vec;
    std::adjacent_difference(differences.begin(), differences.end(), differences.begin());

    EXPECT_THAT(differences,result_differences);
}

int main(int argc, char **argv)
{
    /* code */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}