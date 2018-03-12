#ifndef SML_COSEM_VALUE_H_
#define SML_COSEM_VALUE_H_

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	i8 *scaler;
	u8 *unit;
} sml_cosem_scaler_unit_type;

typedef struct {
	u8 *tag;
	union {
		sml_cosem_scaler_unit_type *scaler_unit;
	} data;
} sml_cosem_value;

#define SML_COSEM_VALUE_TYPE_SCALER_UNIT	0x01

sml_cosem_value *sml_cosem_value_init();
sml_cosem_value *sml_cosem_value_parse(sml_buffer *buf);
void sml_cosem_value_write(const sml_cosem_value *cosem_value, sml_buffer *buf);
void sml_cosem_value_free(sml_cosem_value *cosem_value);

sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_init();
sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_parse(sml_buffer *buf);
void sml_cosem_scaler_unit_type_write(const sml_cosem_scaler_unit_type *cosem_scaler_unit, sml_buffer *buf);
void sml_cosem_scaler_unit_type_free(sml_cosem_scaler_unit_type *cosem_scaler_unit);

#ifdef __cplusplus
}
#endif

#endif /* SML_COSEM_VALUE_H_ */
