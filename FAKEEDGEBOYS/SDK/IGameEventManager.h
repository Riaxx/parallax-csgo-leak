/* Credits: Casual_Hacker @ http://www.unknowncheats.me/forum/counterstrike-global-offensive/163543-eventsmanager.html */

struct DamageText_t {
	int iDamage;
	char szWeapon[32];
	float flEnd;
	DamageText_t(){}
	DamageText_t(int iDamage, char *szWeapon, float flEnd) {
		strcpy(this->szWeapon, szWeapon);
		this->iDamage = iDamage;
		this->flEnd = flEnd;
	}
};


class IGameEvent {
public:
	virtual ~IGameEvent() {};
	virtual const char *GetName() const = 0;    // get event name

	virtual bool  IsReliable() const = 0; // if event handled reliable
	virtual bool  IsLocal() const = 0; // if event is never networked
	virtual bool  IsEmpty(const char *keyName = NULL) = 0; // check if data field exists

	// Data access
	virtual bool  GetBool(const char *keyName = NULL, bool defaultValue = false) = 0;
	virtual int   GetInt(const char *keyName = NULL, int defaultValue = 0) = 0;
	virtual unsigned long long GetUint64(char const *keyName = NULL, unsigned long long defaultValue = 0) = 0;
	virtual float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f) = 0;

	virtual const char *GetString(const char *keyName = NULL, const char *defaultValue = "") = 0;
	virtual const wchar_t *GetWString(char const *keyName = NULL, const wchar_t *defaultValue = L"") = 0;

	virtual void SetBool(const char *keyName, bool value) = 0;
	virtual void SetInt(const char *keyName, int value) = 0;
	virtual void SetUInt64(const char *keyName, unsigned long long value) = 0;
	virtual void SetFloat(const char *keyName, float value) = 0;
	virtual void SetString(const char *keyName, const char *value) = 0;
	virtual void SetWString(const char *keyName, const wchar_t *value) = 0;
public:
	int m_iDamageText;
	DamageText_t DamageText[15];
};