#include "all.h"


static int SendTable_GetNumProps(SendTable* this)
{
	return this->m_nProps;
}

static SendProp* SendTable_GetProp(SendTable* this, int i)
{
	assert(i >= 0 && i < this->m_nProps);
	return this->m_pProps + i;
}


static const char *SendProp_GetName(SendProp* this)
{
	return this->m_pVarName;
}

static SendTable *SendProp_GetDataTable(SendProp* this)
{
	return (SendTable *)this->m_pDataTable;
}

static int SendProp_GetOffset(SendProp* this)
{
	return this->m_Offset;
}


static SendProp *_sendprop_offset_internal(SendTable* table, const char *name)
{
	int count = SendTable_GetNumProps(table);
	for (int i = 0; i < count; ++i) {
		SendProp* prop = SendTable_GetProp(table, i);
		
		if (strcmp(SendProp_GetName(prop), name) == 0) {
			return prop;
		}
		
		if (SendProp_GetDataTable(prop) != NULL) {
			if ((prop = _sendprop_offset_internal(SendProp_GetDataTable(prop),
				name)) != NULL) {
				return prop;
			}
		}
	}
	
	return NULL;
}

uintptr_t sendprop_offset(const char *class_name, const char *name)
{
	ServerClass *sv_class = SV_FindServerClass(class_name);
	if (sv_class == NULL) {
		pr_warn("%s: SV_FindServerClass('%s') returned NULL\n",
			__func__, class_name);
		return 0;
	}
	
	SendProp* prop = _sendprop_offset_internal(sv_class->m_pTable, name);
	if (prop == NULL) {
		pr_warn("%s: could not find '%s' in '%s'",
			__func__, name, class_name);
		return 0;
	}
	
	return SendProp_GetOffset(prop);
}
