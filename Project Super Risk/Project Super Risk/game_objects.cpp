#include "game_objects.h"
#include "engine.h"

UUID::UUID(const UUID& id) :
	_code{ id._code }
{}

UUID& UUID::operator= (const UUID& id)
{
	_code = id._code;
	return *this;
}

UUID UUID::generate()
{
	static uint64_t generator = 0;
	return { ++generator };
}

std::ostream& operator<< (std::ostream& os, const UUID& id) { return os << id._code; }
std::istream& operator>> (std::istream& is, UUID& id) { return is >> id._code; }



GameObject::GameObject(const std::string& tag) :
	UniqueObject{},
	_tag{ tag },
	_gc{ nullptr }
{}
GameObject::GameObject(const char* tag) :
	UniqueObject{},
	_tag{ tag },
	_gc{ nullptr }
{}
GameObject::~GameObject() {}

const std::string& GameObject::getTag() const { return _tag; }
void GameObject::setTag(const std::string& tag) { _tag = tag; }
void GameObject::setTag(const char* tag) { _tag = tag; }

bool GameObject::hasGameControllerAttached() const { return _gc; }

void GameObject::render(sf::RenderTarget* g) {}
void GameObject::update(const delta_t delta) {}
void GameObject::dispatchEvent(const sf::Event& event) {}

GameController* GameObject::getGameController() { return _gc; }



GameObjectContainer::GameObjectContainer() :
	_objs{}
{}
GameObjectContainer::~GameObjectContainer() {}

void GameObjectContainer::addGameObject(GameObject* obj)
{
	Accessor<GameObject> a{ obj };
	_beforeAdd(a);
	_objs.push_back(obj);
	_afterAdd(a);
}

void GameObjectContainer::destroyGameObject(const Accessor<GameObject> obj) { destroyGameObject(obj->getId()); }
void GameObjectContainer::destroyGameObject(const UUID id)
{
	auto it = _findGameObjectById(id);
	if (it != _objs.end())
	{
		GameObject* obj = *it;
		Accessor<GameObject> a{ obj };
		_beforeErase(a);
		_objs.erase(it);
		_afterErase(a);
		delete obj;
	}
}
void GameObjectContainer::destroyAllGameObjects()
{
	for (auto obj : _objs)
		delete obj;
	_objs.clear();
}

GameObject* GameObjectContainer::eraseGameObject(const Accessor<GameObject> obj) { return eraseGameObject(obj->getId()); }
GameObject* GameObjectContainer::eraseGameObject(const UUID id)
{
	auto it = _findGameObjectById(id);
	if (it != _objs.end())
	{
		GameObject* obj = *it;
		Accessor<GameObject> a{ obj };
		_beforeErase(a);
		_objs.erase(it);
		_afterErase(a);
		return obj;
	}
	return nullptr;
}

Accessor<GameObject> GameObjectContainer::getGameObject(const size_t index) const
{
	return index >= _objs.size() ? nullptr : _objs[index];
}
Accessor<GameObject> GameObjectContainer::findGameObject(const UUID id) const
{
	auto it = _findGameObjectById(id);
	return it == _objs.end() ? nullptr : *it;
}

void GameObjectContainer::forEachGameObject(std::function<void(Accessor<GameObject>)> action)
{
	for (auto obj : _objs)
		action(obj);
}
void GameObjectContainer::forEachGameObject(std::function<void(const Accessor<GameObject>)> action) const
{
	for (auto obj : _objs)
		action(obj);
}

size_t GameObjectContainer::getGameObjectCount() const { return _objs.size(); }

void GameObjectContainer::_beforeAdd(Accessor<GameObject>& obj) const {}
void GameObjectContainer::_afterAdd(Accessor<GameObject>& obj) const {}

void GameObjectContainer::_beforeErase(Accessor<GameObject>& obj) const {}
void GameObjectContainer::_afterErase(Accessor<GameObject>& obj) const {}

std::vector<GameObject*>::iterator GameObjectContainer::_findGameObject(std::function<bool(GameObject*)> predicate)
{
	return std::find_if(_objs.begin(), _objs.end(), predicate);
}
std::vector<GameObject*>::const_iterator GameObjectContainer::_findGameObject(std::function<bool(const GameObject*)> predicate) const
{
	return std::find_if(_objs.begin(), _objs.end(), predicate);
}

std::vector<GameObject*>::iterator GameObjectContainer::_findGameObjectById(const UUID id)
{
	return _findGameObject([id](GameObject* obj) -> bool { return obj && obj->getId() == id; });
}
std::vector<GameObject*>::const_iterator GameObjectContainer::_findGameObjectById(const UUID id) const
{
	return _findGameObject([id](const GameObject* obj) -> bool { return obj && obj->getId() == id; });
}
