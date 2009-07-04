
#ifndef SC_OBJECT_H
#define SC_OBJECT_H

#include <sc.h>
#include <sc_containers.h>

typedef void        (*sc_object_method_t) (void);

typedef struct sc_object_entry
{
  sc_object_method_t  key;
  sc_object_method_t  oinmi;
  void               *odata;
}
sc_object_entry_t;

typedef struct sc_object
{
  int                 num_refs; /* reference count */
  sc_hash_t          *table;    /* contains sc_object_entry_t elements */
  sc_array_t          delegates;
}
sc_object_t;

/* *INDENT-OFF* HORRIBLE indent bug */
typedef struct sc_object_recursion_context
{
  sc_hash_t          *visited;
  sc_object_method_t  lookup;
  bool                (*callfn) (sc_object_t *, sc_object_method_t, void *);
  void               *user_data;
}
sc_object_recursion_context_t;
/* *INDENT-ON* */

extern const char  *sc_object_type;

/* reference counting */
void                sc_object_ref (sc_object_t * o);
void                sc_object_unref (sc_object_t * o);

/** Look up a method recursively for all delegates and run a callback on it.
 * Breaks recursion early on the first callback returning true.
 * Ignores objects that have already been called.
 * \param [in,out] o    The object to start looking.
 * \param [in] rc       Recursion context with visited == NULL.
 * \param [in] lookup   Can contain a method to look up, or NULL.
 * \param [in] callfn   If not NULL will be called on successful lookup.
 * \param [in] user_data    Is passed as third parameter to callfn.
 * \return              True if any callfn returned true, false otherwise.
 */
bool                sc_object_recursion (sc_object_t * o,
                                         sc_object_recursion_context_t * rc);

/** Register the implementation of an interface method for an object.
 * If the method is already registered it is replaced.
 * \param[in] o     object instance
 * \param[in] ifm   interface method
 * \param[in] oinmi object instance method implementation
 * \return          true if the method did not exist and was added.
 */
bool                sc_object_method_register (sc_object_t * o,
                                               sc_object_method_t ifm,
                                               sc_object_method_t oinmi);

/** Unregister the implementation of an interface method for an object.
 * The method is required to exist.
 * \param[in] o     object instance
 * \param[in] ifm   interface method
 */
void                sc_object_method_unregister (sc_object_t * o,
                                                 sc_object_method_t ifm);
sc_object_method_t  sc_object_method_lookup (sc_object_t * o,
                                             sc_object_method_t ifm);

/* handle delegates */
void                sc_object_delegate_push (sc_object_t * o,
                                             sc_object_t * d);
void                sc_object_delegate_pop (sc_object_t * o);
void                sc_object_delegate_pop_all (sc_object_t * o);
sc_object_method_t  sc_object_delegate_lookup (sc_object_t * o,
                                               sc_object_method_t ifm);

/* handle types */
bool                sc_object_is_type (sc_object_t * o, const char *type);

/* construction */
sc_object_t        *sc_object_alloc (void);
sc_object_t        *sc_object_klass_new (void);
sc_object_t        *sc_object_new_from_klass (sc_object_t * d);

/* handle object data */
void               *sc_object_get_data (sc_object_t * o,
                                        sc_object_method_t ifm, size_t s);

/* virtual method prototypes */
const char         *sc_object_get_type (sc_object_t * o);
void                sc_object_initialize (sc_object_t * o);
void                sc_object_finalize (sc_object_t * o);
void                sc_object_write (sc_object_t * o, FILE * out);

#endif /* !SC_OBJECT_H */