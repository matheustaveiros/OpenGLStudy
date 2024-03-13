#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "render/Text.h"

class Screen : public GameObject
{
private:
	std::vector<std::unique_ptr<Text>> _texts;
	std::string _key;
protected:
	Text* InstantiateText();

public:
	Screen(Guid guid);
	void OnRender() override;
	void SetKey(const std::string& key) { _key = key; }
};

