#pragma once

#include <SFML/Graphics.hpp>
#include <cinttypes>
#include <iostream>
#include <functional>
#include <vector>

#include "utils.h"

using delta_t = float;

class GameController;

class UUID
{
private:
	uint64_t _code;

	inline UUID(const uint64_t code) :
		_code{ code }
	{}

public:
	UUID(const UUID& id);

	UUID& operator= (const UUID& id);

	static UUID generate();

	inline bool operator== (const UUID& id) const { return _code == id._code; }
	inline bool operator!= (const UUID& id) const { return _code != id._code; }
	inline bool operator> (const UUID& id) const { return _code > id._code; }
	inline bool operator< (const UUID& id) const { return _code < id._code; }
	inline bool operator>= (const UUID& id) const { return _code >= id._code; }
	inline bool operator<= (const UUID& id) const { return _code <= id._code; }

	inline operator bool() const { return _code; }
	inline bool operator! () const { return !_code; }

	friend std::ostream& operator<< (std::ostream& os, const UUID& id);
	friend std::istream& operator>> (std::istream& is, UUID& id);
};

std::ostream& operator<< (std::ostream& os, const UUID& id);
std::istream& operator>> (std::istream& is, UUID& id);


template<UUID(*_IdGen)() = &UUID::generate>
class UniqueObject
{
private:
	const UUID _id;

public:
	inline UniqueObject() :
		_id{ _IdGen() }
	{}

	inline UUID getId() const { return _id; }

	inline bool operator== (const UniqueObject& obj) const { return _id == obj._id; }
	inline bool operator!= (const UniqueObject& obj) const { return _id != obj._id; }
};



class GameObject : public UniqueObject<>
{
private:
	std::string _tag;
	GameController* _gc;

public:
	GameObject(const std::string& tag);
	GameObject(const char* tag = "");
	virtual ~GameObject();

	const std::string& getTag() const;
	void setTag(const std::string& tag);
	void setTag(const char* tag);

	bool hasGameControllerAttached() const;

	virtual void render(sf::RenderTarget* g);
	virtual void update(const delta_t delta);
	virtual void dispatchEvent(const sf::Event& event);

protected:
	GameController* getGameController();

public:
	friend class GameController;
};



class GameObjectContainer
{
protected:
	std::vector<GameObject*> _objs;

public:
	GameObjectContainer();
	virtual ~GameObjectContainer();

	void addGameObject(GameObject* obj);

	void destroyGameObject(const Accessor<GameObject> obj);
	void destroyGameObject(const UUID id);
	void destroyAllGameObjects();

	GameObject* eraseGameObject(const Accessor<GameObject> obj);
	GameObject* eraseGameObject(const UUID id);

	Accessor<GameObject> getGameObject(const size_t index) const;
	Accessor<GameObject> findGameObject(const UUID id) const;

	void forEachGameObject(std::function<void(Accessor<GameObject>)> action);
	void forEachGameObject(std::function<void(const Accessor<GameObject>)> action) const;

	size_t getGameObjectCount() const;

protected:
	virtual void _beforeAdd(Accessor<GameObject>& obj) const;
	virtual void _afterAdd(Accessor<GameObject>& obj) const;

	virtual void _beforeErase(Accessor<GameObject>& obj) const;
	virtual void _afterErase(Accessor<GameObject>& obj) const;

	std::vector<GameObject*>::iterator _findGameObject(std::function<bool(GameObject*)> predicate);
	std::vector<GameObject*>::const_iterator _findGameObject(std::function<bool(const GameObject*)> predicate) const;

	std::vector<GameObject*>::iterator _findGameObjectById(const UUID id);
	std::vector<GameObject*>::const_iterator _findGameObjectById(const UUID id) const;

public:
	template<class _GOType, class... __Args>
	inline Accessor<_GOType> createGameObject(__Args&&... args)
	{
		static_assert(std::is_base_of(_GOType, GameObject));
		_GOType* obj = new _GOType(args...);
		addGameObject(obj);
		return obj;
	}

	template<class _GOType>
	inline Accessor<_GOType> createGameObject()
	{
		static_assert(std::is_base_of(_GOType, GameObject));
		_GOType* obj = new _GOType();
		addGameObject(obj);
		return obj;
	}
};
