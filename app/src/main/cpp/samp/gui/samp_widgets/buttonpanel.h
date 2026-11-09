#pragma once

#include "../widgets/button.h"
#include "../widgets/layout.h"

class ButtonPanel : public Layout
{
public:
	ButtonPanel();
	virtual void draw(ImGuiRenderer* renderer) override;

	CButton* m_bH;

private:
	OButton* m_bOpen;
	CButton* m_bClose;
	
	// В соответствии со старым .h файлом эти кнопки должны быть типа Button*
	Button* m_bAlt;
	Button* m_bY;
	Button* m_bN;
	
	// Контекстные кнопки и TAB (кастомные CButton)
	CButton* m_bF;
	CButton* m_bG;
	CButton* m_b2;
	CButton* m_bTab;
};
