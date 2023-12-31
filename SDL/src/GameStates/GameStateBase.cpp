#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSHelp.h"
#include "GSSelectLevel.h"
#include "GSOver.h"
#include "GSSetting.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSHelp>();
		//GSCREDIT
		break;
	case StateType::STATE_SELECT_LEVEl:
		gs = std::make_shared<GSSelectLevel>();
		//GSSELECTLEVEL
		break;
	case StateType::STATE_OVER:
		gs = std::make_shared<GSOver>();
		//GSOver
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		//GSOver
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
