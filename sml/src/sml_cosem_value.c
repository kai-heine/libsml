#include <sml/sml_cosem_value.h>
#include <sml/sml_number.h>
#include <stdio.h>

sml_cosem_value *sml_cosem_value_init() {
	sml_cosem_value *cosem_value = (sml_cosem_value *) malloc(sizeof(sml_cosem_value));
	*cosem_value = ( sml_cosem_value ) {
		.tag = NULL,
		.data.scaler_unit = NULL
	};

	return cosem_value;
}

sml_cosem_value *sml_cosem_value_parse(sml_buffer *buf) {
	sml_cosem_value *cosem_value = sml_cosem_value_init();

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

void sml_cosem_value_write(const sml_cosem_value *cosem_value, sml_buffer *buf) {
	sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 2);
	sml_u8_write(cosem_value->tag, buf);

	switch (*(cosem_value->tag)) {
		case SML_COSEM_VALUE_TYPE_SCALER_UNIT:
			sml_cosem_scaler_unit_type_write(cosem_value->data.scaler_unit, buf);
			break;
		default:
			fprintf(stderr,"libsml: error: cosem_value choice %02X not yet implemented\n", *(cosem_value->tag));
			break;
	}
}

void sml_cosem_value_free(sml_cosem_value *cosem_value) {
	if (cosem_value) {
		switch (*(cosem_value->tag)) {
			case SML_COSEM_VALUE_TYPE_SCALER_UNIT:
				sml_cosem_scaler_unit_type_free(cosem_value->data.scaler_unit);
				break;
			default:
				break;
		}
		sml_number_free(cosem_value->tag);
		free(cosem_value);
	}
}


sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_init() {
	sml_cosem_scaler_unit_type *scaler_unit = (sml_cosem_scaler_unit_type *) malloc(sizeof(sml_cosem_scaler_unit_type));
	*scaler_unit = ( sml_cosem_scaler_unit_type ) {
		.scaler = NULL,
		.unit = NULL
	};

	return scaler_unit;
}

sml_cosem_scaler_unit_type *sml_cosem_scaler_unit_type_parse(sml_buffer *buf) {
	sml_cosem_scaler_unit_type *scaler_unit = sml_cosem_scaler_unit_type_init();

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

void sml_cosem_scaler_unit_type_write(const sml_cosem_scaler_unit_type *cosem_scaler_unit, sml_buffer *buf) {
	sml_buf_set_type_and_length(buf, SML_TYPE_LIST, 2);
	sml_i8_write(cosem_scaler_unit->scaler, buf);
	sml_u8_write(cosem_scaler_unit->unit, buf);
}

void sml_cosem_scaler_unit_type_free(sml_cosem_scaler_unit_type *cosem_scaler_unit) {
	if (cosem_scaler_unit) {
		sml_number_free(cosem_scaler_unit->scaler);
		sml_number_free(cosem_scaler_unit->unit);
		free(cosem_scaler_unit);
	}
}
