//============================================================================
// Name        : Project.cpp
// Author      : Jacques Visser
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CollisionManager.h"
using namespace std;

#include <gtest/gtest.h>


//------------------------------------------------------------------------------
//						Coordinate
//------------------------------------------------------------------------------
TEST(Coordinate, Construction)
{
	Coordinate testCoord(3,4);
}

TEST(Coordinate, IncrementOperator)
{
	//tests setters implicitly
	Coordinate testCoord{3, 4};
	testCoord += Coordinate{2, 1};

	EXPECT_EQ(5, testCoord.x());
	EXPECT_EQ(5, testCoord.y());
}

TEST(Coordinate, DecrementOperator)
{
	Coordinate testCoord{3, 4};
	testCoord -= Coordinate{3, 4};

	EXPECT_EQ(0, testCoord.x());
	EXPECT_EQ(0, testCoord.y());
}

TEST(Coordinate, EqualityOperator)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(1,1);
	EXPECT_TRUE(testCoord0 == testCoord1);
}

TEST(Coordinate, GreaterThanOperator)
{
	Coordinate testCoord0(2,1);
	Coordinate testCoord1(1,1);
	EXPECT_TRUE(testCoord0 > testCoord1);

	testCoord0 = Coordinate{2,1};
	testCoord1 = Coordinate{1,3};
	EXPECT_FALSE(testCoord0 > testCoord1);
}

TEST(Coordinate, SmallerThanOperator)
{
	Coordinate testCoord0(2,1);
	Coordinate testCoord1(1,1);
	EXPECT_FALSE(testCoord0 < testCoord1);

	testCoord0 = Coordinate{2,1};
	testCoord1 = Coordinate{1,3};
	EXPECT_TRUE(testCoord0 < testCoord1);
}

TEST(Coordinate, GreaterThanFloatOperator)
{
	Coordinate testCoord0(2,1);
	float testFloat{1};
	EXPECT_TRUE(testCoord0 > testFloat);

	testFloat = 5;
	EXPECT_FALSE(testCoord0 > testFloat);
}

TEST(Coordinate, SmallerThanFloatOperator)
{
	Coordinate testCoord0(2,1);
	float testFloat{5};
	EXPECT_TRUE(testCoord0 < testFloat);

	testFloat = 1;
	EXPECT_FALSE(testCoord0 < testFloat);
}

TEST(Coordinate, Addition)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(2,2);
	Coordinate testCoord2(3,3);
	EXPECT_EQ(testCoord2, (testCoord0 + testCoord1));
}

TEST(Coordinate, Subraction)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(2,2);
	Coordinate testCoord2(-1,-1);
	EXPECT_EQ(testCoord2, (testCoord0 - testCoord1));
}

TEST(Coordinate, DotProduct)
{
	Coordinate testCoord0(4,4);
	Coordinate testCoord1(2,2);
	float dot = 16.0f;
	EXPECT_EQ(dot, (testCoord0 * testCoord1));
}

TEST(Coordinate, Angle)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(angle, testCoord.angle());
}

TEST(Coordinate, MagnitudeSquared)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(magnitude*magnitude, testCoord.magSquared());
}

TEST(Coordinate, Magnitude)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(magnitude, testCoord.magnitude());
}

TEST(Coordinate, Rotate)
{
	Coordinate center{1,1};
	Coordinate coord{0,1};

	coord.rotate(PI/2, center);

	Coordinate comparCoord{1,2};
	EXPECT_EQ(comparCoord, coord);
}


//------------------------------------------------------------------------------
//					Line
//------------------------------------------------------------------------------
TEST(Line, Construction)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};
}

TEST(Line, Length)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};
	EXPECT_TRUE(lin.isBetween(sqrt(2), lin.length()-0.01, lin.length()+0.01));
}

TEST(Line, isBelowLineTrue)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};

	std::shared_ptr<Coordinate> tC2{new Coordinate{0.5,0.25}};
	EXPECT_TRUE(lin.isBelow(tC2));
}

TEST(Line, isBelowLineFalse)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};

	std::shared_ptr<Coordinate> tC2{new Coordinate{0.5,1}};
	EXPECT_FALSE(lin.isBelow(tC2));
}

//TEST(Line, intersects)
//{
//	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
//	shared_ptr<Coordinate> c1{new Coordinate{5,0}};
//	Line lin0{c0,c1};
//
//	shared_ptr<Coordinate> c2{new Coordinate{2,-1}};
//	shared_ptr<Coordinate> c3{new Coordinate{2,1}};
//	Line lin1{c2,c3};
//
//	EXPECT_TRUE(lin1.intersects(lin0));
//	EXPECT_TRUE(lin0.intersects(lin1));
//}

