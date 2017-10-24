class IClientEntityList {
public:
	virtual void Unk0();
	virtual void Unk1();
	virtual void Unk2();
	virtual C_BaseEntity* GetClientEntity(int entnum);
	virtual C_BaseEntity* GetClientEntityFromHandle(ULONG handle);
	virtual void Unk5();
	virtual int GetHighestEntityIndex(void);
	virtual void Unk6();
	virtual void Unk7();
};