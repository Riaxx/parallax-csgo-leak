class player_info_t {
public:
	char __pad1[0x10];
	char name[32];//80
	char __pad2[0x64];
	char guid[32 + 1];
	char __pad3[0x17B];
	bool fakeplayer;
};