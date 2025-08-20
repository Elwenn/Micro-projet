#include <gtest/gtest.h>

#include "MyApp.h"
#include "corn/Enemy.h"
#include "corn/Friend.h"
#include "corn/PopCorn.h"
#include "Game.h"

class TestCorn : public ::testing::Test {
protected:
  Game testgame;

  void SetUp() override {
    // Code � ex�cuter avant chaque test
  }

  void TearDown() override {
    // Code � ex�cuter apr�s chaque test
  }
};

// Friend Group Test
TEST_F(TestCorn, TestHitCorn) {

  auto ptr = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
  Enemy myEnemy(0, 0, std::move(ptr));
  
  printf("PV: %d\n", myEnemy.getPV());
  myEnemy.getHit(testgame);
  printf("PV: %d\n", myEnemy.getPV());

  EXPECT_EQ(myEnemy.isAlive(), true);
  EXPECT_EQ(myEnemy.getPV(), 3);
  
}


TEST_F(TestCorn, TestKillCorn) {
  auto ptr = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
  Friend myFriend(0, 0, std::move(ptr));

  myFriend.getHit(testgame);
  myFriend.getHit(testgame);

  EXPECT_EQ(myFriend.isAlive(), false);

}

TEST_F(TestCorn, TestKillPopCorn) {
  auto ptr = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
  Friend myPopCorn(0, 0, std::move(ptr));

  myPopCorn.getHit(testgame);
  myPopCorn.getHit(testgame);

  EXPECT_EQ(myPopCorn.isAlive(), false);

}
