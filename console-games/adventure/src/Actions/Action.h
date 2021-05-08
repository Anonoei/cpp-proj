#pragma once

#include "Core/Base.h"

class Action
{
public:
	Action() {}
	~Action() {}

	void Preform() {}
	void SetName(const char* name) { this->m_Name = name; }

	const char* GetName() { return this->m_Name; }
	UUID GetUUID() { return this->m_UUID; }
protected:
	const char* m_Name = "default";
	UUID m_UUID;
};