TEST(Line, intersects_Horisontal_Line)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
	shared_ptr<Coordinate> c1{new Coordinate{2,-1}};
	Line lin0{c0,c1};

	shared_ptr<Coordinate> c2{new Coordinate{0.55,0.1}};
	shared_ptr<Coordinate> c3{new Coordinate{1,-10}};
	Line lin1{c2,c3};

	EXPECT_TRUE(lin1.intersects(lin0));
	EXPECT_TRUE(lin0.intersects(lin1));
}

TEST(Line, Equality)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
	shared_ptr<Coordinate> c1{new Coordinate{5,0}};
	Line lin0{c0,c1};

	shared_ptr<Coordinate> c2{new Coordinate{0,0}};
	shared_ptr<Coordinate> c3{new Coordinate{5,0}};
	Line lin1{c2,c3};

	Line lin2{c3,c2};

	EXPECT_EQ(lin1, lin0);
	EXPECT_EQ(lin2, lin0);
	EXPECT_EQ(lin2, lin1);
}

TEST(Line, Normal)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
	shared_ptr<Coordinate> c1{new Coordinate{5,0}};
	Line lin0{c0,c1};

	Coordinate norm = lin0.getNormal();
}

//------------------------------------------------------------------------------
//				Triangle
//------------------------------------------------------------------------------
TEST(Triangle, Creation)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	Triangle testTri{tC0, tC1, tC2};
}

TEST(Triangle, isInside)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	std::shared_ptr<Coordinate> tC3{new Coordinate{0.5,0.5}};
	std::shared_ptr<Coordinate> tC4{new Coordinate{2,2}};

	Triangle testTri{tC0, tC1, tC2};

	EXPECT_TRUE(testTri.hasInside(tC3));
	EXPECT_FALSE(testTri.hasInside(tC4));
}

TEST(Triangle, coordsInsideTriangle_VecOfCoords)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	std::shared_ptr<Coordinate> tC3{new Coordinate{2,0}};
	std::shared_ptr<Coordinate> tC4{new Coordinate{0.2,0.2}};
	std::shared_ptr<Coordinate> tC5{new Coordinate{0.5,0.5}};

	vector<shared_ptr<Coordinate>> _coords;
	_coords.push_back(tC3);
	_coords.push_back(tC4);
	_coords.push_back(tC5);

	Triangle testTri{tC0, tC1, tC2};

	//EXPECT_EQ(2, testTri.hasInside(_coords)); // TODO
}

TEST(Triangle, coordsInsideTriangle_VecOfTriangles)
{
	std::shared_ptr<Coordinate> t0C0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{5,5}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{0,5}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	std::shared_ptr<Coordinate> t1C0{new Coordinate{0.5, 0.5}};
	std::shared_ptr<Coordinate> t1C1{new Coordinate{1, 1}};
	std::shared_ptr<Coordinate> t1C2{new Coordinate{0.5, 1}};
	std::shared_ptr<Triangle> t1{new Triangle{t1C0, t1C1, t1C2}};

	std::shared_ptr<Coordinate> t2C0{new Coordinate{0.3, 0.3}};
	std::shared_ptr<Coordinate> t2C1{new Coordinate{5,6}};
	std::shared_ptr<Coordinate> t2C2{new Coordinate{2,0}};
	std::shared_ptr<Triangle> t2{new Triangle{t2C0, t2C1, t2C2}};

	std::vector<std::shared_ptr<Triangle>> tris;
	tris.push_back(t1);
	tris.push_back(t2);

	//EXPECT_EQ(4, t0->hasInside(tris)); //TODO
}

