#include "Scene.h"
#include "physics/Collision.h"

Scene::Scene(const std::string& name) : _name { name }
{
	Scene::ActiveScene = this;
}

void Scene::DestroyGameObject(Guid guid)
{
	if (_gameObjectsMap.contains(guid))
	{
		auto iterator = _gameObjectsMap.find(guid);
		_gameObjectsMap.erase(iterator);
	}
	else
	{
		std::cout << "Unable to Destroy object, the object didn't exist in the scene" << std::endl;
	}
}

Text* Scene::InstantiateText()
{
	Guid newGuid{};
	_textObjectsMap.emplace(newGuid, std::make_unique<Text>(newGuid));

	return _textObjectsMap[newGuid].get();
}

void Scene::DestroyText(Guid guid)
{
	if (_textObjectsMap.contains(guid))
	{
		auto iterator = _textObjectsMap.find(guid);
		_textObjectsMap.erase(iterator);
	}
	else
	{
		std::cout << "Unable to Destroy object, the object didn't exist in the scene" << std::endl;
	}
}

void Scene::Awake()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnAwake();
	}

	OnAwake();
}

void Scene::OnAwake(){}

void Scene::Start()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnStart();
	}

	OnStart();
}

void Scene::OnStart(){}

void Scene::UpdateInput()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnUpdateInput();
	}

	OnUpdateInput();
}

void Scene::OnUpdateInput(){}

void Scene::UpdatePhysics()
{
	for (const auto&[guid, obj] : _gameObjectsMap)
	{
		GameObject* objPtr = obj.get();
		if (!objPtr->IsActive())
			continue;

		for (const auto& [otherGuid, otherObj] : _gameObjectsMap)
		{
			GameObject* otherPtr = otherObj.get();

			if (!otherPtr->IsActive())
				continue;

			if (guid == otherGuid)
				continue;

			if (!objPtr->CanCollideWith(otherPtr))
				continue;

			if (Collision::IsColliding(objPtr, otherPtr))
			{
				objPtr->OnCollide(otherPtr);
			}
			else
			{
				objPtr->OnExitCollision(otherPtr);
			}
		}

		objPtr->OnUpdatePhysics();
	}

	OnUpdatePhysics();
}

void Scene::OnUpdatePhysics(){}

void Scene::Update()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnUpdate();
	}

	OnUpdate();
}

void Scene::OnUpdate(){}

void Scene::Render()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnRender();
	}

	for (const auto& [guid, text] : _textObjectsMap)
	{
		text.get()->Draw();
	}
	
	OnRender();
}

void Scene::OnRender(){}

void Scene::PostRenderUpdate()
{
	for (const auto& [guid, obj] : _gameObjectsMap)
	{
		obj.get()->OnPostRenderUpdate();
	}

	OnPostRenderUpdate();
}

void Scene::OnPostRenderUpdate(){}
