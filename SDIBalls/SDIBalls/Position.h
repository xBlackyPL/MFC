#pragma once
#include "Config.h"
#include "VelocityVector.h"


namespace BallsCore
{
	class Position
	{
	public:
		Position() noexcept
		{
			x_ = BallsConfiguration::default_ball_x;
			y_ = BallsConfiguration::default_ball_y;
		}

		Position(const Position& original) noexcept
		{
			x_ = original.getX();
			y_ = original.getY();
		}

		Position(const Position&& original) noexcept
		{
			x_ = original.getX();
			y_ = original.getY();
		}

		Position(const unsigned int x_axis_velocity, const unsigned int y_axis_velocity) :
			x_(x_axis_velocity),
			y_(y_axis_velocity)
		{
		}

		Position& operator=(const Position& original) noexcept
		{
			x_ = original.getX();
			y_ = original.getY();
			return *this;
		}

		Position& operator=(Position&& original) noexcept
		{
			x_ = original.getX();
			y_ = original.getY();
			return *this;
		}

		~Position() = default;

		unsigned int getX() const { return x_; }
		unsigned int getY() const { return y_; }

		Position& setX(const unsigned int x)
		{
			x_ = x;
			return *this;
		}

		Position& setY(const unsigned int y)
		{
			y_ = y;
			return *this;
		}

		Position& changeX(const unsigned int x)
		{
			x_ += x;
			return *this;
		}

		Position& changeY(const unsigned int y)
		{
			y_ += y;
			return *this;
		}

		Position& change(const VelocityVector& velocity_vector)
		{
			x_ += velocity_vector.getXAxisVelocity();
			y_ += velocity_vector.getYAxisVelocity();
			return *this;
		}
		
	private:
		unsigned int x_;
		unsigned int y_;
	};
}
