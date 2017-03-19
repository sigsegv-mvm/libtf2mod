#ifndef _LIBTF2MOD_CONVAR_H
#define _LIBTF2MOD_CONVAR_H


enum {
	FCVAR_NONE                  = 0,
	
	FCVAR_UNREGISTERED          = (1 << 0),
	FCVAR_DEVELOPMENTONLY       = (1 << 1),
	FCVAR_GAMEDLL               = (1 << 2),
	FCVAR_CLIENTDLL             = (1 << 3),
	FCVAR_HIDDEN                = (1 << 4),
	
	FCVAR_PROTECTED             = (1 << 5),
	FCVAR_SPONLY                = (1 << 6),
	FCVAR_ARCHIVE               = (1 << 7),
	FCVAR_NOTIFY                = (1 << 8),
	FCVAR_USERINFO              = (1 << 9),
	FCVAR_CHEAT                 = (1 << 14),
	
	FCVAR_PRINTABLEONLY         = (1 << 10),
	FCVAR_UNLOGGED              = (1 << 11),
	FCVAR_NEVER_AS_STRING       = (1 << 12),
	FCVAR_RELEASE               = (1 << 19),
	
	FCVAR_REPLICATED            = (1 << 13),
	FCVAR_DEMO                  = (1 << 16),
	FCVAR_DONTRECORD            = (1 << 17),
	
	FCVAR_NOT_CONNECTED         = (1 << 22),
	FCVAR_ARCHIVE_XBOX          = (1 << 24),
	FCVAR_SERVER_CAN_EXECUTE    = (1 << 28),
	FCVAR_SERVER_CANNOT_QUERY   = (1 << 29),
	FCVAR_CLIENTCMD_CAN_EXECUTE = (1 << 30),
};


typedef void (*FnChangeCallback_t)(void*, const char*, float);

typedef struct {
	int m_nArgc;
	int m_nArgv0Size;
	char m_pArgSBuffer[512];
	char m_pArgvBuffer[512];
	const char *m_ppArgv[64];
} CCommand;
SIZE_CHECK(CCommand, 0x508);

typedef void (*FnCommandCallback_t)(const CCommand*);
typedef void (*FnCommandCallbackVoid_t)(void);

typedef struct {
	void **vtable;
	
	void *m_pNext;
	
	bool m_bRegistered;
	
	const char *m_pszName;
	const char *m_pszHelpString;
	
	int m_nFlags;
} ConCommandBase;
SIZE_CHECK(ConCommandBase, 0x18);

typedef struct {
	ConCommandBase base;
	void **vtable;
	
	void *m_pParent;
	
	const char *m_pszDefaultValue;
	
	char *m_pszString;
	int m_StringLength;
	
	float m_fValue;
	int m_nValue;
	
	bool m_bHasMin;
	float m_fMinVal;
	bool m_bHasMax;
	float m_fMaxVal;
	
	/* some new stuff, probably competitive related, got added circa Dec 2015 */
	uint8_t pad1[0x14];
	
	FnChangeCallback_t m_fnChangeCallback;
} ConVar;
SIZE_CHECK(ConVar, 0x5c);

typedef struct {
	ConCommandBase base;
	
	uint8_t pad1[0xc];
} ConCommand;
SIZE_CHECK(ConCommand, 0x24);


static inline const char **CCommand_ArgV(const CCommand* this)
{
	if (this->m_nArgc == 0) {
		return NULL;
	} else {
		return (const char **)this->m_ppArgv;
	}
}

static inline const char *CCommand_ArgS(const CCommand* this)
{
	if (this->m_nArgv0Size == 0) {
		return "";
	} else {
		return &this->m_pArgSBuffer[this->m_nArgv0Size];
	}
}

static inline const char *CCommand_GetCommandString(const CCommand* this)
{
	if (this->m_nArgc == 0) {
		return "";
	} else {
		return this->m_pArgSBuffer;
	}
}

static inline const char *CCommand_Arg(const CCommand* this, int nIndex)
{
	if (nIndex < 0 || nIndex >= this->m_nArgc) {
		return "";
	}
	
	return this->m_ppArgv[nIndex];
}


static inline float ConVar_GetFloat(const ConVar* this)
{
	ConVar* parent = (ConVar*)this->m_pParent;
	return parent->m_fValue;
}

static inline int ConVar_GetInt(const ConVar* this)
{
	ConVar* parent = (ConVar*)this->m_pParent;
	return parent->m_nValue;
}

static inline char const* ConVar_GetString(const ConVar* this)
{
	if ((this->base.m_nFlags & FCVAR_NEVER_AS_STRING) != 0) {
		return "FCVAR_NEVER_AS_STRING";
	}
	
	ConVar* parent = (ConVar*)this->m_pParent;
	if (parent->m_pszString != NULL) {
		return parent->m_pszString;
	} else {
		return "";
	}
}


void convar_init(void);


#endif
