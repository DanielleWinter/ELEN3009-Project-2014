/*
 * Coordinate.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <cmath>
#include <iostream>
/*! \def PI
 *  This defines the value of pi as a float, to be used in calculating angles.
 */

/*! \def INF
 * This value defines a very large number - approximately infinity to the program.
 */

/*! \def NOTHING
 * This value approximates zero
 */
#define PI 3.1415926536
#define INF 200000
#define NOTHING 0.001

class Collision_Exception{};

/*! \class Coordinate
 *  \brief The Coordinate class is used to define a point with an x value and a y value and perform operations on the coordinate.
 *
 * The class has overloaded operator functions for performing mathematical operations and comparisons on coordinates.
 * A coordinate can be defined by a magnitude and angle as well as an x value and y value.
 */
class Coordinate
{
public:
	~Coordinate(){};
	/*!
	 *  default constructor
	 */
	Coordinate();
	/*! \brief Coordinate has floats for x and y coordinates
	 * 	\param newX gives x coordinate
	 * 	\param newY gives y coordinate
	 */
	Coordinate(float newX, float newY);

	/*! Coordinate takes in a constant coordinate position by reference.
	 *
	 */
	Coordinate(const Coordinate& pos);

	/*! \brief angle gives the angle in degrees
	 *
	 * \return Angle is a float value.
	 */
	float angle() const;
	/*! \brief magnitude returns the distance of the coordinate from the origin
	 *
	 */
	float magnitude() const;
	/*! \brief magSquared returns the squared distance from the origin
	 *
	 */
	float magSquared() const;

	float x() const;	//x position
	float y() const;	//y position
	void print() const;	//prints coordinate values to the console

	/*! \brief operator+ for addition of coordinates
	 * \param coord is an x,y coordinate
	 * \return returns sum of two coordinates
	 */
	Coordinate operator+(const Coordinate& coord) const;
	/*!  \brief operator- for coordinate subtraction
	 * 	\return returns difference of two coordinates
	 */
	Coordinate operator-(const Coordinate& coord) const;
	/*!  operator* for coordinate dot product
	 *   \return returns dot product
	 */
	float operator*(const Coordinate& coord) const; //dot product

	void operator+=(const Coordinate& coord);
	void operator-=(const Coordinate& coord);
	bool operator==(const Coordinate& coord) const;
	bool operator>(const Coordinate& coord) const;
	bool operator<(const Coordinate& coord) const;


	Coordinate operator*(const float& rhs) const;
	Coordinate operator/(const float& rhs) const;
	bool operator>(const float& rhs) const;
	bool operator<(const float& rhs) const;
	bool operator==(const float& rhs) const;

	void rotate(const float angle, const Coordinate& center);
	void rotate(const float angle);

	float _x;
	float _y;
	void setX(float x);
	void setY(float y);
};

#endif /* COORDINATE_H_ */
