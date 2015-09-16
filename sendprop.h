#ifndef _LIBTF2MOD_SENDPROP_H
#define _LIBTF2MOD_SENDPROP_H


typedef struct {
	uint8_t pad1[0x30];
	
	const char *m_pVarName; // +30
	
	uint8_t pad2[0x8];
	
	void* m_ProxyFn; // +3c
	
	uint8_t pad3[0x4];
	
	void* m_pDataTable; // +44
	int   m_Offset;     // +48
	
	uint8_t pad4[0x4];
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

typedef enum {
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_NUMSendPropTypes,
} SendPropType;

typedef struct {
	union {
		float m_Float;
		long  m_Int;
		char *m_pString;
		void *m_pData;
		float m_Vector[3];
	};
	SendPropType m_Type;
} DVariant;


typedef void (*SendVarProxyFn)(const SendProp*, const void*, const void*,
	DVariant* pOut, int, int);


SendProp* sendprop_find(const char *class_name, const char *name);

uintptr_t sendprop_offset(const char *class_name, const char *name);


#endif
