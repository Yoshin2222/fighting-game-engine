#include "conditions.hpp"

//Conditions

bool helperCompare(CmpType t, int v1, int v2)
{
	switch(t)
	{
	case CMP_LT:	// <
//		printf("CMP_LT: %i < %i\n", v1, v2);
		return v1 < v2;
	case CMP_LTE:	// <=
		return v1 <= v2;
	case CMP_GT:	// >
//		printf("CMP_GT: %i > %i\n", v1, v2);
		return v1 > v2;
	case CMP_GTE:	// >=
		return v1 >= v2;
	case CMP_E:
//		printf("CMP_E: %i == %i\n", v1, v2);
		return v1 == v2;
	default:
		ASSERT(false);
		return false;
	}
}
//COMPARE METER: Compares the meter
Cnd_compareMeter::Cnd_compareMeter()
{
	ASSERT(false);
}

Cnd_compareMeter::Cnd_compareMeter(Character* obj, Meter meter, CmpType t, int value)
: m_meter(meter), m_t(t), m_value(value)
{
	this->Condition::m_obj = obj;
}

bool Cnd_compareMeter::check()
{
	return helperCompare(m_t,  ((Character*)m_obj)->getMeter(m_meter), m_value);
}

Cnd_compareMeter* Cnd_compareMeter::clone()
{
	return new Cnd_compareMeter(*this);
}

//FRAME: Checks the frame. Based on the frame stored in the
//Character it is passed.
Cnd_frame::Cnd_frame()
{
	ASSERT(false);
}

Cnd_frame::Cnd_frame(GameObject* obj, unsigned int frame, CmpType t)
: m_frame(frame), m_t(t)
{
	this->Condition::m_obj = obj;
}

bool Cnd_frame::check()
{
	return helperCompare(m_t, g_frame, m_frame);
}

Cnd_frame* Cnd_frame::clone()
{
	return new Cnd_frame(*this);
}

//FRAMES SINCE: More useful thane FRAME. Checks the number of
//frames since the Character's current move was executed
Cnd_framesSince::Cnd_framesSince()
{
	ASSERT(false);
}

Cnd_framesSince::Cnd_framesSince(GameObject* obj, unsigned int frames, CmpType t)
: m_frames(frames), m_t(t)
{
	this->Condition::m_obj = obj;
}

bool Cnd_framesSince::check()
{
//	return helperCompare(m_t, 
//						m_obj->getFrame() - m_obj->getMove()->getStartFrame(), 
//						m_frames);
	//new version using global frame indicator
	return helperCompare(m_t, 
						g_frame - m_obj->getMove()->getStartFrame(), 
						m_frames);

}

Cnd_framesSince* Cnd_framesSince::clone()
{
	return new Cnd_framesSince(*this);
}


//MOVE: 
Cnd_move::Cnd_move()
{
	ASSERT(false);
}

Cnd_move::Cnd_move(GameObject *obj, std::string cmpName)
: m_cmpName(cmpName)
{
	this->Condition::m_obj = obj;
}

bool Cnd_move::check()
{
	return *( m_obj->getMove()->getName() ) == m_cmpName;
}

Cnd_move* Cnd_move::clone()
{
	return new Cnd_move(*this);
}
