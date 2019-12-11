#pragma once

#include <cinttypes>
#include <SFML/Graphics/ConvexShape.hpp>

#include "json.h"

namespace scenario
{
	namespace
	{
		class Lockable
		{
		private:
			bool _lock;

		protected:
			Lockable();

			void lock();
			bool isLocked();
		};
	}

	class Mesh : public JsonSerializable, Lockable
	{
	private:
		sf::ConvexShape _shape;

	public:
		Mesh();
		Mesh(const Mesh& mesh);

		Mesh& operator= (const Mesh& mesh);

		void addPoint(float x, float y);
		void addPoint(const sf::Vector2f& point);

		void setPoint(const size_t index, float x, float y);
		void setPoint(const size_t index, const sf::Vector2f& point);

		void setSize(const size_t size);

		float getPointX(const size_t index) const;
		float getPointY(const size_t index) const;
		const sf::Vector2f& getPoint(const size_t index) const;

		size_t size() const;
		bool empty() const;

		Json serialize() const;
		void unserialize(const Json& json);
	};
}
