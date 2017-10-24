class player_info_t {
public:
	unsigned long long      unknown;
	unsigned long long      xuid;
	char                    name[128];
	int                     userID;
	char                    guid[32 + 1];
	unsigned int            friendsID;
	char                    friendsName[128];
	bool                    fakeplayer;
	bool                    ishltv;
	unsigned long           customFiles[4];
	unsigned char           filesDownloaded;
};