#include <sml/sml_list_type.h>
#include <sml/sml_number.h>
#include <stdio.h>

sml_list_type *sml_list_type_init() {
	sml_list_type *list = (sml_list_type *) malloc(sizeof(sml_list_type));
	*list = ( sml_list_type ) {
		.tag = NULL,
		.data.cosem_value = NULL
	};

	return list;
}

sml_list_type *sml_list_type_parse(sml_buffer *buf) {
	sml_list_type *list = sml_list_type_init();

	if (sml_buf_get_next_type(buf) != SML_TYPE_LIST) {
		buf->error = 1;
		goto error;
	}

	if (sml_buf_get_next_length(buf) != 2) {
		buf->error = 1;
		goto error;
	}

	list->tag = sml_u8_parse(buf);
	if (sml_buf_has_errors(buf)) goto error;

	switch (*(list->tag)) {
		case SML_LIST_TYPE_COSEM_VALUE:
			list->data.cosem_value = sml_cosem_value_parse(buf);
			break;
		default:
			fprintf(stderr,"libsml: error: list type choice %02X not yet implemented\n", *(list->tag));
			break;
	}

	return list;

error:
	free(list);
	return 0;
}

void sml_list_type_write(sml_list_type *list, sml_buffer *buf) {

}

void sml_list_type_free(sml_list_type *list) {
	if (list) {
		switch (*(list->tag)) {
			case SML_LIST_TYPE_COSEM_VALUE:
				sml_cosem_value_free(list->data.cosem_value);
				break;
			default:
				break;
		}
		sml_number_free(list->tag);
		free(list);
	}
}
