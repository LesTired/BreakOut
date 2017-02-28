/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * collision-model-data.cc
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

#include "collision-model-data.h"

CollisionModelData::CollisionModelData()
:time_of_collision(INFINITY)
{
}

double CollisionModelData::get_time_of_collision()
{
	return time_of_collision;
}

double CollisionModelData::get_reflection_velocity_x()
{
	return velocity_s[0];
}

double CollisionModelData::get_reflection_velocity_y()
{
	return velocity_s[1];
}

// Collision-model for Ball hits Line
// ----------------------------------
void CollisionModelData::operator()
(const BallData &Ball, const MathVector2D &A, const MathVector2D &B)
{
	// --- Calculate where the ball hits the line ---
	//
	// Let L be the distance vector between the points A and B
	// L = A - B
	//
	// The parallel-component v_p of the balls velocity-vector v is calculated
	// by projecting v on L:
	// v_p = (<v,L>/<L,L>) * L
	//
	// Therefore the normal-component v_n can be written as,
	// v_n = v - v_p
	//
	// The Point Q of the Balls surface that hits the Line is given by:
	// Q = r*(v_n/|v_n|) + X
	// where	X ... position of Balls center at t=0
	//			r ... radius of ball
	//
	// Setting up a simple equation for the line:
	// A + lambda*(B-A) == P
	// If lambda is a real number between 0 and 1 the arbitrary point P is
	// located at the line.
	//
	// Solve equation: Q + v*t == A + lambda*(B-A) for lambda and t!
	//
	// Def.: v_o (in code v_ortho) is orthogonal to v:
	// v_o = (v_y, -v_x)
	//
	// Solution: lambda = <(Q - A),v_o>/<(B - A),v_o>
	//			 t = (A_x + lambda*(B_x - A_x) - Q_x)/v_x or
	//			 t = (A_y + lambda*(B_y - A_y) - Q_y)/v_y
	// <.,.> is the standard scalar-product! |.| is the norm!

	MathVector2D L = A - B;

	// if distance is zero redirect to point-collision model.
	if(fabs(L[0]) < 1.0E-6 && fabs(L[1]) < 1.0E-6)
	{
		(*this)(Ball, A);
		return;
	}

	MathVector2D v_n = Ball.velocity - (((Ball.velocity * L)/(L * L)) * L);
	MathVector2D v_ortho(Ball.velocity[1], -Ball.velocity[0]);
	MathVector2D Q = (v_n/v_n.norm()) * Ball.radius + Ball.position;

	double lambda = ((Q-A)*v_ortho)/((B-A)*v_ortho);

	if(lambda > 1.0E-6 && lambda < 1.0)
	{
		// To prevent possible division by 0!
		double collision_time_temp =
		(fabs(Ball.velocity[0]) > fabs(Ball.velocity[1]))?
		(A[0] + lambda*(B[0]-A[0]) - Q[0]) / Ball.velocity[0]:
		(A[1] + lambda*(B[1]-A[1]) - Q[1]) / Ball.velocity[1];

		// Bind result to this timestep.
		if(collision_time_temp > 1.0 || collision_time_temp < 0.0)
		{
			collision_time_temp = INFINITY;
		}

		// Check wether this is smallest collision-time calculated so far
		// within this timestep.
		if(collision_time_temp < time_of_collision)
		{
			// --- Calculate velocity vector of reflected Ball ---
			//
			// The reflection of velocity ... v' (in code: velocity_s)
			// is calculated by v' = -v_n + v_t
			//
			// Therefore: v' = v - (2 * v_n)

			time_of_collision = collision_time_temp;
			velocity_s = Ball.velocity - (2.0 * v_n);
		}
	}
}

