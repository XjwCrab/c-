#include"Utility.h"
_LIB_EXT_ MYSQL mysql;
_LIB_EXT_ MYSQL_RES *result;
_LIB_EXT_ MYSQL_ROW row;
_LIB_EXT_ HINSTANCE g_hInstance;
_LIB_EXT_ int g_level;
_LIB_EXT_ char g_operator[VALUE_LENTH_MAX];
#ifndef BOOK_DESK_INFO
#define BOOK_DESK_INFO
BOOL CALLBACK Desk_Info_Proc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam);
#endif