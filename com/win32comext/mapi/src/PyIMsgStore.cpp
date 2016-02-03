/*
 * FILE : C:\pywin32-220\pywin32-220\com\win32comext\mapi\src\PyIMsgStore.cpp
 *
 * This file was automatically generated by :
 * Simplified Wrapper and Interface Generator (SWIG)
 * Version 1.1 (Patch 5)
 *
 * Portions Copyright (c) 1995-1998
 * The University of Utah and The Regents of the University of California.
 * Permission is granted to distribute this file in any manner provided
 * this notice remains intact.
 *
 * Do not make changes to this file--changes will be lost!
 *
 */


#define SWIGCODE
/* Implementation : PYTHON */

#define SWIGPYTHON
#include <string.h>
#include <stdlib.h>
/***********************************************************************
 * $Header$
 * swig_lib/python/python.cfg
 *
 * This file contains coded needed to add variable linking to the
 * Python interpreter.   C variables are added as a new kind of Python
 * datatype.
 *
 * Also contains supporting code for building python under Windows
 * and things like that.
 *
 * $Log$
 * Revision 1.1  2000/03/14 23:34:06  mhammond
 * Needed to modify a standard Swig file to avoid the 'extern "C"' around Python.h (which gets upset when it tries to include whcar.h as part of the new Unicode patches)
 *
 ************************************************************************/

#include "Python.h"

/* Definitions for Windows/Unix exporting */
#if defined(__WIN32__)
#   if defined(_MSC_VER)
#	define SWIGEXPORT(a,b) __declspec(dllexport) a b
#   else
#	if defined(__BORLANDC__)
#	    define SWIGEXPORT(a,b) a _export b
#	else
#	    define SWIGEXPORT(a,b) a b
#	endif
#   endif
#else
#   define SWIGEXPORT(a,b) a b
#endif

#ifdef SWIG_GLOBAL
#ifdef __cplusplus
#define SWIGSTATIC extern "C"
#else
#define SWIGSTATIC
#endif
#endif

#ifndef SWIGSTATIC
#define SWIGSTATIC static
#endif

#ifdef NEED_SWIG_VARLINK

typedef struct {
  char  *name;
  PyObject *(*get_attr)(void);
  int (*set_attr)(PyObject *);
} swig_globalvar;

typedef struct swig_varlinkobject {
  PyObject_HEAD
  swig_globalvar **vars;
  int      nvars;
  int      maxvars;
} swig_varlinkobject;

/* ----------------------------------------------------------------------
   swig_varlink_repr()

   Function for python repr method
   ---------------------------------------------------------------------- */

static PyObject *
swig_varlink_repr(swig_varlinkobject *v)
{
  v = v;
  return PyString_FromString("<Global variables>");
}

/* ---------------------------------------------------------------------
   swig_varlink_print()

   Print out all of the global variable names
   --------------------------------------------------------------------- */

static int
swig_varlink_print(swig_varlinkobject *v, FILE *fp, int flags)
{

  int i = 0;
  flags = flags;
  fprintf(fp,"Global variables { ");
  while (v->vars[i]) {
    fprintf(fp,"%s", v->vars[i]->name);
    i++;
    if (v->vars[i]) fprintf(fp,", ");
  }
  fprintf(fp," }\n");
  return 0;
}

/* --------------------------------------------------------------------
   swig_varlink_getattr

   This function gets the value of a variable and returns it as a
   PyObject.   In our case, we'll be looking at the datatype and
   converting into a number or string
   -------------------------------------------------------------------- */

static PyObject *
swig_varlink_getattr(swig_varlinkobject *v, char *n)
{
  int i = 0;
  char temp[128];

  while (v->vars[i]) {
    if (strcmp(v->vars[i]->name,n) == 0) {
      return (*v->vars[i]->get_attr)();
    }
    i++;
  }
  sprintf(temp,"C global variable %s not found.", n);
  PyErr_SetString(PyExc_NameError,temp);
  return NULL;
}

/* -------------------------------------------------------------------
   swig_varlink_setattr()

   This function sets the value of a variable.
   ------------------------------------------------------------------- */

