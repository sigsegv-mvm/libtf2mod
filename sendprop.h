#ifndef _LIBTF2MOD_SENDPROP_H
#define _LIBTF2MOD_SENDPROP_H


typedef struct {
	uint8_t pad1[0x30];
	
	const char *m_pVarName; // +30
	
	uint8_t pad2[0x10];
	
	void* m_pDataTable; // +44
	int   m_Offset;     // +48
	
	uint8_t pad3[0x4];
} SendProp;
SIZE_CHECK(SendProp, 0x50);

typedef struct {
	SendProp* m_pProps; // +00
	int m_nProps;       // +04
	
	uint8_t pad1[0xc];
} SendTable;
SIZE_CHECK(SendTable, 0x14);

typedef struct {
	uint8_t pad1[0x4];
	
	SendTable* m_pTable; // +04
	
	uint8_t pad2[0xc];
} ServerClass;
SIZE_CHECK(ServerClass, 0x14);


uintptr_t sendprop_offset(const char *sv_class, const char *name);


#endif
