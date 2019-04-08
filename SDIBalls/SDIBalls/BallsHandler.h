#pragma once
#include <vector>
#include <random>
#include "Config.h"
#include "Ball.h"
#include <iostream>
#include <map>

namespace BallsCore
{
	using BallPool = std::vector<Ball>;

	class BallsHandler
	{
	private:
		BallPool ball_pool_;
		CRect* client_view_;
	public:
		BallsHandler() = default;

		explicit BallsHandler(CRect* client_rect)
		{
			client_view_ = client_rect;
		}

		const BallPool& viewBallPool() const
		{
			return ball_pool_;
		}

		void spawnRandomBall()
		{
			std::random_device random_device;
			std::mt19937 generator(random_device());

			const std::uniform_int_distribution<> radius_distribution(30, 120);

			const unsigned int radius = radius_distribution(generator);

			const std::uniform_int_distribution<> x_axis_velocity_distribution(
				BallsConfiguration::minimal_ball_x_axis_velocity,
				BallsConfiguration::maximal_ball_x_axis_velocity);
			const std::uniform_int_distribution<> y_axis_velocity_distribution(
				BallsConfiguration::minimal_ball_x_axis_velocity,
				BallsConfiguration::maximal_ball_x_axis_velocity);

			const std::uniform_int_distribution<> x_distribution(30 + radius, client_view_->Width() - 2 * radius);
			const std::uniform_int_distribution<> y_distribution(30 + radius, client_view_->Height() - 2 * radius);

			const std::uniform_int_distribution<> color_index_distribution(0, BallsConfiguration::Colors.size() - 1);
			const std::uniform_int_distribution<> pen_size_distribution(0, 4);

			VelocityVector velocity_vector;
			velocity_vector
				.setXAxisVelocity(x_axis_velocity_distribution(generator))
				.setYAxisVelocity(y_axis_velocity_distribution(generator));

			Position position;
			position
				.setX(x_distribution(generator))
				.setY(y_distribution(generator));

			ball_pool_.push_back(Ball(position, velocity_vector, radius, color_index_distribution(generator),
			                          pen_size_distribution(generator)));
		}

		void killLast()
		{
			if (!ball_pool_.empty())
			{
				ball_pool_.erase(ball_pool_.begin());
			}
		}

		unsigned int numberOfBalls() const
		{
			return static_cast<unsigned int>(ball_pool_.size());
		}

		void moveBalls()
		{
			for (auto& ball : ball_pool_)
			{
				ball.move();
				const auto position = ball.viewPosition();
				if (position.getX() >= client_view_->Width() - ball.getRadius() || position.getX() <= 0)
				{
					ball.reversXAxisVelocity();
				}

				if (position.getY() >= client_view_->Height() - 2 * ball.getRadius() || position.getY() <= 0)
				{
					ball.reversYAxisVelocity();
				}
			}
		}

		void drawBalls(CDC* device_context_memory) const
		{
			for (const auto& ball : viewBallPool())
			{
				const auto old_pen = device_context_memory->SelectObject(ball.viewPen());
				const auto old_brush = device_context_memory->SelectObject(ball.viewBrush());
				device_context_memory->Ellipse(ball.viewAppearance());
				device_context_memory->SelectObject(old_pen);
				device_context_memory->SelectObject(old_brush);
			}
		}
	};
}
