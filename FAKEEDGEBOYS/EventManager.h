#define EVENT_HOOK( x )

class IGameEvent
{
public:

	const char* GetName()
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return ReadFunc<OriginalFn>(this, 1)(this);
	}

	int GetInt(const char *keyName, int defaultValue)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const char *, int);
		return ReadFunc<OriginalFn>(this, 6)(this, keyName, defaultValue);
	}
	bool GetBool(const char *keyName, bool value)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, const char *, bool);
		return ReadFunc<OriginalFn>(this, 5)(this, keyName, value);
	}
	char GetString(const char *keyName, const char *value)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, const char *, const char *);
		return ReadFunc<OriginalFn>(this, 9)(this, keyName, value);
	}
	/*bool GetBool(const char *keyName, bool value)
	{
	typedef bool(__thiscall* OriginalFn)(PVOID, const char *, bool);
	return getvfunc<OriginalFn>(this, 5)(this, keyName, value);
	}*/
};



class IGameEventListener2
{
public:
	virtual	~IGameEventListener2(void) {};

	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent(IGameEvent *event) = 0;
	int m_nDebugID;
	virtual int GetEventDebugID(void) { return m_nDebugID; }
};

struct DamageText_t
{
	int iDamage;
	char szWeapon[32];
	float flEnd;
	DamageText_t() {}
	DamageText_t(int iDamage, char *szWeapon, float flEnd)
	{
		strcpy(this->szWeapon, szWeapon);
		this->iDamage = iDamage;
		this->flEnd = flEnd;
	}
};

class cGameEvent : public IGameEventListener2
{

private:

	int m_iDamageText;
	DamageText_t DamageText[15];

public:

	void FireGameEvent(IGameEvent *event);
	void RegisterSelf();
	void Register();

	DamageText_t GetDamageText(int nId)
	{
		return DamageText[nId];
	}

	char czWeapon[30];

};
extern cGameEvent gEvent;



class IGameEventManager
{
public:
	bool AddListener(IGameEventListener2 *listener, const char *name, bool bServerSide)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, IGameEventListener2*, const char*, bool);
		return ReadFunc<OriginalFn>(this, 3)(this, listener, name, bServerSide);
	}

	bool FireEventClientSide(IGameEvent *event)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, IGameEvent*);
		return ReadFunc<OriginalFn>(this, 8)(this, event);
	}
};

void cGameEvent::FireGameEvent(IGameEvent *event)
{
	const char* szEventName = event->GetName();
	if (!szEventName)	return;

	if (strcmp(szEventName, "round_start") == 0)
	{
		//pValve->pEngine->ExecuteClientCmd("say OH SHIT WADDUP");
	}

}


void cGameEvent::Register()
{
	EVENT_HOOK(FireEvent);
}