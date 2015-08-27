#include "all.h"


DETOUR(debug_usermessage);
/*  */


static unknown_t (*trampoline_UserMessageBegin)(IRecipientFilter*, char const*);
static unknown_t (*trampoline_MessageEnd)(void);
static unknown_t (*trampoline_MessageWriteAngle)(float);
static unknown_t (*trampoline_MessageWriteAngles)(QAngle const*);
static unknown_t (*trampoline_MessageWriteBits)(void const*, int);
static unknown_t (*trampoline_MessageWriteBool)(bool);
static unknown_t (*trampoline_MessageWriteByte)(int);
static unknown_t (*trampoline_MessageWriteChar)(int);
static unknown_t (*trampoline_MessageWriteCoord)(float);
static unknown_t (*trampoline_MessageWriteEHandle)(CBaseEntity*);
static unknown_t (*trampoline_MessageWriteEntity)(int);
static unknown_t (*trampoline_MessageWriteFloat)(float);
static unknown_t (*trampoline_MessageWriteLong)(int);
static unknown_t (*trampoline_MessageWriteSBitLong)(int, int);
static unknown_t (*trampoline_MessageWriteShort)(int);
static unknown_t (*trampoline_MessageWriteString)(char const*);
static unknown_t (*trampoline_MessageWriteUBitLong)(unsigned int, int);
static unknown_t (*trampoline_MessageWriteVec3Coord)(Vector const*);
static unknown_t (*trampoline_MessageWriteVec3Normal)(Vector const*);
static unknown_t (*trampoline_MessageWriteWord)(int);


static unknown_t detour_UserMessageBegin(IRecipientFilter* filter, char const* name)
{
	pr_debug("UserMessageBegin(\"%s\")\n", name);
	return trampoline_UserMessageBegin(filter, name);
}

static unknown_t detour_MessageEnd(void)
{
	pr_debug("MessageEnd()\n");
	return trampoline_MessageEnd();
}

static unknown_t detour_MessageWriteAngle(float angle)
{
	pr_debug("MessageWriteAngle(%f)\n", angle);
	return trampoline_MessageWriteAngle(angle);
}

static unknown_t detour_MessageWriteAngles(QAngle const* angles)
{
	pr_debug("MessageWriteAngles(TODO)\n");
	return trampoline_MessageWriteAngles(angles);
}

static unknown_t detour_MessageWriteBits(void const* bits, int len)
{
	pr_debug("MessageWriteBits(TODO)\n");
	return trampoline_MessageWriteBits(bits, len);
}

static unknown_t detour_MessageWriteBool(bool v)
{
	pr_debug("MessageWriteBool(%s)\n", (v ? "true" : "false"));
	return trampoline_MessageWriteBool(v);
}

static unknown_t detour_MessageWriteByte(int v)
{
	pr_debug("MessageWriteByte(%02x)\n", v);
	return trampoline_MessageWriteByte(v);
}

static unknown_t detour_MessageWriteChar(int v)
{
	pr_debug("MessageWriteChar(%02x)\n", v);
	return trampoline_MessageWriteChar(v);
}

static unknown_t detour_MessageWriteCoord(float v)
{
	pr_debug("MessageWriteCoord(%f)\n", v);
	return trampoline_MessageWriteCoord(v);
}

static unknown_t detour_MessageWriteEHandle(CBaseEntity* e)
{
	pr_debug("MessageWriteEHandle(%08x)\n", (uintptr_t)e);
	return trampoline_MessageWriteEHandle(e);
}

static unknown_t detour_MessageWriteEntity(int e)
{
	pr_debug("MessageWriteEntity(%d)\n", e);
	return trampoline_MessageWriteEntity(e);
}

static unknown_t detour_MessageWriteFloat(float v)
{
	pr_debug("MessageWriteFloat(%f)\n", v);
	return trampoline_MessageWriteFloat(v);
}

static unknown_t detour_MessageWriteLong(int v)
{
	pr_debug("MessageWriteLong(%08x)\n", v);
	return trampoline_MessageWriteLong(v);
}

static unknown_t detour_MessageWriteSBitLong(int v, int len)
{
	pr_debug("MessageWriteSBitLong(%d %08x)\n", len, v);
	return trampoline_MessageWriteSBitLong(v, len);
}

static unknown_t detour_MessageWriteShort(int v)
{
	pr_debug("MessageWriteShort(%04x)\n", v);
	return trampoline_MessageWriteShort(v);
}

static unknown_t detour_MessageWriteString(char const* s)
{
	pr_debug("MessageWriteString(\"%s\")\n", s);
	return trampoline_MessageWriteString(s);
}

static unknown_t detour_MessageWriteUBitLong(unsigned int v, int len)
{
	pr_debug("MessageWriteUBitLong(%d %08x)\n", len, v);
	return trampoline_MessageWriteUBitLong(v, len);
}

static unknown_t detour_MessageWriteVec3Coord(Vector const* vec)
{
	pr_debug("MessageWriteVec3Coord(TODO)\n");
	return trampoline_MessageWriteVec3Coord(vec);
}

static unknown_t detour_MessageWriteVec3Normal(Vector const* vec)
{
	pr_debug("MessageWriteVec3Normal(TODO)\n");
	return trampoline_MessageWriteVec3Normal(vec);
}

static unknown_t detour_MessageWriteWord(int v)
{
	pr_debug("MessageWriteWord(%04x)\n", v);
	return trampoline_MessageWriteWord(v);
}


DETOUR_SETUP
{
	DETOUR_CREATE(UserMessageBegin);
	DETOUR_CREATE(MessageEnd);
	DETOUR_CREATE(MessageWriteAngle);
	DETOUR_CREATE(MessageWriteAngles);
	DETOUR_CREATE(MessageWriteBits);
	DETOUR_CREATE(MessageWriteBool);
	DETOUR_CREATE(MessageWriteByte);
	DETOUR_CREATE(MessageWriteChar);
	DETOUR_CREATE(MessageWriteCoord);
	DETOUR_CREATE(MessageWriteEHandle);
	DETOUR_CREATE(MessageWriteEntity);
	DETOUR_CREATE(MessageWriteFloat);
	DETOUR_CREATE(MessageWriteLong);
	DETOUR_CREATE(MessageWriteSBitLong);
	DETOUR_CREATE(MessageWriteShort);
	DETOUR_CREATE(MessageWriteString);
	DETOUR_CREATE(MessageWriteUBitLong);
	DETOUR_CREATE(MessageWriteVec3Coord);
	DETOUR_CREATE(MessageWriteVec3Normal);
	DETOUR_CREATE(MessageWriteWord);
}
