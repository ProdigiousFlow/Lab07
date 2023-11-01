// Lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(360, 30));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.setVelocity(Vector2f(1, 0));


	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle wall1;
	wall1.setSize(Vector2f(20, 800));
	wall1.setCenter(Vector2f(10, 400));
	wall1.setStatic(true);
	world.AddPhysicsBody(wall1);

	PhysicsRectangle wall2;
	wall2.setSize(Vector2f(20, 800));
	wall2.setCenter(Vector2f(790, 400));
	wall2.setStatic(true);
	world.AddPhysicsBody(wall2);

	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(80, 80));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	int thudCount(0);
	floor.onCollision = [](PhysicsBodyCollisionResult result) {
		cout << "thud " << endl;
	};
	wall1.onCollision = [](PhysicsBodyCollisionResult result) {
		cout << "thud " << endl;
		};
	wall2.onCollision = [](PhysicsBodyCollisionResult result) {
		cout << "thud " << endl;
		};
	ceiling.onCollision = [](PhysicsBodyCollisionResult result) {
		cout << "thud " << endl;
		};
	int hitCount(0);
	obstacle.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "bang  " << hitCount + 1 << endl;
		hitCount++;
		if (hitCount >= 2) {
			exit(1);
		}
	};



	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(wall1);
		window.draw(wall2);
		window.draw(ceiling);
		window.draw(obstacle);
		window.display();
	}
}