static int
swig_varlink_setattr(swig_varlinkobject *v, char *n, PyObject *p)
{
  char temp[128];
  int i = 0;
  while (v->vars[i]) {
    if (strcmp(v->vars[i]->name,n) == 0) {
      return (*v->vars[i]->set_attr)(p);
    }
    i++;
  }
  sprintf(temp,"C global variable %s not found.", n);
  PyErr_SetString(PyExc_NameError,temp);
  return 1;
}

statichere PyTypeObject varlinktype = {
/*  PyObject_HEAD_INIT(&PyType_Type)  Note : This doesn't work on some machines */
  PyObject_HEAD_INIT(0)
  0,
  "varlink",                          /* Type name    */
  sizeof(swig_varlinkobject),         /* Basic size   */
  0,                                  /* Itemsize     */
  0,                                  /* Deallocator  */
  (printfunc) swig_varlink_print,     /* Print        */
  (getattrfunc) swig_varlink_getattr, /* get attr     */
  (setattrfunc) swig_varlink_setattr, /* Set attr     */
  0,                                  /* tp_compare   */
  (reprfunc) swig_varlink_repr,       /* tp_repr      */
  0,                                  /* tp_as_number */
  0,                                  /* tp_as_mapping*/
  0,                                  /* tp_hash      */
};

/* Create a variable linking object for use later */

SWIGSTATIC PyObject *
SWIG_newvarlink(void)
{
  swig_varlinkobject *result = 0;
  result = PyMem_NEW(swig_varlinkobject,1);
  varlinktype.ob_type = &PyType_Type;    /* Patch varlinktype into a PyType */
  result->ob_type = &varlinktype;
  /*  _Py_NewReference(result);  Does not seem to be necessary */
  result->nvars = 0;
  result->maxvars = 64;
  result->vars = (swig_globalvar **) malloc(64*sizeof(swig_globalvar *));
  result->vars[0] = 0;
  Py_XINCREF((PyObject *) result);
  return ((PyObject*) result);
}

SWIGSTATIC void
SWIG_addvarlink(PyObject *p, char *name,
	   PyObject *(*get_attr)(void), int (*set_attr)(PyObject *p))
{
  swig_varlinkobject *v;
  v= (swig_varlinkobject *) p;

  if (v->nvars >= v->maxvars -1) {
    v->maxvars = 2*v->maxvars;
    v->vars = (swig_globalvar **) realloc(v->vars,v->maxvars*sizeof(swig_globalvar *));
    if (v->vars == NULL) {
      fprintf(stderr,"SWIG : Fatal error in initializing Python module.\n");
      exit(1);
    }
  }
  v->vars[v->nvars] = (swig_globalvar *) malloc(sizeof(swig_globalvar));
  v->vars[v->nvars]->name = (char *) malloc(strlen(name)+1);
  strcpy(v->vars[v->nvars]->name,name);
  v->vars[v->nvars]->get_attr = get_attr;
  v->vars[v->nvars]->set_attr = set_attr;
  v->nvars++;
  v->vars[v->nvars] = 0;
}

#else
#define SWIG_newvarlink() Py_None
#endif /* SWIG_NEED_VARLINK */
#ifdef NEED_SWIG_PTR
/*****************************************************************************
 * $Header$
 *
 * swigptr.swg
 *
 * This file contains supporting code for the SWIG run-time type checking
 * mechanism.  The following functions are available :
 *
 * SWIG_RegisterMapping(char *origtype, char *newtype, void *(*cast)(void *));
 *
 *      Registers a new type-mapping with the type-checker.  origtype is the
 *      original datatype and newtype is an equivalent type.  cast is optional
 *      pointer to a function to cast pointer values between types (this
 *      is typically used to cast pointers from derived classes to base classes in C++)
 *
 * SWIG_MakePtr(char *buffer, void *ptr, char *typestring);
 *
 *      Makes a pointer string from a pointer and typestring.  The result is returned
 *      in buffer which is assumed to hold enough space for the result.
 *
 * char * SWIG_GetPtr(char *buffer, void **ptr, char *type)
 *
 *      Gets a pointer value from a string.  If there is a type-mismatch, returns
 *      a character string to the received type.  On success, returns NULL.
 *
 *
 * You can remap these functions by making a file called "swigptr.swg" in
 * your the same directory as the interface file you are wrapping.
 *
 * These functions are normally declared static, but this file can be
 * can be used in a multi-module environment by redefining the symbol
 * SWIGSTATIC.
 *****************************************************************************/

#include <stdlib.h>

