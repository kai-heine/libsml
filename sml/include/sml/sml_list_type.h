#ifndef SML_LIST_TYPE_H_
#define SML_LIST_TYPE_H_

#include "sml_shared.h"
#include "sml_cosem_value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	u8 *tag;
	union {
		// smlTime
		// smlTimestampedValue
		sml_cosem_value *cosem_value;
	} data;
} sml_list_type;

#define SML_LIST_TYPE_COSEM_VALUE	0x03

sml_list_type *sml_list_type_init();
sml_list_type *sml_list_type_parse(sml_buffer *buf);
void sml_list_type_write(sml_list_type *list, sml_buffer *buf);
void sml_list_type_free(sml_list_type *list);

#ifdef __cplusplus
}
#endif

#endif /* SML_LIST_TYPE_H_ */