TEST(Triangle, Move)
{
	Coordinate c0{0,0};
	Coordinate c1{5,5};
	Coordinate c2{0,5};
	std::shared_ptr<Coordinate> t0C0{new Coordinate{c0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{c1}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{c2}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	Coordinate dPos{1,1};

	t0->move(dPos);

	EXPECT_EQ(dPos+c0, *(t0->getCoordinate(0)));
	EXPECT_EQ(dPos+c1, *(t0->getCoordinate(1)));
	EXPECT_EQ(dPos+c2, *(t0->getCoordinate(2)));
}

TEST(Triangle, Rotate)
{
	Coordinate center{3,3};
	float angle{3};

	Coordinate c0{0,0};
	Coordinate c1{5,5};
	Coordinate c2{0,5};
	std::shared_ptr<Coordinate> t0C0{new Coordinate{c0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{c1}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{c2}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	t0->rotate(angle, center);
	c0.rotate(angle, center);
	c1.rotate(angle, center);
	c2.rotate(angle, center);

	EXPECT_EQ(c0, *(t0->getCoordinate(0)));
	EXPECT_EQ(c1, *(t0->getCoordinate(1)));
	EXPECT_EQ(c2, *(t0->getCoordinate(2)));
}

//------------------------------------------------------------------------------
//					GameObject
//------------------------------------------------------------------------------
TEST(GameObject, Construction)
{
	GameObject testGO{1};
}

TEST(GameObject, addTriangle)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{0,1}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};

	GameObject testGO{1};
	testGO.addTriangle(testTri);
}

TEST(GameObject, animateLinearForce)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{0,1}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	GameObject testGO{1};
	testGO.addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC5{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC6{new Coordinate{0,1}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	GameObject testGO1{1};
	testGO1.addTriangle(testTri1);

	Coordinate force{1,0};
	testGO.applyForceLinear(force);

	testGO.animate(1);

	EXPECT_FALSE(testGO.getCenter() == testGO1.getCenter());
}



TEST(GameObject, IntersectingLine)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,0.1}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	GameObject testGO{1};
	testGO.addTriangle(testTri);

	shared_ptr<Coordinate> tC3{new Coordinate{0.5,0.25}};
	shared_ptr<Coordinate> tC4{new Coordinate{0.5,-10}};
	Line testLine{tC3, tC4};

	Line lin0{tC0, tC2};
	auto lin1 = testGO.intersectingLine(testLine);

	EXPECT_EQ(lin0, lin1);
}

TEST(GameObject, avgCoordInside)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,0}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	GameObject testGO{1};
	testGO.addTriangle(testTri);

	shared_ptr<Coordinate> tC3{new Coordinate{0.5,0.27}};
	shared_ptr<Coordinate> tC4{new Coordinate{0.5,0.25}};
	shared_ptr<Coordinate> tC5{new Coordinate{1,-1}};
	shared_ptr<Triangle> testTri2{new Triangle{tC3, tC4, tC5}};
	GameObject testGO1{1};
	testGO1.addTriangle(testTri2);

	Coordinate avgCoord = testGO.avgCoordInside(testGO1);
	Coordinate coord{0.5,0.26};
	EXPECT_EQ(coord, avgCoord);
}

TEST(GameObject, intersectingLine)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,0}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	GameObject testGO{1};
	testGO.addTriangle(testTri);

	shared_ptr<Coordinate> tC3{new Coordinate{0.5, 0.4}};
	shared_ptr<Coordinate> tC4{new Coordinate{0.5, -0.4}};
	Line penetrating{tC3, tC4};

	Line intersected = testGO.intersectingLine(penetrating);
	Line intersectedReal{tC0, tC2};

	EXPECT_EQ(intersectedReal, intersected);
}

//------------------------------------------------------------------------------
//					Collision
//------------------------------------------------------------------------------
// A paradigm of collider and collidee is used with this class, A collidee is
// defined as an object that has one or more vertex of a collider inside of it.
// when both objects have coordinates of the other inside them the roles of
// collider and collidee is randomly selected. It is assumed that collisions
// will be detected before objects intersect to this level.

TEST(Collision, Construction_and_Find_Collision_Edge_Easy)
{
	//center of mass of collider is outside collidee
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0,-1}};
	shared_ptr<Coordinate> tC5{new Coordinate{2,-1}};
	shared_ptr<Coordinate> tC6{new Coordinate{1,1}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Coordinate velocity(0,1);
	testGO1->applyImpulseLinear(velocity);

	Collision col{testGO, testGO1};

	Line colEdgeReal{tC0, tC1};
	Line colEdgeFound = col._collisionEdge;

	EXPECT_EQ(colEdgeReal, colEdgeFound);
}

TEST(Collision, Construction_and_Find_Collision_Edge_Hard)
{
	//center of mass of collider is inside collidee
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0.5,0.1}};
	shared_ptr<Coordinate> tC5{new Coordinate{0.6,0.1}};
	shared_ptr<Coordinate> tC6{new Coordinate{0.45, -0.01}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Coordinate velocity(0,10);
	testGO1->applyImpulseLinear(velocity);
	EXPECT_EQ(velocity, testGO1->getVelocity());

	EXPECT_TRUE(testGO->hasInside(testGO1->getCenter()));

	shared_ptr<Coordinate> penetrator0{
			new Coordinate{testGO->avgCoordInside(*testGO1)}};
	shared_ptr<Coordinate> penetrator1{ new Coordinate{
		(*penetrator0) -
		(testGO1->getVelocity())*INF/2 +
		(testGO->getCenter()- (*penetrator0))
	}};

	Line penetratingLine{ penetrator0, penetrator1};
	auto collisionEdge = testGO->intersectingLine(penetratingLine);
	Line collisionEdgeActual{tC0, tC1};

	EXPECT_EQ(collisionEdgeActual, collisionEdge);

	Collision col{testGO, testGO1};
}