#ifdef SWIG_GLOBAL
#ifdef __cplusplus
#define SWIGSTATIC extern "C"
#else
#define SWIGSTATIC
#endif
#endif

#ifndef SWIGSTATIC
#define SWIGSTATIC static
#endif


/* SWIG pointer structure */

typedef struct SwigPtrType {
  char               *name;               /* Datatype name                  */
  int                 len;                /* Length (used for optimization) */
  void               *(*cast)(void *);    /* Pointer casting function       */
  struct SwigPtrType *next;               /* Linked list pointer            */
} SwigPtrType;

/* Pointer cache structure */

typedef struct {
  int                 stat;               /* Status (valid) bit             */
  SwigPtrType        *tp;                 /* Pointer to type structure      */
  char                name[256];          /* Given datatype name            */
  char                mapped[256];        /* Equivalent name                */
} SwigCacheType;

/* Some variables  */

static int SwigPtrMax  = 64;           /* Max entries that can be currently held */
                                       /* This value may be adjusted dynamically */
static int SwigPtrN    = 0;            /* Current number of entries              */
static int SwigPtrSort = 0;            /* Status flag indicating sort            */
static int SwigStart[256];             /* Starting positions of types            */

/* Pointer table */
static SwigPtrType *SwigPtrTable = 0;  /* Table containing pointer equivalences  */

/* Cached values */

#define SWIG_CACHESIZE  8
#define SWIG_CACHEMASK  0x7
static SwigCacheType SwigCache[SWIG_CACHESIZE];
static int SwigCacheIndex = 0;
static int SwigLastCache = 0;

/* Sort comparison function */
static int swigsort(const void *data1, const void *data2) {
	SwigPtrType *d1 = (SwigPtrType *) data1;
	SwigPtrType *d2 = (SwigPtrType *) data2;
	return strcmp(d1->name,d2->name);
}

/* Binary Search function */
static int swigcmp(const void *key, const void *data) {
  char *k = (char *) key;
  SwigPtrType *d = (SwigPtrType *) data;
  return strncmp(k,d->name,d->len);
}

/* Register a new datatype with the type-checker */

SWIGSTATIC
void SWIG_RegisterMapping(char *origtype, char *newtype, void *(*cast)(void *)) {

  int i;
  SwigPtrType *t = 0,*t1;

  /* Allocate the pointer table if necessary */

  if (!SwigPtrTable) {
    SwigPtrTable = (SwigPtrType *) malloc(SwigPtrMax*sizeof(SwigPtrType));
    SwigPtrN = 0;
  }
  /* Grow the table */
  if (SwigPtrN >= SwigPtrMax) {
    SwigPtrMax = 2*SwigPtrMax;
    SwigPtrTable = (SwigPtrType *) realloc((char *) SwigPtrTable,SwigPtrMax*sizeof(SwigPtrType));
  }
  for (i = 0; i < SwigPtrN; i++)
    if (strcmp(SwigPtrTable[i].name,origtype) == 0) {
      t = &SwigPtrTable[i];
      break;
    }
  if (!t) {
    t = &SwigPtrTable[SwigPtrN];
    t->name = origtype;
    t->len = strlen(t->name);
    t->cast = 0;
    t->next = 0;
    SwigPtrN++;
  }

  /* Check for existing entry */

  while (t->next) {
    if ((strcmp(t->name,newtype) == 0)) {
      if (cast) t->cast = cast;
      return;
    }
    t = t->next;
  }

  /* Now place entry (in sorted order) */

  t1 = (SwigPtrType *) malloc(sizeof(SwigPtrType));
  t1->name = newtype;
  t1->len = strlen(t1->name);
  t1->cast = cast;
  t1->next = 0;
  t->next = t1;
  SwigPtrSort = 0;
}

/* Make a pointer value string */

SWIGSTATIC
void SWIG_MakePtr(char *_c, const void *_ptr, char *type) {
  static char _hex[16] =
  {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   'a', 'b', 'c', 'd', 'e', 'f'};
  unsigned long _p, _s;
  char _result[20], *_r;    /* Note : a 64-bit hex number = 16 digits */
  _r = _result;
  _p = (unsigned long) _ptr;
  if (_p > 0) {
    while (_p > 0) {
      _s = _p & 0xf;
      *(_r++) = _hex[_s];
      _p = _p >> 4;
    }
    *_r = '_';
    while (_r >= _result)
      *(_c++) = *(_r--);
  } else {
    strcpy (_c, "NULL");
  }
  if (_ptr)
    strcpy (_c, type);
}

