// HashMapTests.cpp
//
// ICS 45C Fall 2018
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"

//#include <iostream>


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
   HashMap empty;
   ASSERT_EQ(0, empty.size());
}


TEST(TestHashMap, canAddToHashMap)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   ASSERT_EQ(1, hm.size());
}

TEST(TestHashMap, containsKey)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   ASSERT_TRUE(hm.contains("Arya"));
}

TEST(TestHashMap, doesntContainKey)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   ASSERT_FALSE(hm.contains("Kanye"));
}


TEST(TestHashMap, canAddToHashMapTwo)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   hm.add("Kanye", "West");
   ASSERT_EQ(2, hm.size());
}


TEST(TestHashMap, canFindValue)
{
   HashMap hm;
   hm.add("Kanye", "West");
   ASSERT_EQ("West", hm.value("Kanye"));
}


TEST(TestHashMap, checkInitialBucketCount)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   ASSERT_EQ(10, hm.bucketCount());
}


TEST(TestHashMap, checkLoadFactor)
{
   HashMap hm;
   hm.add("Arya", "Kash");
   ASSERT_EQ(0.1, hm.loadFactor());
}


TEST(TestHashMap, doesBucketCountChange)
{
   HashMap hm;
   hm.add("a", "a");
   hm.add("b", "b");
   hm.add("c", "c");
   hm.add("d", "d");
   hm.add("e", "e");
   hm.add("a1", "a1");
   hm.add("b2", "b2");
   hm.add("c3", "c3");
   hm.add("d4", "d4");
   hm.add("e5", "e5");
   ASSERT_EQ(21, hm.bucketCount());
}


// TEST(TestHashMap, maxBucketSizeTest)
// {
//    HashMap hm;
//    hm.add("a", "a");
//    hm.add("b", "b");
//    hm.add("c", "c");
//    hm.add("d", "d");
//    hm.add("e", "e");
//    hm.add("a1", "a1");
//    hm.add("b2", "b2");
//    hm.add("c3", "c3");
//    hm.add("d4", "d4");
//    hm.add("e5", "e5");
//    ASSERT_EQ(9, hm.maxBucketSize());
// }


TEST(TestHashMap, removeVersionOne)
{
	HashMap hm;
 	hm.add("a", "a");
    hm.add("b", "b");
    hm.add("c", "c");
    hm.add("d", "d");
    hm.add("e", "e");
    hm.add("a1", "a1");
    hm.add("b2", "b2");
    hm.add("c3", "c3");
    hm.add("d4", "d4");
    hm.add("e5", "e5");
    hm.remove("d");
    ASSERT_EQ(false, hm.contains("d"));
}


TEST(TestHashMap, removeVersionTwo)
{
	HashMap hm;
 	hm.add("a", "a");
    hm.add("b", "b");
    hm.add("c", "c");
    hm.add("d", "d");
    hm.add("e", "e");
    hm.add("a1", "a1");
    hm.add("b2", "b2");
    hm.add("c3", "c3");
    hm.add("d4", "d4");
    hm.add("e5", "e5");
    hm.add("aa", "a");
    hm.add("bb", "b");
    hm.add("cc", "c");
    hm.add("dd", "d");
    hm.add("ee", "e");
    hm.remove("bb");
    ASSERT_EQ(false, hm.contains("bb"));
}

TEST(TestHashMap, removeVersionThree)
{
	HashMap hm;
 	hm.add("a", "a");
    hm.add("b", "b");
    hm.add("c", "c");
    hm.add("d", "d");
    hm.add("e", "e");
    hm.add("a1", "a1");
    hm.add("b2", "b2");
    hm.add("c3", "c3");
    hm.add("d4", "d4");
    hm.add("e5", "e5");
    hm.add("aa", "a");
    hm.add("bb", "b");
    hm.add("cc", "c");
    hm.add("dd", "d");
    hm.add("ee", "e");
    hm.remove("e5");
    ASSERT_EQ(false, hm.contains("e5"));
}





























