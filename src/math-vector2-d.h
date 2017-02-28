/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * math-vector2-d.h
 * Copyright (C) 2017 Michael Lehner <010.wintermute@gmail.com>
 *
 * BreakOut is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BreakOut is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MATH_VECTOR2_D_H_
#define _MATH_VECTOR2_D_H_

#include <vector>
#include <iostream>
#include <cmath>

// For working with two-dimensional Vectors in euklidean space.
// The scalar product is implemented as overloaded '*' operator between
// two MathVector2D elements.
//
// Note: A few bits of the code are redundand for the sake of efficiency!
class MathVector2D
{
public:
	MathVector2D();
	MathVector2D(double, double);

	void print();
	double norm() const;

	const MathVector2D operator-() const;
	MathVector2D &operator+=(const MathVector2D&);
	MathVector2D &operator-=(const MathVector2D&);
	MathVector2D &operator*=(const double&);
	MathVector2D &operator/=(const double&);

	double& operator[] (const int);
	const double& operator[] (const int) const;

	const bool operator==(const MathVector2D&) const;
	const bool operator!=(const MathVector2D&) const;

private:
	double vec[2];
};

const MathVector2D operator+(const MathVector2D&, const MathVector2D&);
const MathVector2D operator-(const MathVector2D&, const MathVector2D&);
const MathVector2D operator*(const MathVector2D&, const double&);
const MathVector2D operator*(const double&, const MathVector2D&);
const MathVector2D operator/(const MathVector2D&, const double&);
const MathVector2D operator/(const double&, const MathVector2D&);
const double operator*(const MathVector2D&, const MathVector2D&);

#endif // _MATH_VECTOR2_D_H_