// Collision-model for Ball hits Circle
// ------------------------------------
void CollisionModelData::operator()
(const BallData &Ball, const MathVector2D &C, double r)
{
	// --- Calculate time of collision ---
	//
	// Solve equation: |X + v*t - C| == r + R for t!
	// where	X ... position of Balls center at t=0
	//			v ... velocity of Ball
	//			C ... center point of fixed Circle
	//			r ... radius of Ball
	//			R ... radius of fixed Circle
	//
	// Use abbreviations: d = r + R, D = X - C
	//
	// Solution: t = - <v,D>/<v,v> (+/-) sqrt((<v,D>/<v,v>)^2 + d^2 - <D,D>)
	// <.,.> is the standard scalar-product! |.| is the norm!

	double d = Ball.radius + r;
	MathVector2D D = Ball.position - C;

	// further abbreviations!
	double q = (Ball.velocity * D) / (Ball.velocity * Ball.velocity);
	double Q = q*q + (d*d - D*D)/(Ball.velocity * Ball.velocity);

	// Test if there is a real solution of the equation.
	if(Q > 1E-6)
	{
		// Quadratic equation always has two solutions ... find the smallest!
		// Collision has to occur within timestep, otherwise it gets discarded.
		double t1 = -q + sqrt(Q);
		double t2 = -q - sqrt(Q);

		if(t1 > 1.0 || t1 < 1E-6) t1 = INFINITY;
		if(t2 > 1.0 || t2 < 1E-6) t2 = INFINITY;
		double collision_time_temp = (t1 < t2 ? t1 : t2);

		// Check wether this is smallest collision-time calculated so far
		// within this timestep.
		if(collision_time_temp < time_of_collision)
		{
			// --- Calculate velocity vector of reflected Ball ---
			//
			// Normal-vector of collision ... D' (in code: D_s, read "D stroke")
			// D' = X + v*t - C ... X, v, C as above
			// Project v on D' to get Normal-vector of velocity v_n.
			// v_n = (<v,D'>/<D',D'>) * D'
			//
			// Tangential-vector of velocity ... v_t can be calculated from
			// v = v_n + v_t
			// => v_t = v - v_n
			//
			// The reflection of velocity ... v' (in code: velocity_s)
			// is calculated by v' = -v_n + v_t
			//
			// Therefore: v' = v - (2 * v_n)

			MathVector2D D_s = (Ball.position +
								Ball.velocity * collision_time_temp) - C;
			MathVector2D v_n = ((Ball.velocity * D_s) / (D_s * D_s)) * D_s;

			// Set the results.
			time_of_collision = collision_time_temp;
			velocity_s = Ball.velocity - (2.0 * v_n);
		}
	}
}

// Collision-model for Ball hits Point
// -----------------------------------
void CollisionModelData::operator()
(const BallData &Ball, const MathVector2D &P)
{
	// A Point will be handled like a Circle with radius 0.
	(*this)(Ball, P, 0.0);
}

// Collision-model for Ball hits Brick
// -----------------------------------
void CollisionModelData::operator()
(const BallData &Ball, const BrickData &Brick)
{
	// Brick consist of 4 Corner-Points A, B, C, D and 4 Lines AB, BC, CD, DA.
	MathVector2D A(Brick.position[0],
				   Brick.position[1]);
	MathVector2D B(Brick.position[0] + Brick.size[0],
				   Brick.position[1]);
	MathVector2D C(Brick.position[0] + Brick.size[0],
				   Brick.position[1] + Brick.size[1]);
	MathVector2D D(Brick.position[0],
				   Brick.position[1] + Brick.size[1]);

	// Make use of the more primitve Collision-models.
	(*this)(Ball, A, B);
	(*this)(Ball, B, C);
	(*this)(Ball, C, D);
	(*this)(Ball, D, A);

	(*this)(Ball, A);
	(*this)(Ball, B);
	(*this)(Ball, C);
	(*this)(Ball, D);
}

// Collision-model for Ball hits Paddle
// ------------------------------------
void CollisionModelData::operator()
(const BallData &Ball, const PaddleData &Paddle)
{
	// Paddle consists of Brick-like body and Caps (as Circles) on both ends.
	BrickData BrickPad	 (Paddle.position[0] - Paddle.size[0]/2.0,
					   	  Paddle.position[1],
					   	  Paddle.size[0],
					   	  Paddle.size[1]);
	MathVector2D CapLeft (Paddle.position[0] - Paddle.size[0]/2.0,
						  Paddle.position[1] + Paddle.size[1]/2.0);
	MathVector2D CapRight(Paddle.position[0] + Paddle.size[0]/2.0,
						  Paddle.position[1] + Paddle.size[1]/2.0);

	// Use relative velocity between Ball and Paddle.
	double temp_coll_time = time_of_collision;
	BallData rel_Ball = Ball;
	rel_Ball.velocity[0] -= Paddle.velocity;

	// Make use of the more primitve Collision-models.
	(*this)(rel_Ball, BrickPad);
	(*this)(rel_Ball, CapLeft,  Paddle.size[1]/2.0);
	(*this)(rel_Ball, CapRight, Paddle.size[1]/2.0);
	
	if(time_of_collision < temp_coll_time)
	{
		velocity_s[0] += Paddle.velocity;
	}
}

CollisionModelData::~CollisionModelData()
{
}