/* Define for backwards compatibility */

#define _swig_make_hex   SWIG_MakePtr

/* Function for getting a pointer value */

SWIGSTATIC
char *SWIG_GetPtr(char *_c, void **ptr, char *_t)
{
  unsigned long _p;
  char temp_type[256];
  char *name;
  int  i, len;
  SwigPtrType *sp,*tp;
  SwigCacheType *cache;
  int  start, end;
  _p = 0;

  /* Pointer values must start with leading underscore */
  if (*_c == '_') {
      _c++;
      /* Extract hex value from pointer */
      while (*_c) {
	  if ((*_c >= '0') && (*_c <= '9'))
	    _p = (_p << 4) + (*_c - '0');
	  else if ((*_c >= 'a') && (*_c <= 'f'))
	    _p = (_p << 4) + ((*_c - 'a') + 10);
	  else
	    break;
	  _c++;
      }

      if (_t) {
	if (strcmp(_t,_c)) {
	  if (!SwigPtrSort) {
	    qsort((void *) SwigPtrTable, SwigPtrN, sizeof(SwigPtrType), swigsort);
	    for (i = 0; i < 256; i++) {
	      SwigStart[i] = SwigPtrN;
	    }
	    for (i = SwigPtrN-1; i >= 0; i--) {
	      SwigStart[(int) (SwigPtrTable[i].name[1])] = i;
	    }
	    for (i = 255; i >= 1; i--) {
	      if (SwigStart[i-1] > SwigStart[i])
		SwigStart[i-1] = SwigStart[i];
	    }
	    SwigPtrSort = 1;
	    for (i = 0; i < SWIG_CACHESIZE; i++)
	      SwigCache[i].stat = 0;
	  }

	  /* First check cache for matches.  Uses last cache value as starting point */
	  cache = &SwigCache[SwigLastCache];
	  for (i = 0; i < SWIG_CACHESIZE; i++) {
	    if (cache->stat) {
	      if (strcmp(_t,cache->name) == 0) {
		if (strcmp(_c,cache->mapped) == 0) {
		  cache->stat++;
		  *ptr = (void *) _p;
		  if (cache->tp->cast) *ptr = (*(cache->tp->cast))(*ptr);
		  return (char *) 0;
		}
	      }
	    }
	    SwigLastCache = (SwigLastCache+1) & SWIG_CACHEMASK;
	    if (!SwigLastCache) cache = SwigCache;
	    else cache++;
	  }
	  /* We have a type mismatch.  Will have to look through our type
	     mapping table to figure out whether or not we can accept this datatype */

	  start = SwigStart[(int) _t[1]];
	  end = SwigStart[(int) _t[1]+1];
	  sp = &SwigPtrTable[start];
	  while (start < end) {
	    if (swigcmp(_t,sp) == 0) break;
	    sp++;
	    start++;
	  }
	  if (start >= end) sp = 0;
	  /* Try to find a match for this */
	  if (sp) {
	    while (swigcmp(_t,sp) == 0) {
	      name = sp->name;
	      len = sp->len;
	      tp = sp->next;
	      /* Try to find entry for our given datatype */
	      while(tp) {
		if (tp->len >= 255) {
		  return _c;
		}
		strncpy(temp_type,tp->name,255);
		strncat(temp_type,_t+len,255-tp->len);
		if (strcmp(_c,temp_type) == 0) {

		  strcpy(SwigCache[SwigCacheIndex].mapped,_c);
		  strcpy(SwigCache[SwigCacheIndex].name,_t);
		  SwigCache[SwigCacheIndex].stat = 1;
		  SwigCache[SwigCacheIndex].tp = tp;
		  SwigCacheIndex = SwigCacheIndex & SWIG_CACHEMASK;

		  /* Get pointer value */
		  *ptr = (void *) _p;
		  if (tp->cast) *ptr = (*(tp->cast))(*ptr);
		  return (char *) 0;
		}
		tp = tp->next;
	      }
	      sp++;
	      /* Hmmm. Didn't find it this time */
	    }
	  }
	  /* Didn't find any sort of match for this data.
	     Get the pointer value and return the received type */
	  *ptr = (void *) _p;
	  return _c;
	} else {
	  /* Found a match on the first try.  Return pointer value */
	  *ptr = (void *) _p;
	  return (char *) 0;
	}
      } else {
	/* No type specified.  Good luck */
	*ptr = (void *) _p;
	return (char *) 0;
      }
  } else {
    if (strcmp (_c, "NULL") == 0) {
	*ptr = (void *) 0;
	return (char *) 0;
    }
    *ptr = (void *) 0;
    return _c;
  }
}

