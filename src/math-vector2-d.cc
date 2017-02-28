/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * math-vector2-d.cc
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

#include "math-vector2-d.h"

MathVector2D::MathVector2D()
{
	vec[0] = 0.0;
	vec[1] = 0.0;
}

MathVector2D::MathVector2D(double x, double y)
{
	vec[0] = x;
	vec[1] = y;
}

void MathVector2D::print()
{
	std::cout << "(" << vec[0] << ", " << vec[1] << ")" << std::endl;
}

double MathVector2D::norm() const
{
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
}

const MathVector2D MathVector2D::operator-() const
{
	MathVector2D result(-vec[0], -vec[1]);

	return result;
}

MathVector2D &MathVector2D::operator+=(const MathVector2D &MVec2)
{
	vec[0] += MVec2[0];
	vec[1] += MVec2[1];

	return *this;
}

MathVector2D &MathVector2D::operator-=(const MathVector2D &MVec2)
{
	vec[0] -= MVec2[0];
	vec[1] -= MVec2[1];

	return *this;
}

MathVector2D &MathVector2D::operator*=(const double &scalar)
{
	vec[0] *= scalar;
	vec[1] *= scalar;

	return *this;
}

MathVector2D &MathVector2D::operator/=(const double &scalar)
{
	if(fabs(scalar) >= 1E-6)
	{
		vec[0] /= scalar;
		vec[1] /= scalar;
	}
	else
	{
		vec[0] = INFINITY;
		vec[1] = INFINITY;
	}

	return *this;
}

double& MathVector2D::operator[] (const int index)
{
	return vec[index];
}

const double& MathVector2D::operator[] (const int index) const
{
	return vec[index];
}

const bool MathVector2D::operator==(const MathVector2D &MVec2) const
{
	if(fabs(vec[0] - MVec2[0]) > 1E-6 || fabs(vec[1] - MVec2[1]) > 1E-6)
	{
		return false;
	}

	return true;
}

const bool MathVector2D::operator!=(const MathVector2D &MVec2) const
{
	return !(*this == MVec2);
}

const
MathVector2D operator+(const MathVector2D &MVec1, const MathVector2D &MVec2)
{
	MathVector2D result = MVec1;
	result += MVec2;
	return result;
}

const
MathVector2D operator-(const MathVector2D &MVec1, const MathVector2D &MVec2)
{
	MathVector2D result = MVec1;
	result -= MVec2;
	return result;
}

const MathVector2D operator*(const MathVector2D &MVec, const double &scalar)
{
	MathVector2D result = MVec;
	result *= scalar;
	return result;
}

const MathVector2D operator*(const double &scalar, const MathVector2D &MVec)
{
	MathVector2D result = MVec;
	result *= scalar;
	return result;
}

const MathVector2D operator/(const MathVector2D &MVec, const double &scalar)
{
	MathVector2D result = MVec;
	result /= scalar;
	return result;
}

const MathVector2D operator/(const double &scalar, const MathVector2D &MVec)
{
	MathVector2D result;
	result[0] = fabs(MVec[0]) >= 1E-6 ? 1.0/MVec[0] : INFINITY;
	result[1] = fabs(MVec[1]) >= 1E-6 ? 1.0/MVec[1] : INFINITY;

	result *= scalar;
	return result;
}

const double operator*(const MathVector2D &MVec1, const MathVector2D &MVec2)
{
	return MVec1[0] * MVec2[0] + MVec1[1] * MVec2[1];
}



