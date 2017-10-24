class C_BaseEntityList {
public:

	virtual C_BaseEntity*   GetClientNetworkable(int entnum) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
	virtual C_BaseEntity*        GetClientEntity(int entNum) = 0;
	virtual C_BaseEntity*        GetClientEntityFromHandle(int hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int GetMaxEntities() = 0;
};