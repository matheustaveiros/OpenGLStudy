#pragma once

#include <unordered_map>
#include <vector>
#include <span>
class PhysicsLayer
{
public:
	enum class Layer
	{
		None = -1,
		Default = 0,
		Player = 1,
		Enemy = 2,
		Scenario = 3
	};

	static void SetLayerCollision(const Layer& layer, const std::vector<Layer>& collision)
	{
		if (!_collisionMatrix.contains(layer))
		{
			_collisionMatrix.try_emplace(layer, collision);
		}
		else
		{
			_collisionMatrix[layer] = collision;
		}
	}

	static std::span<Layer> GetCollisionLayers(const Layer& layer)
	{
		return _collisionMatrix[layer];
	}

private:
	static std::unordered_map<Layer, std::vector<Layer>> _collisionMatrix;
};