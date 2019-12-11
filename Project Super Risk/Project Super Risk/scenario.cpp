#include "scenario.h"

#include "limit.h"

#define check_bounds(idx) ((idx) >= 0 && (idx) < this->_shape.getPointCount())


scenario::Lockable::Lockable() :
	_lock{}
{}

void scenario::Lockable::lock() { _lock = true; }
bool scenario::Lockable::isLocked() { return _lock; }




scenario::Mesh::Mesh() :
	_shape{}
{}
scenario::Mesh::Mesh(const scenario::Mesh& mesh) :
	_shape{ mesh._shape }
{}

scenario::Mesh& scenario::Mesh::operator= (const scenario::Mesh& mesh)
{
	_shape = mesh._shape;
	return *this;
}

void scenario::Mesh::addPoint(float x, float y)
{
	addPoint({ x, y });
}
void scenario::Mesh::addPoint(const sf::Vector2f& point)
{
	const auto size = _shape.getPointCount();
	_shape.setPointCount(size + 1);
	_shape.setPoint(size, point);
}

void scenario::Mesh::setPoint(const size_t index, float x, float y)
{
	setPoint(index, { x, y });
}
void scenario::Mesh::setPoint(const size_t index, const sf::Vector2f& point)
{
	if (check_bounds(index))
		_shape.setPoint(index, point);
}

void scenario::Mesh::setSize(const size_t size)
{
	_shape.setPointCount(utils::max(size_t{ 3 }, size));
}

float scenario::Mesh::getPointX(const size_t index) const
{
	return getPoint(index).x;
}
float scenario::Mesh::getPointY(const size_t index) const
{
	return getPoint(index).y;
}
const sf::Vector2f& scenario::Mesh::getPoint(const size_t index) const
{
	return check_bounds(index) ? _shape.getPoint(index) : sf::Vector2f{};
}

size_t scenario::Mesh::size() const { return _shape.getPointCount(); }
bool scenario::Mesh::empty() const { return _shape.getPointCount() < 1; }

Json scenario::Mesh::serialize() const
{
	Json j;
	const size_t size = this->size();
	j["count"] = static_cast<int32_t>(size);
	
	std::vector<int32_t> x_axis{ static_cast<int32_t>(size) };
	std::vector<int32_t> y_axis{ static_cast<int32_t>(size) };
	for (size_t i = 0; i < size; ++i)
	{
		const auto& point = _shape.getPoint(i);
		x_axis[i] = static_cast<int32_t>(point.x);
		y_axis[i] = static_cast<int32_t>(point.y);
	}
	j["x_axis"] = x_axis;
	j["y_axis"] = y_axis;

	return std::move(j);
}

void scenario::Mesh::unserialize(const Json& json)
{
	try
	{
		const size_t size = json["count"].get<int32_t>();
		_shape.setPointCount(size);

		if (size > 0)
		{
			std::vector<int32_t> x_axis{ json["x_axis"].get<std::vector<int32_t>>() };
			std::vector<int32_t> y_axis{ json["y_axis"].get<std::vector<int32_t>>() };

			const size_t len = utils::min(utils::min(x_axis.size(), y_axis.size()), size);
			for (size_t i = 0; i < len; ++i)
				_shape.setPoint(i, { static_cast<float>(x_axis[i]), static_cast<float>(y_axis[i]) });
		}
	}
	catch (...)
	{
		_shape.setPointCount(0);
	}
}
