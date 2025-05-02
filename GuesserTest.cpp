/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(GuesserTest, secret_never_too_short)
{
  Guesser object(          "");
  ASSERT_TRUE(object.match(""));
}

TEST(GuesserTest, secret_never_too_long)
{
  Guesser object(          "123456789012345678901234567890123456789012345678901234567890");
  ASSERT_TRUE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, shortest_secret_with_guess_not_too_distant_no_lockout)
{
  Guesser object(          "");
  object.match(            "12");
  ASSERT_TRUE(object.match(""));
}

TEST(GuesserTest, shortest_secret_with_guess_slightly_too_distant_lockout)
{
  Guesser object(           "");
  object.match(             "123");
  ASSERT_FALSE(object.match(""));
}

TEST(GuesserTest, shortest_secret_with_guess_way_too_distant_lockout)
{
  Guesser object(           "");
  object.match(             "1234567890123456789012345678901234567890");
  ASSERT_FALSE(object.match(""));
}

TEST(GuesserTest, longest_secret_with_guess_slighty_too_distant_over_lockout)
{
  Guesser object(           "12345678901234567890123456789012");
  object.match(             "12345678901234567890123456789012345");
  ASSERT_FALSE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, longest_secret_with_guess_way_too_distant_over_lockout)
{
  Guesser object(           "12345678901234567890123456789012");
  object.match(             "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
  ASSERT_FALSE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, longest_secret_with_guess_slighty_too_distant_under_lockout)
{
  Guesser object(           "12345678901234567890123456789012");
  object.match(             "12345678901234567890123456789");
  ASSERT_FALSE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, longest_secret_with_guess_way_too_distant_under_lockout)
{
  Guesser object(           "12345678901234567890123456789012");
  object.match(             "");
  ASSERT_FALSE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, longest_secret_with_guess_not_too_distant_over_no_lockout)
{
  Guesser object(          "12345678901234567890123456789012");
  object.match(            "1234567890123456789012345678901234");
  ASSERT_TRUE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, longest_secret_with_guess_not_too_distant_under_no_lockout)
{
  Guesser object(          "12345678901234567890123456789012");
  object.match(            "123456789012345678901234567890");
  ASSERT_TRUE(object.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, happy_secret_guess_slighty_too_distant_over_lockout)
{
  Guesser object(           "1234567890");
  object.match(             "1234567890123");
  ASSERT_FALSE(object.match("1234567890"));
}

TEST(GuesserTest, happy_secret_guess_slighty_too_distant_under_lockout)
{
  Guesser object(           "1234567890");
  object.match(             "1234567");
  ASSERT_FALSE(object.match("1234567890"));
}

TEST(GuesserTest, happy_secret_guess_way_too_distant_over_lockout)
{
  Guesser object(           "1234567890");
  object.match(             "12345678901234567890123456789012345678901234567890");
  ASSERT_FALSE(object.match("1234567890"));
}

TEST(GuesserTest, happy_secret_guess_way_too_distant_under_lockout)
{
  Guesser object(           "12345678901234567890");
  object.match(             "");
  ASSERT_FALSE(object.match("12345678901234567890"));
}

TEST(GuesserTest, happy_secret_guess_not_too_distant_over_no_lockout)
{
  Guesser object(          "1234567890");
  object.match(            "123456789012");
  ASSERT_TRUE(object.match("1234567890"));
}

TEST(GuesserTest, happy_secret_guess_not_too_distant_under_no_lockout)
{
  Guesser object(          "1234567890");
  object.match(            "12345678");
  ASSERT_TRUE(object.match("1234567890"));
}

TEST(GuesserTest, correct_guess_1st_no_lockout)
{
  Guesser object(          "Password1");
  ASSERT_TRUE(object.match("Password1"));
}

TEST(GuesserTest, correct_guess_1st_3_guesses_remaining)
{
  Guesser object("Password1");
  object.match(  "Password1");
  ASSERT_EQ(3,object.remaining());
}

TEST(GuesserTest, correct_guess_2nd_no_lockout)
{
  Guesser object(          "Password1");
  object.match(            "Password");
  ASSERT_TRUE(object.match("Password1"));
}

TEST(GuesserTest, correct_guess_2nd_2_guesses_remaining)
{
  Guesser object("Password1");
  object.match(  "Password");
  object.match(  "Password1");
  ASSERT_EQ(2,object.remaining());
}

TEST(GuesserTest, correct_guess_3rd_no_lockout)
{
  Guesser object(          "Password1");
  object.match(            "Password");
  object.match(            "PAssword1");
  ASSERT_TRUE(object.match("Password1"));
}

TEST(GuesserTest, correct_guess_3rd_1_remaining)
{
  Guesser object("Password1");
  object.match(  "Password");
  object.match(  "PAssword1");
  object.match(  "Password1");
  ASSERT_EQ(1,object.remaining());
}


TEST(GuesserTest, three_wrong_guesses_lockout)
{
  Guesser object(           "Password1");
  object.match(             "Password2");
  object.match(             "Passwort1");
  object.match(             "Password12");
  ASSERT_FALSE(object.match("Password1"));
}

TEST(GuesserTest, three_wrong_guesses_0_remaining)
{
  Guesser object("Password1");
  object.match(  "Password2");
  object.match(  "Passwort1");
  object.match(  "Password12");
  ASSERT_EQ(0,object.remaining());
}