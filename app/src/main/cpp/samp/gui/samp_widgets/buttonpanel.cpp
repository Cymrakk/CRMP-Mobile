#include "../../main.h"
#include "../gui.h"
#include "../../game/game.h"
#include "../../net/netgame.h"
#include "../../net/localplayer.h"

extern UI* pUI;
extern CNetGame* pNetGame;
extern CGame *pGame;

bool bNeedEnterVehicle = false;
bool OpenButton = false;
int Tab = 0;

ButtonPanel::ButtonPanel()
	: Layout(Orientation::HORIZONTAL)
{
	m_bTab   = new CButton("TAB", UISettings::fontSize() / 2);
	m_bOpen  = new OButton(">>", UISettings::fontSize() / 2);
	m_bClose = new CButton("<<", UISettings::fontSize() / 2);
	
	// Выделение памяти в строгом соответствии со старым типами из .h
	m_bAlt   = new Button("ALT", UISettings::fontSize() / 2);
	m_bH     = new CButton("H", UISettings::fontSize() / 2);
	m_bY     = new Button("Y", UISettings::fontSize() / 2);
	m_bN     = new Button("N", UISettings::fontSize() / 2);
	
	m_bF     = new CButton("F", UISettings::fontSize() / 2);
	m_bG     = new CButton("G", UISettings::fontSize() / 2);
	m_b2     = new CButton("2", UISettings::fontSize() / 2);
	
	m_bOpen->setCallback([]()  { OpenButton = true; });
	m_bClose->setCallback([]() { OpenButton = false; });

	m_bTab->setCallback([]() 
	{ 
		if (Tab == 0) {
			if (pUI) { pUI->playertablist()->show(); Tab = 1; }
		}
		else {
			Tab = 0;
		}
	});

	m_bAlt->setCallback([this]() {
		if (pNetGame && pNetGame->GetPlayerPool()) {
			CPlayerPed* pLocalPed = pGame->FindPlayerPed();
			if (pLocalPed) {
				if (!pLocalPed->IsInVehicle() && !pLocalPed->IsAPassenger())
					LocalPlayerKeys.bKeys[ePadKeys::KEY_WALK] = true;
				else
					LocalPlayerKeys.bKeys[ePadKeys::KEY_FIRE] = true;
			}
		}
	});

	m_bH->setCallback([this]() { if(m_bH->visible()) LocalPlayerKeys.bKeys[ePadKeys::KEY_CTRL_BACK] = true; });
	m_bY->setCallback([this]() { if(m_bY->visible()) LocalPlayerKeys.bKeys[ePadKeys::KEY_YES] = true; });
	m_bN->setCallback([this]() { if(m_bN->visible()) LocalPlayerKeys.bKeys[ePadKeys::KEY_NO] = true; });
	m_bF->setCallback([this]() { if(m_bF->visible()) LocalPlayerKeys.bKeys[ePadKeys::KEY_SECONDARY_ATTACK] = true; });
	
	m_bG->setCallback([this]() { bNeedEnterVehicle = true; });
	m_b2->setCallback([this]() { LocalPlayerKeys.bKeys[ePadKeys::KEY_ACTION] = true; });
	
	this->addChild(m_bOpen);
	this->addChild(m_bClose);
	this->addChild(m_bAlt);
	this->addChild(m_bG);
	this->addChild(m_b2);
	this->addChild(m_bH);
	this->addChild(m_bF);
	this->addChild(m_bY);
	this->addChild(m_bN);
	this->addChild(m_bTab);
}

void ButtonPanel::draw(ImGuiRenderer* renderer)
{
	if (!pNetGame || (pUI && pUI->dialog() && pUI->dialog()->visible())) {
		return;
	}

	m_bOpen->setVisible(false);
	m_bClose->setVisible(false);
	m_bG->setVisible(false);
	m_b2->setVisible(false);
	m_bH->setVisible(false);
	m_bF->setVisible(false);
	m_bY->setVisible(false);
	m_bN->setVisible(false);
	m_bTab->setVisible(false);

	m_bAlt->setVisible(true);

	if (OpenButton) {
		m_bClose->setVisible(true);
		m_bH->setVisible(true);
		m_bF->setVisible(true);
		m_bY->setVisible(true);
		m_bN->setVisible(true);
		m_bTab->setVisible(true);
	} else {
		m_bOpen->setVisible(true);
	}

	if (pGame && pGame->FindPlayerPed()) {
		CPlayerPed* pLocalPed = pGame->FindPlayerPed();

		if (!pLocalPed->IsInVehicle() && !pLocalPed->IsAPassenger()) {
			if (pNetGame->GetVehiclePool()) {
				CVehiclePool* pVehiclePool = pNetGame->GetVehiclePool();
				VEHICLEID ClosetVehicleID = pVehiclePool->FindNearestToLocalPlayerPed();

				if (ClosetVehicleID != INVALID_VEHICLE_ID && pVehiclePool->GetSlotState(ClosetVehicleID)) {
					CVehicle* pVehicle = pVehiclePool->GetAt(ClosetVehicleID);
					if (pVehicle && pVehicle->m_pVehicle->GetDistanceFromLocalPlayerPed() < 5.0f) {
						m_bG->setVisible(true); 
					}
				}
			}
		} 
		else if (pLocalPed->IsInVehicle() && !pLocalPed->IsAPassenger()) {
			m_b2->setVisible(true); 
		}
	}

	Widget::draw(renderer);
}