/* Compatibility mode */

#define _swig_get_hex  SWIG_GetPtr

#else
#define SWIG_RegisterMapping(a,b,c)
#endif // NEED_SWIG_PTR

static PyObject* t_output_helper(PyObject* target, PyObject* o) {
    PyObject*   o2;
    PyObject*   o3;

    if (!target) {
        target = o;
    } else if (target == Py_None) {
        Py_DECREF(Py_None);
        target = o;
    } else {
        if (!PyTuple_Check(target)) {
            o2 = target;
            target = PyTuple_New(1);
            PyTuple_SetItem(target, 0, o2);
        }
        o3 = PyTuple_New(1);
        PyTuple_SetItem(o3, 0, o);

        o2 = target;
        target = PySequence_Concat(o2, o3);
        Py_DECREF(o2);
        Py_DECREF(o3);
    }
    return target;
}

#include "PyWinTypes.h"
#ifdef NEED_PYWINOBJECTS_H
#include "PyWinObjects.h"
#endif
#include "tchar.h"
typedef BOOL  BOOLAPI;
typedef DWORD  DWORDAPI;

#define PyHANDLE HANDLE // Use a #define so we can undef it later if we need the true defn.
//typedef HANDLE PyHKEY;

#include "PythonCOM.h"

#define SWIG_PYTHONCOM
typedef long  HRESULT_KEEP;
typedef long  HRESULT_KEEP_INFO;

#define MAKE_OUTPUT_INTERFACE(source, target, iid) \
{ \
    PyObject *o; \
    o = PyCom_PyObjectFromIUnknown(*source, iid, FALSE /* bAddRef */); \
    if (target==NULL) \
      target = o; \
	else if (target == Py_None) { /* has been incref'd already!*/ \
		Py_DECREF(Py_None); \
		target = o; \
    } else { \
      if (!PyList_Check(target)) { \
        PyObject *o2 = target; \
        target = PyList_New(0); \
        PyList_Append(target,o2); \
        Py_XDECREF(o2); \
      } \
      PyList_Append(target,o); \
      Py_XDECREF(o); \
    } \
}

#include "pymapiutil.h"


#include "PyIMAPIProp.h"
#include "PyIMsgStore.h"

PyIMsgStore::PyIMsgStore(IUnknown *pDisp) :
	PyIMAPIProp(pDisp)
{
	ob_type = &type;
}

PyIMsgStore::~PyIMsgStore()
{
}

/*static*/ IMsgStore *PyIMsgStore::GetI(PyObject *self)
{
	return (IMsgStore *)PyIUnknown::GetI(self);
}

// @pyswig <o PyIInterface>|OpenEntry|Opens a folder or message and returns an interface object for further access.
PyObject *PyIMsgStore::OpenEntry(PyObject *self, PyObject *args)
{
    HRESULT  _result;
    char * entryString;
	int entryStrLen;
    IID iid;
	IID *pIID;
    PyObject * objIID = 0;
    unsigned long  flags;
    IUnknown * pUnk = NULL;
	ULONG resType;
	PyObject *obEntry;

	IMsgStore *_swig_self;
	if ((_swig_self=GetI(self))==NULL) return NULL;
	// @pyparm string|entryId||The entryID of the object
	// @pyparm <o PyIID>|iid||The IID of the object to return, or None for the default IID
	// @pyparm int|flags||Bitmask of flags that controls how the object is opened.
    if(!PyArg_ParseTuple(args,"OOl:OpenEntry",&obEntry, &objIID,&flags))
        return NULL;
	if (obEntry==Py_None) {
		entryString = NULL;
		entryStrLen = 0;
	} else if PyString_Check(obEntry) {
		entryString = PyString_AsString(obEntry);
		entryStrLen = PyString_Size(obEntry);
	} else {
		PyErr_SetString(PyExc_TypeError, "EntryID must be a string or None");
		return NULL;
	}
	if (objIID==Py_None)
		pIID = NULL;
	else {
		pIID = &iid;
		if (!PyWinObject_AsIID(objIID, pIID))
			return NULL;
	}
	Py_BEGIN_ALLOW_THREADS
     _result = (HRESULT )_swig_self->OpenEntry(entryStrLen,(ENTRYID *)entryString,pIID,flags, &resType, &pUnk);
	Py_END_ALLOW_THREADS
     if (FAILED(_result)) {
           return OleSetOleError(_result);
     }
	 return PyMAPIObject_FromTypedUnknown( resType, pUnk, FALSE /*bAddRef*/);
}


