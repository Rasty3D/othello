static const char *name = "maxchips";

extern "C" const char *getName()
{
	return name;
}

extern "C" bool setParam(const char *name, const char *value)
{
	// No parameters
	return false;
}

extern "C" bool move(const unsigned char *board, int turn, char *move)
{
	// TODO
	move[0] = '4';
	move[1] = 'f';
	return true;
}
