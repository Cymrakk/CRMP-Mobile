#pragma once

#include "../widgets/button.h"
#include "../widgets/layout.h"

class ButtonPanel : public Layout
{
public:
	ButtonPanel();
	CButton* m_bH;
	// Метод покадровой сборки панели без лишних кнопок
	virtual void draw(ImGuiRenderer* renderer) override;

private:
	OButton* m_bOpen;
	CButton* m_bClose;
	CButton* m_bAlt;
	CButton* m_bY;
	CButton* m_bN;
	CButton* m_bF;
	CButton* m_bG;
	CButton* m_b2;
	CButton* m_bTab; // Кнопка TAB осталась и будет выводиться последней
};

