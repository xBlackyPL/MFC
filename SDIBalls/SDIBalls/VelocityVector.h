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

		explicit VelocityVector(const VelocityVector& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
		}

		explicit VelocityVector(const VelocityVector&& original) noexcept
		{
			x_axis_velocity_ = original.getXAxisVelocity();
			y_axis_velocity_ = original.getYAxisVelocity();
		}

		VelocityVector(const unsigned char x_axis_velocity, const unsigned char y_axis_velocity) :
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

		unsigned char getXAxisVelocity() const { return x_axis_velocity_; }
		unsigned char getYAxisVelocity() const { return y_axis_velocity_; }
		void increaseXAxisVelocity(const unsigned char acceleration) { x_axis_velocity_ += acceleration; }
		void increaseYAxisVelocity(const unsigned char acceleration) { y_axis_velocity_ += acceleration; }
		void setXAxisVelocity(const unsigned char x_axis_velocity) { x_axis_velocity_ = x_axis_velocity; }
		void setYAxisVelocity(const unsigned char y_axis_velocity) { y_axis_velocity_ = y_axis_velocity; }

	private:
		unsigned char x_axis_velocity_;
		unsigned char y_axis_velocity_;
	};
}
