#include "../../main.h"
#include "..//gui.h"
#include "button.h"

extern bool OpenButton;

// ============== Обычная кнопка (Button) =========================//
Button::Button(const std::string& caption, float font_size)
{
	m_callback = nullptr;

	m_label = new Label(caption, ImColor(1.0f, 1.0f, 1.0f), false, font_size);
	this->addChild(m_label);

	m_color = UISettings::buttonColor();
	m_colorFocused = UISettings::buttonFocusedColor();
}

void Button::performLayout()
{
	float padding = UISettings::padding();

	m_label->performLayout();
	this->setSize(m_label->size() + ImVec2(padding * 2, padding / 2 * 2));

	m_label->setPosition((size() - m_label->size()) / 2);
}

void Button::draw(ImGuiRenderer* renderer)
{
	renderer->drawRect(absolutePosition(), absolutePosition() + size(),
		focused() ? m_colorFocused : m_color, true);

	// Старая серая обводка (Outline) для обычных кнопок диалогов
	renderer->drawRect(absolutePosition() + ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		(absolutePosition() + size()) - ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		ImColor(0.287f, 0.287f, 0.287f, 0.890f), false, UISettings::outlineSize());

	Widget::draw(renderer);
}

void Button::touchPopEvent()
{
	if (m_callback) m_callback();
}


//============== Кастомная кнопка панели (CButton) =========================//
CButton::CButton(const std::string& caption, float font_size)
{
	m_callback = nullptr;

	m_label = new Label(caption, ImColor(1.0f, 1.0f, 1.0f), false, font_size);
	this->addChild(m_label);

	m_color = UISettings::buttonColor();
	m_colorFocused = UISettings::buttonFocusedColor();
}

void CButton::performLayout()
{
	float padding = UISettings::padding();

	m_label->performLayout();
	this->setSize(m_label->size() + ImVec2(padding * 2, padding / 2 * 2));

	m_label->setPosition((size() - m_label->size()) / 2);
}

void CButton::draw(ImGuiRenderer* renderer)
{
	renderer->drawRect(absolutePosition(), absolutePosition() + size(),
		focused() ? m_colorFocused : m_color, true);

	// Старая голубая обводка для кастомных кнопок панели
	renderer->drawRect(absolutePosition() + ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		(absolutePosition() + size()) - ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		ImColor(0x64, 0x95, 0xED), false, UISettings::outlineSize());

	Widget::draw(renderer);
}

void CButton::touchPopEvent()
{
	if (m_callback) m_callback();
}


//======== Кнопка открытия панели >> (OButton) ====================//
OButton::OButton(const std::string& caption, float font_size)
{
	m_callback = nullptr;

	m_label = new Label(caption, ImColor(1.0f, 1.0f, 1.0f), false, font_size);
	this->addChild(m_label);

	m_color = UISettings::buttonColor();
	m_colorFocused = UISettings::buttonFocusedColor();
}

void OButton::performLayout()
{
	float padding = UISettings::padding();

	m_label->performLayout();
	this->setSize(m_label->size() + ImVec2(padding * 2, padding / 2 * 2));

	m_label->setPosition((size() - m_label->size()) / 2);
}

void OButton::draw(ImGuiRenderer* renderer)
{
	renderer->drawRect(absolutePosition(), absolutePosition() + size(),
		focused() ? m_colorFocused : m_color, true);

	// Голубая обводка для стрелочки открытия
	renderer->drawRect(absolutePosition() + ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		(absolutePosition() + size()) - ImVec2(UISettings::outlineSize(), UISettings::outlineSize()),
		ImColor(0x64, 0x95, 0xED), false, UISettings::outlineSize());

	Widget::draw(renderer);
}

void OButton::touchPopEvent()
{
	if (m_callback) m_callback();
}
