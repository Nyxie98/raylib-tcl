#include <tcl.h>
#include <raylib.h>

static int
InitWindowCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    const char* title;
    int width, height;

    if (objc != 4) {
        Tcl_WrongNumArgs(interp, 1, objv, "a b");
        return TCL_ERROR;
    }
    
    title = Tcl_GetString(objv[3]);
    if (Tcl_GetIntFromObj(interp, objv[1], &width) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[2], &height) != TCL_OK) {
        return TCL_ERROR;
    }

    InitWindow(width, height, title);
    
    return TCL_OK;
}

static int
SetTargetFPSCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    int fps;
    
    if (objc != 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "fps");
        return TCL_ERROR;
    }

    if (Tcl_GetIntFromObj(interp, objv[1], &fps) != TCL_OK) {
        return TCL_ERROR;
    }

    SetTargetFPS(fps);

    return TCL_OK;
}

static int
WindowShouldCloseCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    bool shouldClose = WindowShouldClose();

    Tcl_SetObjResult(interp, Tcl_NewBooleanObj(shouldClose));
    return TCL_OK;
}

// Drawing
static int
BeginDrawingCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    BeginDrawing();
    return TCL_OK;
}

static int
EndDrawingCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    EndDrawing();
    return TCL_OK;
}

static int
ClearBackgroundCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    int col_len, clist[4];
    Tcl_Obj **col;

    if (objc != 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "r g b a");
        return TCL_ERROR;
    }

    if (Tcl_ListObjGetElements(interp, objv[1], &col_len, &col) != TCL_OK) {
        return TCL_ERROR;
    }

    for (int i = 0; i < 4; i++) {
        Tcl_GetIntFromObj(interp, col[i], &clist[i]);
    }

    ClearBackground((Color){clist[0],clist[1],clist[2],clist[3]});
    return TCL_OK;
}

static int
CloseWindowCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    CloseWindow();
    return TCL_OK;
}

static int
DrawTextCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    const char* title;
    int x, y, fs, col_len, clist[4];
    Tcl_Obj **col;

    if (objc != 6) {
        Tcl_WrongNumArgs(interp, 1, objv, "text x y size color");
        return TCL_ERROR;
    }

    if (Tcl_ListObjGetElements(interp, objv[5], &col_len, &col) != TCL_OK) {
        return TCL_ERROR;
    }
    
    title = Tcl_GetString(objv[1]);
    if (Tcl_GetIntFromObj(interp, objv[2], &x) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[3], &y) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[4], &fs) != TCL_OK) {
        return TCL_ERROR;
    }

    for (int i = 0; i < 4; i++) {
        Tcl_GetIntFromObj(interp, col[i], &clist[i]);
    }

    DrawText(title, x, y, fs, (Color){clist[0],clist[1],clist[2],clist[3]});
    
    return TCL_OK;
}

static int
DrawRectableCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    int x, y, w, h, col_len, clist[4];
    Tcl_Obj **col;

    if (objc != 6) {
        Tcl_WrongNumArgs(interp, 1, objv, "x y w h color");
        return TCL_ERROR;
    }

    if (Tcl_ListObjGetElements(interp, objv[5], &col_len, &col) != TCL_OK) {
        return TCL_ERROR;
    }
    
    if (Tcl_GetIntFromObj(interp, objv[1], &x) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[2], &y) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[3], &w) != TCL_OK ||
        Tcl_GetIntFromObj(interp, objv[4], &h) != TCL_OK) {
        return TCL_ERROR;
    }

    for (int i = 0; i < 4; i++) {
        Tcl_GetIntFromObj(interp, col[i], &clist[i]);
    }

    DrawRectangle(x, y, w, h, (Color){clist[0],clist[1],clist[2],clist[3]});
    
    return TCL_OK;
}

static int
IsKeyDownCmd(
    ClientData    clientData,
    Tcl_Interp   *interp,
    int           objc,
    Tcl_Obj *const objv[]
){
    int key;
    bool isDown;
    
    if (objc != 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "key");
        return TCL_ERROR;
    }

    if (Tcl_GetIntFromObj(interp, objv[1], &key) != TCL_OK) {
        return TCL_ERROR;
    }

    isDown = IsKeyDown(key);

    Tcl_SetObjResult(interp, Tcl_NewBooleanObj(isDown));
    return TCL_OK;
}

/* Initialization entry point; name must match the library name */
int
Raylib_Init(Tcl_Interp *interp)
{
    /* Initialize the stubs table for version 8.6 or later */
    if (Tcl_InitStubs(interp, "8.6", 0) == NULL) {
        return TCL_ERROR;
    }
    
    // Manage Window
    Tcl_CreateObjCommand(interp, "init_window", InitWindowCmd, NULL, NULL);
    Tcl_CreateObjCommand(interp, "window_should_close", WindowShouldCloseCmd, NULL, NULL);
    Tcl_CreateObjCommand(interp, "close_window", CloseWindowCmd, NULL,  NULL);
    Tcl_CreateObjCommand(interp, "set_target_fps",  SetTargetFPSCmd,  NULL,  NULL);

    // Draw Graphics
    Tcl_CreateObjCommand(interp, "begin_drawing",  BeginDrawingCmd,  NULL,  NULL);
    Tcl_CreateObjCommand(interp, "end_drawing",  EndDrawingCmd, NULL, NULL);
    Tcl_CreateObjCommand(interp, "clear_background", ClearBackgroundCmd, NULL, NULL);

    Tcl_CreateObjCommand(interp, "draw_text", DrawTextCmd, NULL, NULL);
    Tcl_CreateObjCommand(interp, "draw_rectangle", DrawRectableCmd, NULL, NULL);

    // Input
    Tcl_CreateObjCommand(interp, "is_key_down",  IsKeyDownCmd,  NULL,  NULL);

    /* Declare that we provide package “myext” version “1.0” */
    return Tcl_PkgProvide(interp, "raylib", "1.0");
}