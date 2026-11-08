#include "../../main.h"
#include "..//gui.h"
#include "button.h"

extern bool OpenButton;

// --- СТАРАЯ КЛАССИЧЕСКАЯ ОТРИСОВКА FLAT-КНОПОК (БЕЗ ОБВОДКИ) ---
void DrawBaseButton(Widget* widget, ImGuiRenderer* renderer, const ImColor& color)
{
	// Просто плоская заливка прямоугольника кнопки, как в старом ImGui
	renderer->drawRect(widget->absolutePosition(), widget->absolutePosition() + widget->size(), color, true);
}

// ================== ОБЫЧНАЯ КНОПКА (Button) ==================
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
	// Точные размеры под старый лаунчер (55x40 в координатах новой системы)
	this->setFixedSize(ImVec2(55.0f, 40.0f));
	m_label->performLayout();
	m_label->setPosition((size() - m_label->size()) / 2);
}

void Button::draw(ImGuiRenderer* renderer)
{
	DrawBaseButton(this, renderer, focused() ? m_colorFocused : m_color);
	Widget::draw(renderer);
}

void Button::touchPopEvent()
{
	if (m_callback) m_callback();
}


// ================== КАСТОМНАЯ КНОПКА ПАНЕЛИ (CButton) ==================
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
	this->setFixedSize(ImVec2(55.0f, 40.0f));
	m_label->performLayout();
	m_label->setPosition((size() - m_label->size()) / 2);
}

void CButton::draw(ImGuiRenderer* renderer)
{
	DrawBaseButton(this, renderer, focused() ? m_colorFocused : m_color);
	Widget::draw(renderer);
}

void CButton::touchPopEvent()
{
	if (m_callback) m_callback();
}


// ================== КНОПКА ОТКРЫТИЯ ПАНЕЛИ >> (OButton) ==================
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
	this->setFixedSize(ImVec2(55.0f, 40.0f));
	m_label->performLayout();
	m_label->setPosition((size() - m_label->size()) / 2);
}

void OButton::draw(ImGuiRenderer* renderer)
{
	DrawBaseButton(this, renderer, focused() ? m_colorFocused : m_color);
	Widget::draw(renderer);
}

void OButton::touchPopEvent()
{
	if (m_callback) m_callback();
}
