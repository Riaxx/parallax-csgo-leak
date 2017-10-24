class player_info_t;


class INetChannelInfo
{
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMPENTS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char  *GetName(void) const = 0;	// get channel name
	virtual const char  *GetAddress(void) const = 0; // get channel IP address as string
	virtual float		GetTime(void) const = 0;	// current net time
	virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
	virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut(void) const = 0;	// true if timing out
	virtual bool		IsPlayback(void) const = 0;	// true if demo playback

	virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			GetTotalPackets(int flow) const = 0;
	virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;  // TCP progress if transmitting
	virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};



class IVEngineClient {
public:
	virtual void Func0();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void GetScreenSize(int& width, int& height);
	virtual void Func6();
	virtual void ClientCmd(const char* pszString);
	virtual void GetPlayerInfo(int index, player_info_t* pInfo);
	virtual int GetPlayerForUserID(int);
	virtual void Func10();
	virtual void Func11();
	virtual int GetLocalPlayer(void);
	virtual void Func13();
	virtual float Time();
	virtual void Func15();
	virtual void Func16();
	virtual void Func17();
	virtual void GetViewAngles(Vector& vAngles);
	virtual void SetViewAngles(Vector& vAngles);
	virtual void Func20();
	virtual void Func21();
	virtual void Func22();
	virtual void Func23();
	virtual void Func24();
	virtual void Func25();
	virtual bool IsInGame();
	virtual bool IsConnected();
	virtual void Func28();
	virtual void Func29();
	virtual void Func30();
	virtual void Func31();
	virtual void Func32();
	virtual void Func33();
	virtual void Func34();
	virtual void Func35();
	virtual void Func36();
	virtual void Func37();
	virtual void Func38();
	virtual void Func39();
	virtual void Func40();
	virtual void Func41();
	virtual void Func42();
	virtual void Func43();
	virtual void Func44();
	virtual void Func45();
	virtual void Func46();
	virtual void Func47();
	virtual void Func48();
	virtual void Func49();
	virtual void Func50();
	virtual void Func51();
	virtual void Func52();
	virtual void Func53();
	virtual void Func54();
	virtual void Func55();
	virtual void Func56();
	virtual void Func57();
	virtual void Func58();
	virtual void Func59();
	virtual void Func60();
	virtual void Func61();
	virtual void Func62();
	virtual void Func63();
	virtual void Func64();
	virtual void Func65();
	virtual void Func66();
	virtual void Func67();
	virtual void Func68();
	virtual void Func69();
	virtual void Func70();
	virtual void Func71();
	virtual void Func72();
	virtual void Func73();
	virtual void Func74();
	virtual void Func75();
	virtual void Func76();
	virtual void Func77();
	virtual INetChannelInfo* GetNetChannelInfo(void);
	virtual void Func79();
	virtual void Func80();
	virtual void Func81();
	virtual void Func82();
	virtual void Func83();
	virtual void Func84();
	virtual void Func85();
	virtual void Func86();
	virtual void Func87();
	virtual void Func88();
	virtual void Func89();
	virtual void Func90();
	virtual void Func91();
	virtual bool IsTakingScreenShot();
	virtual void Func93();
	virtual void Func94();
	virtual void Func95();
	virtual void Func96();
	virtual void Func97();
	virtual void Func98();
	virtual void Func99();
	virtual void Func100();
	virtual void Func101();
	virtual void Func102();
	virtual void Func103();
	virtual void Func104();
	virtual void Func105();
	virtual void Func106();
	virtual void Func107();
	virtual void ExecuteClientCmd(const char* pszString);
	virtual void Func109();
	virtual void Func110();
	virtual void Func111();
	virtual void Func112();
	virtual void Func113();
	virtual void Func114();
	virtual void Func115();
	virtual void Func116();
	virtual void Func117();
	virtual void Func118();
	virtual void Func119();
	virtual void Func120();
	virtual void Func121();
}; /* Credits: Valve  (thanks for the dylibs). */