#pragma once

#include "PacManBase.h"
#include "logic/PacManLogic.h"

class PacMan
{
public:
	PacMan() {}
	~PacMan() {}

	void Startup();
	bool Runtime(daTimestep ts);
	void Shutdown();

	float GetTime() { return this->m_Timer.ElapsedMillis(); }

	bool IsRunning() { return this->m_Running; }
	void SetIsRunning(bool enable) { this->m_Running = enable; }

	float GetLastFrameTime() { return this->m_LastFrameTime; }
	void SetLastFrameTime(float time) { this->m_LastFrameTime = time; }

	//void OnEvent(daEvent& e)
	//{
	//	daEventDispatcher dispatcher(e);
	//	dispatcher.Dispatch<daKeyPressedEvent>(DA_BIND_EVENT_FN(PacMan::OnKeyPressed));
	//	dispatcher.Dispatch<daMouseButtonPressedEvent>(DA_BIND_EVENT_FN(PacMan::OnMouseButtonPressed));
	//}
private:
	PacManLogic s_Logic;
	daTimer m_Timer;
	bool m_Running = true;
	float m_LastFrameTime = 0.0f;
};

