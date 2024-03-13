#include "Screen.h"

Screen::Screen(Guid guid) : GameObject(guid)
{

}

void Screen::OnRender()
{
	if (!IsActive())
		return;

	for (const auto& text : _texts)
	{
		text->Draw();
	}
}

Text* Screen::InstantiateText()
{
	_texts.emplace_back(std::make_unique<Text>());
	return _texts.back().get();
}