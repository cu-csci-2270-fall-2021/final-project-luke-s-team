// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
       
    int len = 5;
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    result = test_insert(commits, len, tabSize);
    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    int len1 = 1;
    string commits1[] = {""};
    int tabSize1 = 5;
    result = test_insert(commits1, len1, tabSize1);
    expected = "0|| (0,)\n1|| \n2|| \n3|| \n4|| \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    int len2 = 2;
    string commits2[] = {"fun","fun"};
    int tabSize2 = 5;
    result = test_insert(commits2, len2, tabSize2);
    expected = "0|| \n1|| \n2|| \n3|| \n4|| fun(0,1,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    int len3 = 8;
    string commits3[] = {"fun","fun","yay","wonderful","hard","difficult","computer","software"};
    int tabSize3 = 5;
    result = test_insert(commits3, len3, tabSize3);
    expected = "0|| software(7,)-->hard(4,)\n1|| \n2|| wonderful(3,)\n3|| \n4|| computer(6,)-->difficult(5,)-->yay(2,)-->fun(0,1,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);

    
}

//TODO add more tests for insert. Design tests for search from hashTable.

TEST_F(test_x,TestSearch)
{
    string result;
    string expected;
    
    string str = "computer";
    int len = 5;
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    result = test_search(str,commits, len, tabSize);
    expected = "computer(0,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string str1 = "science";
    int len1 = 5;
    string commits1[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize1 = 5;
    result = test_search(str1,commits1, len1, tabSize1);
    expected = "science(1,4,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string str3 = "yay";
    int len3 = 5;
    string commits3[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize3 = 5;
    result = test_search(str3,commits3, len3, tabSize3);
    expected = "Key cannot be found.\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string str4 = "computer";
    int len4 = 5;
    string commits4[] = {"", "", "", "", ""};
    int tabSize4 = 5;
    result = test_search(str4,commits4, len4, tabSize4);
    expected = "Key cannot be found.\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string str5 = "";
    int len5 = 5;
    string commits5[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize5 = 5;
    result = test_search(str5,commits5, len5, tabSize5);
    expected = "Key cannot be found.\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

TEST_F(test_x,TestHash)
{
    string result;
    string expected;
    
    string str = "";
    int tabSize = 0;
    
    str = "";
    tabSize = 5;
    result = test_hash(str,tabSize);
    expected = "Hashed: \nResult: 0\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    str = "science";
    tabSize = 5;
    result = test_hash(str,tabSize);
    expected = "Hashed: science\nResult: 0\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    str = "fun";
    tabSize = 5;
    result = test_hash(str,tabSize);
    expected = "Hashed: fun\nResult: 4\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    str = "fun";
    tabSize = 37;
    result = test_hash(str,tabSize);
    expected = "Hashed: fun\nResult: 33\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    str = "1";
    tabSize = 5;
    result = test_hash(str,tabSize);
    expected = "Hashed: 1\nResult: 4\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    str = "13a j%7X";
    tabSize = 29;
    result = test_hash(str,tabSize);
    expected = "Hashed: 13a j%7X\nResult: 22\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}
