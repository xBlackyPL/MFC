#pragma once
#include <utility>
#include "Config.h"

namespace BallsCore
{
	class VelocityVector
	{
	public:
		VelocityVector() :
			x_axis_velocity_(BallsConfiguration::default_ball_x_axis_velocity),
			y_axis_velocity_(BallsConfiguration::default_ball_y_axis_velocity)
		{}

		VelocityVector(const VelocityVector& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
		}

		VelocityVector(const VelocityVector&& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
		}

		VelocityVector(const int x_axis_velocity, const int y_axis_velocity) :
			x_axis_velocity_(x_axis_velocity),
			y_axis_velocity_(y_axis_velocity)
		{}

		VelocityVector& operator=(const VelocityVector& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
			return *this;
		}
		VelocityVector& operator=(VelocityVector&& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
			return *this;
		}

		~VelocityVector() = default;

		int getXAxisVelocity() const { return x_axis_velocity_; }
		int getYAxisVelocity() const { return y_axis_velocity_; }

		VelocityVector& increaseXAxisVelocity(const int acceleration)
		{
			x_axis_velocity_ += acceleration;
			return *this;
		}
		VelocityVector& increaseYAxisVelocity(const int acceleration)
		{
			y_axis_velocity_ += acceleration;
			return *this;
		}
		VelocityVector& setXAxisVelocity(const int x_axis_velocity)
		{
			x_axis_velocity_ = x_axis_velocity;
			return *this;
		}

		VelocityVector& setYAxisVelocity(const int y_axis_velocity)
		{
			y_axis_velocity_ = y_axis_velocity;
			return *this;
		}

	private:
		int x_axis_velocity_;
		int y_axis_velocity_;
	};
}
