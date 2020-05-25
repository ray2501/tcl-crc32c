/*
 * Tcl bindings for crc32c library.
 */

#define NS "crc32c"
#include <crc32c/crc32c.h>

/*
 * For C++ compilers, use extern "C"
 */

#ifdef __cplusplus

extern "C" {
#endif

#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int CRC32C_EXTEND(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv);
static int CRC32C_VALUE(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv);

/*
 * Only the _Init function is exported.
 */

extern DLLEXPORT int	Crc32c_Init(Tcl_Interp * interp);

/*
 * end block for C++
 */

#ifdef __cplusplus
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * Crc_Init --
 *
 *	Initialize the new package.  The string "Crc32c" in the
 *	function name must match the PACKAGE declaration at the top of
 *	configure.ac.
 *
 * Results:
 *	A standard Tcl result
 *
 * Side effects:
 *	The Crc32c package is created.
 *
 *----------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
DLLEXPORT int
Crc32c_Init(Tcl_Interp *interp)
{
    Tcl_Namespace *nsPtr; /* pointer to hold our own new namespace */

    /*
     * This may work with 8.0, but we are using strictly stubs here,
     * which requires 8.1.
     */
    if (Tcl_InitStubs(interp, "8.5", 0) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }

    /*
     * Create the namespace named crc32c.
     * crc32c command is too short, we need a namespace.
     */
    nsPtr = Tcl_CreateNamespace(interp, NS, NULL, NULL);
    if (nsPtr == NULL) {
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, NS "::extend", 
        (Tcl_ObjCmdProc *) CRC32C_EXTEND,
        (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

    Tcl_CreateObjCommand(interp, NS "::value", 
        (Tcl_ObjCmdProc *) CRC32C_VALUE,
        (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

    return TCL_OK;
}

static int CRC32C_EXTEND(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv){
  const uint8_t *str = NULL;
  int length = 0;
  uint32_t value = 0;
  uint32_t result = 0;
  char resValue[16];
    
  if( objc != 3 ){
    Tcl_WrongNumArgs(interp, 1, objv, "value data");
    return TCL_ERROR;
  }

  if(Tcl_GetIntFromObj(interp, objv[1], (int *)&value) != TCL_OK) {
    return TCL_ERROR;
  }

  str = (const uint8_t *) Tcl_GetStringFromObj(objv[2], &length);
  if( !str || length < 1) {
    return TCL_ERROR;
  }

  /*
   * Here needs to return a unsigned int value, print to a string and return
   */
  result =  crc32c_extend(value, str, length);
  sprintf(resValue, "%u", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj( resValue, -1));
  return TCL_OK;
}

static int CRC32C_VALUE(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv){
  const uint8_t *str = NULL;
  int length = 0;
  uint32_t result = 0;
  char resValue[16];
    
  if( objc != 2 ){
    Tcl_WrongNumArgs(interp, 1, objv, "data");
    return TCL_ERROR;
  } 
  
  str = (const uint8_t *) Tcl_GetStringFromObj(objv[1], &length);
  if( !str || length < 1) {
    return TCL_ERROR;
  } 
  
  /*
   * Here needs to return a unsigned int value, print to a string and return
   */
  result = crc32c_value(str, length);
  sprintf(resValue, "%u", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj( resValue, -1));
  return TCL_OK;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
