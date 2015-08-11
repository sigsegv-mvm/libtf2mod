#include "all.h"


uintptr_t datamap_offset(datamap_t *map, const char *name)
{
	//pr_debug("%s: name '%s' map %08x\n", __func__, name, map);
	while (map != NULL) {
		//mem_dump(map->dataDesc, sizeof(typedescription_t) * map->dataNumFields, false);
		//pr_debug("%s:  map->dataNumFields %d\n", __func__, map->dataNumFields);
		for (int i = 0; i < map->dataNumFields; ++i) {
			//pr_debug("%s:   i %d\n", __func__, i);
			//pr_debug("%s:   map->dataDesc[i].fieldName %08x\n", __func__, map->dataDesc[i].fieldName);
			if (map->dataDesc[i].fieldName == NULL) {
				continue;
			}
			//pr_debug("%s:   map->dataDesc[i].fieldName '%s'\n", __func__, map->dataDesc[i].fieldName);
			if (strcmp(name, map->dataDesc[i].fieldName) == 0) {
				return map->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];
			}
			//pr_debug("%s:   map->dataDesc[i].td %08x\n", __func__, map->dataDesc[i].td);
			if (map->dataDesc[i].td != NULL) {
				uintptr_t offset;
				if ((offset = datamap_offset(map->dataDesc[i].td,
					name)) != 0) {
					//pr_debug("%s:    return %04x\n", __func__, offset);
					return offset;
				}
				//pr_debug("%s:    nope\n", __func__);
			}
		}
		
		//pr_debug("%s: basemap %08x\n", __func__, map->baseMap);
		map = map->baseMap;
	}
	
	//pr_debug("%s: return 0\n", __func__);
	return 0;
}
