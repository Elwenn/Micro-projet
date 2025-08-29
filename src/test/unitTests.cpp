#include <gtest/gtest.h>

#include "MyApp.h"
#include "corn/Enemy.h"
#include "corn/Friend.h"
#include "Game.h"

class TestCorn : public ::testing::Test {
protected:
  sf::RenderWindow window;
  Game testgame;

  TestCorn()
    : window(sf::VideoMode({800, 600}), "Test Window"),
      testgame(window)
  {
  }

  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Friend Group Test
TEST_F(TestCorn, TestHitCorn) {
  Friend myFriend(0, 0, 60);
  
  printf("PV: %d\n", myFriend.getPV());
  myFriend.getHit(testgame);
  printf("PV: %d\n", myFriend.getPV());

  EXPECT_EQ(myFriend.isAlive(), true);
  EXPECT_EQ(myFriend.getPV(), 1);
  
}


TEST_F(TestCorn, TestKillCorn) {
  Friend myFriend(0, 0, 60);

  myFriend.getHit(testgame);
  myFriend.getHit(testgame);

  EXPECT_EQ(myFriend.isAlive(), false);

}

