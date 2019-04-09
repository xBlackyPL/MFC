#pragma once
#include <vector>
#include <random>
#include "Config.h"
#include "Ball.h"
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

			const std::uniform_int_distribution<> radius_distribution(15, 60);

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
			
			VelocityVector velocity_vector;
			velocity_vector
				.setXAxisVelocity(x_axis_velocity_distribution(generator))
				.setYAxisVelocity(y_axis_velocity_distribution(generator));

			Position position;
			position
				.setX(x_distribution(generator))
				.setY(y_distribution(generator));

			ball_pool_.push_back(Ball(position, velocity_vector, radius, color_index_distribution(generator)));
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

		void moveBalls(CRect* client_view)
		{
			client_view_ = client_view;
			for (auto& ball : ball_pool_)
			{
				const auto position = ball.viewPosition();
				
				if(ball.viewAppearance()->right >= client_view_->right)
				{
					ball.reverseXAxisVelocity();
					ball.viewAppearance()->MoveToX(client_view_->right - ball.viewAppearance()->Size().cx);
				}
				else if (ball.viewAppearance()->left <= client_view_->left)
				{
					ball.reverseXAxisVelocity();
					ball.viewAppearance()->MoveToX(0);
				}

				if (ball.viewAppearance()->bottom >= client_view_->bottom)
				{
					ball.reverseYAxisVelocity();
					ball.viewAppearance()->MoveToY(client_view_->bottom - ball.viewAppearance()->Size().cy);
				}
				else if(ball.viewAppearance()->top <= client_view_->top)
				{
					ball.reverseYAxisVelocity();
					ball.viewAppearance()->MoveToY(0);
				}
				ball.move();
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

		void updateBalls(CRect* client_view)
		{			
			// client_view_ = client_view;
			// for (auto& ball : ball_pool_)
			// {
			// 	const auto position = ball.viewPosition();
			// 	if (position.getX() + ball.getRadius() >= static_cast<unsigned int>(client_view_->Width()))
			// 	{
			// 		ball.setX(static_cast<unsigned int>(client_view_->Width()) - ball.getRadius() - 1);
			// 		ball.reverseXAxisVelocity();
			// 	}
			// 	else if (position.getX() <= ball.getRadius())
			// 	{
			// 		ball.setX(ball.getRadius() + 1);
			// 		ball.reverseXAxisVelocity();
			// 	}
			//
			// 	if (position.getY() + ball.getRadius() >= static_cast<unsigned int>(client_view_->Height()))
			// 	{
			// 		ball.setY(static_cast<unsigned int>(client_view_->Height()) - ball.getRadius() - 1);
			// 		ball.reverseYAxisVelocity();
			// 	}
			// 	else if (position.getY() <= ball.getRadius())
			// 	{
			// 		ball.setY(ball.getRadius() + 1);
			// 		ball.reverseYAxisVelocity();
			// 	}
			// }		
		}
	};
}
