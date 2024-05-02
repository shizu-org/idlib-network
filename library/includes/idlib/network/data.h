#if !defined(IDLIB_DATA_H_INCLUDED)
#define IDLIB_DATA_H_INCLUDED

// The "void" value can be used as values in mappings.
// The "void" value can be used as list elements.
#define IDLIB_DATA_KIND_VOID (0)
#define IDLIB_DATA_KIND_MAP (1)
#define IDLIB_DATA_KIND_LIST (2)
#define IDLIB_DATA_KIND_STRING (3)
#define IDLIB_DATA_KIND_NUMBER (4)

typedef struct idlib_data_context_impl idlib_data_context_impl;

typedef struct idlib_data_impl idlib_data_impl;

struct idlib_data_context_impl {
  idlib_data_impl* objects;
};

struct idlib_data_impl {
  uint8_t kind;
};

// You can create multiple contexts.
// Elements belonging to one context must not
// The API is not(!) thread safe.
// You can create from two contexts a new context that now owns all the data.
// The two input contexts are destroyed.

idlib_status
idlib_data_create_context
  (
    idlib_context** context
  );

idlib_status
idlib_data_destroy_context
  (
    idlib_context* context
  );

idlib_status
idlib_data_create_map
  (
    idlib_context* context,
    idlib_data** data
  );

idlib_status
idlib_data_create_list
  (
    idlib_context* context,
    idlib_data** data
  );

idlib_status
idlib_data_create_string
  (
    idlib_context* context,
    idlib_data **data,
    char const* p,
    size_t n
  );

idlib_status
idlib_data_create_boolean
  (
    idlib_context* context,
    idlib_data** data,
    bool value
  );

// extension function
idlib_status
idlib_data_create_number_int8
  (
    idlib_context* context,
    idlib_data** data,
    int8_t value
  );

// extension function
idlib_status
idlib_data_create_number_int16
  (
    idlib_context* context,
    idlib_data** data,
    int16_t value
  );

idlib_status
idlib_data_create_number_int32
  (
    idlib_context* context,
    idlib_data** data,
    int32_t value
  );

idlib_status
idlib_data_create_number_int64
  (
    idlib_context* context,
    idlib_data** data,
    int64_t value
  );

idlib_status
idlib_data_create_number_uint8
  (
    idlib_context* context,
    idlib_data** data,
    uint8_t value
  );

idlib_status
idlib_data_create_number_uint6
  (
    idlib_context* context,
    idlib_data** data,
    uint16_t value
  );

idlib_status
idlib_data_create_number_uint32
  (
    idlib_context* context,
    idlib_data** data,
    uint32_t value
  );

idlib_status
idlib_data_create_number_uint64
  (
    idlib_context* context,
    idlib_data** data,
    uint64_t value
  );

idlib_status
idlib_data_create_number_float
  (
    idlib_context* context,
    idlib_data** data,
    float value
  );

idlib_status
idlib_data_create_number_double
  (
    idlib_context* context,
    idlib_data** data,
    double value
  );

#endif // IDLIB_DATA_H_INCLUDED
