#pragma once


class Misc
{

public:
	void isRdy();

private:

	const char *setStrRight(std::string txt, unsigned int value);



};

extern int promene;

extern std::unique_ptr<Misc> misc;

//bool applyProxies();

using IsRdyFn = void(__cdecl*)();
extern IsRdyFn IsRdy;