// @pyswig <o PyIID>, string|GetReceiveFolder|Obtains the folder that was established as the destination for incoming messages of a specified message class or the default receive folder for the message store.
PyObject *PyIMsgStore::GetReceiveFolder(PyObject *self, PyObject *args)
{
	HRESULT  _result;
	unsigned long  flags;
	PyObject *obClass;
	TCHAR *szClass;
	TCHAR *sz_explicit_class = NULL;
	ULONG eid_cb;
	LPENTRYID eid_out = NULL;
	PyObject *rc = NULL;

	IMsgStore *_swig_self;
	if ((_swig_self=GetI(self))==NULL) return NULL;
	// @pyparm string|||Message class that is associated with a receive folder. If thid parameter is set to None or an empty string, GetReceiveFolder returns the default receive folder for the message store.
	// @pyparm int|flags||
	if(!PyArg_ParseTuple(args,"Ol:OpenEntry",&obClass, &flags))
		goto done;

	if (!PyWinObject_AsTCHAR(obClass, &szClass, TRUE))
		goto done;

	Py_BEGIN_ALLOW_THREADS
	_result = (HRESULT )_swig_self->GetReceiveFolder(szClass, flags, &eid_cb, &eid_out, &sz_explicit_class);
	Py_END_ALLOW_THREADS
	if (FAILED(_result)) {
		OleSetOleError(_result);
		goto done;
	}

	rc = Py_BuildValue("NN", PyString_FromStringAndSize((char *)eid_out, eid_cb),
	                         PyWinObject_FromTCHAR(sz_explicit_class));
	MAPIFreeBuffer(eid_out);
	MAPIFreeBuffer(sz_explicit_class);
	PyWinObject_FreeTCHAR(szClass);
done:
	return rc;
}


PyObject *PyIMsgStore::CompareEntryIDs(PyObject *self, PyObject *args)
{
	PyObject *rc = NULL;
	HRESULT hr;
	ULONG cb1, cb2;
	ULONG flags=0;
	ULONG ulResult;
	LPENTRYID peid1 = NULL, peid2 = NULL;
	IMsgStore *_swig_self;
	PyObject *obE1, *obE2;
	if ((_swig_self=GetI(self))==NULL) return NULL;
    if(!PyArg_ParseTuple(args,"OO|i:CompareEntryIDs",
		&obE1, // @pyparm string|entryId||The first entry ID to be compared
		&obE2, // @pyparm string|entryId||The second entry ID to be compared
		&flags)) // @pyparm int|flags|0|Reserved - must be zero.
        goto done;

	if (!PyWinObject_AsString(obE1, (char **)&peid1, FALSE, &cb1))
        goto done;

	if (!PyWinObject_AsString(obE2, (char **)&peid2, FALSE, &cb2))
        goto done;

	Py_BEGIN_ALLOW_THREADS
	hr=_swig_self->CompareEntryIDs(cb1, peid1, cb2, peid2, flags, &ulResult);
	Py_END_ALLOW_THREADS
	if (FAILED(hr))
		rc =  OleSetOleError(hr);
	else
		rc = PyInt_FromLong(ulResult);
done:
	PyWinObject_FreeString((char *)peid1);
	PyWinObject_FreeString((char *)peid2);
	return rc;
}

