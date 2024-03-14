#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include "GameObject.h"
#include "Scene.h"

template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
class ObjectPooling
{
private:
    std::vector<T*> _pool;
    std::vector<bool> _available;

public:
    ObjectPooling() = default;
    ~ObjectPooling()
    {
        for (int i = 0; i < _pool.size(); i++)
        {
            Scene::ActiveScene->DestroyGameObject(dynamic_cast<GameObject*>(_pool[i])->GetGuid());
        }
    }

    int GetPoolSize() const { return static_cast<int>(_available.size()); }
    T* AccessObjectByIndex(int index) { return _pool[index]; }

    std::tuple<bool, T*> GetObjectAndState(int i)
    {
        return std::make_tuple(_available[i], _pool[i]);
    }

    T* GetObject()
    {
        for (size_t i = 0; i < _pool.size(); ++i)
        {
            if (_available[i])
            {
                _available[i] = false;
                return _pool[i];
            }
        }

        T* newObj = Scene::ActiveScene->InstantiateGameObject<T>();
        _pool.push_back(newObj);
        _available.push_back(false);
        return newObj;

        return nullptr;
    }

    void Release(const T* object)
    {
        for (size_t i = 0; i < _pool.size(); ++i)
        {
            if (_pool[i] == object)
            {
                if (!_available[i])
                {
                    _available[i] = true;
                    return;
                }
                else
                {
                    throw std::invalid_argument("Object already released");
                }
            }
        }
        throw std::invalid_argument("Object not found in pool");
    }
};
