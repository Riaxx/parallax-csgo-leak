class IGameConsole {
public:
	virtual void	Activate() = 0;

	virtual void	Initialize() = 0;

	// hides the console
	virtual void	Hide() = 0;

	// clears the console
	virtual void	Clear() = 0;

	// return true if the console has focus
	virtual bool	IsConsoleVisible() = 0;

	// prints a message to the console
	virtual void	Printf(const char *format, ...) = 0;

	// printes a debug message to the console
	virtual void	DPrintf(const char *format, ...) = 0;

	// printes a debug message to the console
	virtual void	ColorPrintf(Color& clr, const char *format, ...) = 0;

	virtual void	SetParent(VPANEL parent) = 0;
};