PyObject *PyIMsgStore::AbortSubmit(PyObject *self, PyObject *args)
{
	PyObject *rc = NULL;
	HRESULT hr;
	ULONG cb;
	ULONG flags=0;
	LPENTRYID peid = NULL;
	IMsgStore *_swig_self;
	PyObject *obE;
	if ((_swig_self=GetI(self))==NULL) return NULL;
	if(!PyArg_ParseTuple(args,"O|i:AbortSubmit",
		&obE, // @pyparm string|entryId||The entry ID of the item to be aborted.
		&flags)) // @pyparm int|flags|0|Reserved - must be zero.
		goto done;

	if (!PyWinObject_AsString(obE, (char **)&peid, FALSE, &cb))
		goto done;

	Py_BEGIN_ALLOW_THREADS
	hr=_swig_self->AbortSubmit(cb, peid, flags);
	Py_END_ALLOW_THREADS
	if (FAILED(hr))
		rc =  OleSetOleError(hr);
	else {
		rc = Py_None;
		Py_INCREF(Py_None);
	}
done:
	PyWinObject_FreeString((char *)peid);
	return rc;
}
PyObject *PyIMsgStore::GetReceiveFolderTable(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    HRESULT  _result;
    unsigned long  _arg0;
    IMAPITable ** _arg1;
    IMAPITable * temp;

{
  _arg1 = &temp;
}
	IMsgStore *_swig_self;
	if ((_swig_self=GetI(self))==NULL) return NULL;
    if(!PyArg_ParseTuple(args,"l:GetReceiveFolderTable",&_arg0))
        return NULL;
{
      Py_BEGIN_ALLOW_THREADS
          _result = (HRESULT )_swig_self->GetReceiveFolderTable(_arg0,_arg1);

      Py_END_ALLOW_THREADS
      if (FAILED(_result))  {

#ifdef SWIG_THIS_IID
           return PyCom_BuildPyException(_result, _swig_self,  SWIG_THIS_IID);
#else
           return PyCom_BuildPyException(_result);
#endif
      }
}{
	_resultobj = Py_None;
	Py_INCREF(Py_None);
}
{
	MAKE_OUTPUT_INTERFACE(_arg1, _resultobj, IID_IMAPITable)
}
    return _resultobj;
}

PyObject *PyIMsgStore::GetLastError(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    HRESULT  _result;
    HRESULT  _arg0;
    unsigned long  _arg1;
    MAPIERROR ** _arg2;
    MAPIERROR * temp;

{
	_arg2 = &temp;
}
	IMsgStore *_swig_self;
	if ((_swig_self=GetI(self))==NULL) return NULL;
    if(!PyArg_ParseTuple(args,"ll:GetLastError",&_arg0,&_arg1))
        return NULL;
{
      Py_BEGIN_ALLOW_THREADS
          _result = (HRESULT )_swig_self->GetLastError(_arg0,_arg1,_arg2);

      Py_END_ALLOW_THREADS
      if (FAILED(_result))  {

#ifdef SWIG_THIS_IID
           return PyCom_BuildPyException(_result, _swig_self,  SWIG_THIS_IID);
#else
           return PyCom_BuildPyException(_result);
#endif
      }
}{
	_resultobj = Py_None;
	Py_INCREF(Py_None);
}
{
	PyObject_FromMAPIERROR(*_arg2, TRUE, TRUE);
}
    return _resultobj;
}

static PyMethodDef IMsgStoreMethods[] = {
	 { "AbortSubmit", PyIMsgStore::AbortSubmit, 1 },
	 { "GetLastError", PyIMsgStore::GetLastError, 1 },
	 { "CompareEntryIDs", PyIMsgStore::CompareEntryIDs, 1 },
	 { "GetReceiveFolderTable", PyIMsgStore::GetReceiveFolderTable, 1 },
	 { "GetReceiveFolder", PyIMsgStore::GetReceiveFolder, 1 },
	 { "OpenEntry", PyIMsgStore::OpenEntry, 1 },
	 { NULL, NULL }
};
PyComTypeObject PyIMsgStore::type("PyIMsgStore",	&PyIMAPIProp::type,
	sizeof(PyIMsgStore),
	IMsgStoreMethods,
	GET_PYCOM_CTOR(PyIMsgStore));
#ifndef SWIG_PYTHONCOM
/* This code only valid if non COM SWIG builds */
#ifndef PYCOM_EXPORT
	 PyDict_SetItemString(d,"UNICODE", PyInt_FromLong(
#ifdef UNICODE
	1
#else
	0
#endif
	));
#endif
  PyWinGlobals_Ensure();
  PyDict_SetItemString(d, "error", PyWinExc_ApiError);
#endif SWIG_PYTHONCOM
