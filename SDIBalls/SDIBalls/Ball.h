#pragma once
#include <atltypes.h>
#include <iterator>
#include "VelocityVector.h"
#include "Position.h"
#include "GraphicalRepresentation.h"


namespace BallsCore
{
	class Ball
	{
	private:
		Position position_{};
		unsigned int radius_;
		VelocityVector velocity_vector_;
		std::unique_ptr<CRect> appearance_;
		std::unique_ptr<CPen> pen_;
		std::unique_ptr<CBrush> brush_;


	public:
		Ball(const Position position, const VelocityVector velocity_vector, const unsigned int radius,
		     const unsigned int color_index, unsigned int pen_size):
			position_(position), radius_(radius), velocity_vector_(velocity_vector)
		{
			appearance_ = std::make_unique<CRect>(position_.getX(), position_.getY(), position_.getX() + radius,
			                                      position_.getY() + radius);
			auto item = BallsConfiguration::Colors.begin();
			std::advance(item, color_index);
			auto color = item->second;

			if (item->first == "White")
			{
				pen_ = std::make_unique<CPen>(PS_SOLID, pen_size, BallsConfiguration::Colors.at("Black"));
			}
			else
			{
				pen_ = std::make_unique<CPen>(PS_SOLID, pen_size, color);
			}

			brush_ = std::make_unique<CBrush>(color);
		}

		const Position& viewPosition() const
		{
			return position_;
		}

		const VelocityVector& viewVelocityVector() const
		{
			return velocity_vector_;
		}

		void reversXAxisVelocity()
		{
			auto new_velocity = velocity_vector_.getXAxisVelocity();
			new_velocity *= -1;
			velocity_vector_.setXAxisVelocity(new_velocity);
		}

		void reversYAxisVelocity()
		{
			auto new_velocity = velocity_vector_.getYAxisVelocity();
			new_velocity *= -1;
			velocity_vector_.setYAxisVelocity(new_velocity);
		}

		void move()
		{
			position_.change(velocity_vector_);
			appearance_->OffsetRect(velocity_vector_.getXAxisVelocity(), velocity_vector_.getYAxisVelocity());
		}

		unsigned int getRadius() const
		{
			return radius_;
		}

		CRect* viewAppearance() const
		{
			return appearance_.get();
		}

		CPen* viewPen() const
		{
			return pen_.get();
		}

		CBrush* viewBrush() const
		{
			return brush_.get();
		}
	};
}