TEST(Collision, Construction_Easy_No_Movement)
{
	//center of mass of collider is outside collidee
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0,-1}};
	shared_ptr<Coordinate> tC5{new Coordinate{2,-1}};
	shared_ptr<Coordinate> tC6{new Coordinate{1,1}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Collision col{testGO, testGO1};

	Line colEdgeReal{tC0, tC1};
	Line colEdgeFound = col._collisionEdge;

	EXPECT_EQ(colEdgeReal, colEdgeFound);
}

TEST(Collision, Construction_Hard_No_Movement)
{
	//center of mass of collider is inside collidee
		shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
		shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
		shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
		shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
		shared_ptr<GameObject> testGO{new GameObject{1}};
		testGO->addTriangle(testTri);

		shared_ptr<Coordinate> tC4{new Coordinate{0.5,0.1}};
		shared_ptr<Coordinate> tC5{new Coordinate{0.6,0.1}};
		shared_ptr<Coordinate> tC6{new Coordinate{0.45, -0.01}};
		shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
		shared_ptr<GameObject> testGO1{new GameObject{1}};
		testGO1->addTriangle(testTri1);

		EXPECT_TRUE(testGO->hasInside(testGO1->getCenter()));

		shared_ptr<Coordinate> penetrator0{
				new Coordinate{testGO->avgCoordInside(*testGO1)}};
		shared_ptr<Coordinate> penetrator1{ new Coordinate{
			(*penetrator0) -
			(testGO1->getVelocity())*INF -
			(testGO->getCenter()- (*penetrator0))*INF
		}};

		Line penetratingLine{ penetrator0, penetrator1};
		auto collisionEdge = testGO->intersectingLine(penetratingLine);
		Line collisionEdgeActual{tC0, tC1};

		EXPECT_EQ(collisionEdgeActual, collisionEdge);

		Collision col{testGO, testGO1};
}

TEST(Collision, Resolution_No_Movement)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0.5,0.1}};
	shared_ptr<Coordinate> tC5{new Coordinate{0.6,0.1}};
	shared_ptr<Coordinate> tC6{new Coordinate{0.45, -0.01}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Collision col{testGO, testGO1};

	col.resolve(0.015);

	EXPECT_FALSE(testGO->hasInside(testGO1));
}

TEST(Collision, Resolution_With_Movement)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{1,2}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0.5,0.1}};
	shared_ptr<Coordinate> tC5{new Coordinate{0.6,0.1}};
	shared_ptr<Coordinate> tC6{new Coordinate{0.45, -0.01}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Coordinate velocity(0,10);
	testGO1->applyImpulseLinear(velocity);

	Collision col{testGO, testGO1};

	col.resolve(0.015);

	EXPECT_FALSE(testGO->hasInside(testGO1));
}

//------------------------------------------------------------------------------
//			CollisionManager
//------------------------------------------------------------------------------

TEST(CollisionManager, objectsCollided_NoCollisions)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{2,0}};
	shared_ptr<Coordinate> tC2{new Coordinate{0,1}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
	shared_ptr<GameObject> testGO{new GameObject{1}};
	testGO->addTriangle(testTri);

	shared_ptr<Coordinate> tC4{new Coordinate{0,-1}};
	shared_ptr<Coordinate> tC5{new Coordinate{2,-1}};
	shared_ptr<Coordinate> tC6{new Coordinate{1,1}};
	shared_ptr<Triangle> testTri1{new Triangle{tC4, tC5, tC6}};
	shared_ptr<GameObject> testGO1{new GameObject{1}};
	testGO1->addTriangle(testTri1);

	Coordinate force{0,1};
	testGO1->applyImpulseLinear(force);

	vector<shared_ptr<GameObject>> GOs;
	GOs.push_back(testGO);
	GOs.push_back(testGO1);

	CollisionManager CM{};
	CM.setGameObjecs(GOs);
	CM.findCollisions();

	EXPECT_EQ(0, CM.numCollisions());
}

