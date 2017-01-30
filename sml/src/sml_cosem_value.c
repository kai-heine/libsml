#include <sml/sml_cosem_value.h>
#include <sml/sml_number.h>
#include <stdio.h>

sml_cosem_value *sml_cosem_value_init() {
	return 0;
}

sml_cosem_value *sml_cosem_value_parse(sml_buffer *buf) {
	sml_cosem_value *cosem_value = (sml_cosem_value *) malloc(sizeof(sml_cosem_value));
	*cosem_value = ( sml_cosem_value ) {
		.tag = NULL,
		.data.scaler_unit = NULL
	};

	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}

	if (sml_buf_get_next_length(buf) != 2) {
		buf->error = 1;
		goto error;
	}

	cosem_value->tag = sml_u8_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;

	switch (*(cosem_value->tag)) {
		case SML_COSEM_VALUE_TYPE_SCALER_UNIT:
			cosem_value->data.scaler_unit = sml_cosem_scaler_unit_type_parse(buf);
			break;
		default:
			fprintf(stderr,"libsml: error: cosem_value choice %02X not yet implemented\n", *(cosem_value->tag));
			break;
	}

	return cosem_value;

error:
	free(cosem_value);
	return 0;
}

void sml_cosem_value_write(sml_cosem_value *cosem_value, sml_buffer *buf) {

}

void sml_cosem_value_free(sml_cosem_value *cosem_value) {

}


sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_init() {
	return 0;
}

sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_parse(sml_buffer *buf) {
	sml_cosem_scaler_unit_type *scaler_unit = (sml_cosem_scaler_unit_type *) malloc(sizeof(sml_cosem_scaler_unit_type));
	*scaler_unit = ( sml_cosem_scaler_unit_type ) {
		.scaler = NULL,
		.unit = NULL
	};

	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}

	if (sml_buf_get_next_length(buf) != 2) {
		buf->error = 1;
		goto error;
	}

	scaler_unit->scaler = sml_i8_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;

	scaler_unit->unit = sml_u8_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;

	return scaler_unit;

error:
	free(scaler_unit);
	return 0;
}

void sml_cosem_scaler_unit_type_write(sml_cosem_scaler_unit_type *cosem_scaler_unit, sml_buffer *buf) {

}

void sml_cosem_scaler_unit_type_free(sml_cosem_scaler_unit_type *cosem_scaler_unit) {

}
