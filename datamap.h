#ifndef _LIBTF2MOD_DATAMAP_H
#define _LIBTF2MOD_DATAMAP_H


struct datamap;

typedef struct {
	fieldtype_t			fieldType;
	const char			*fieldName;
	int					fieldOffset[ TD_OFFSET_COUNT ]; // 0 == normal, 1 == packed offset
	unsigned short		fieldSize;
	short				flags;
	// the name of the variable in the map/fgd data, or the name of the action
	const char			*externalName;	
	// pointer to the function set for save/restoring of custom data types
	void/*ISaveRestoreOps*/		*pSaveRestoreOps; 
	// for associating function with string names
	uint64_t/*inputfunc_t*/			inputFunc; 
	// For embedding additional datatables inside this one
	struct datamap			*td;
	
	// Stores the actual member variable size in bytes
	int					fieldSizeInBytes;
	
	// FTYPEDESC_OVERRIDE point to first baseclass instance if chains_validated has occurred
	void/*struct typedescription_t*/ *override_field;
	
	// Used to track exclusion of baseclass fields
	int					override_count;
  	
	// Tolerance for field errors for float fields
	float				fieldTolerance;
} typedescription_t;
SIZE_CHECK(typedescription_t, 0x38);

struct datamap {
	typedescription_t *dataDesc;
	int                dataNumFields;
	char const        *dataClassName;
	struct datamap    *baseMap;
	
	uint8_t pad1[0x8];
};
typedef struct datamap datamap_t;
SIZE_CHECK(datamap_t, 0x18);


uintptr_t datamap_offset(datamap_t *map, const char *name);


#endif
