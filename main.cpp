#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include "resource.h"

#define MAXLEN 1024
#define LISTFILE "files1149761294.txt"
#define RAWCMD "ffmpeg -f concat -safe 0 -i files1149761294.txt -c copy \"%s\[merged]%s\""

HINSTANCE hInst;

int ProcessFiles(HWND hwndDlg,char (*files)[MAXLEN],int dropcount){
	FILE *fp=fopen(LISTFILE,"w");
	char cmd[MAXLEN],path[MAXLEN],*filename;
	int i;
	if(!fp){
		MessageBox(hwndDlg,"创建临时文件失败！","错误",MB_ICONERROR);
		return -1;
	}
	for(i=0;i<dropcount;i++){
		fprintf(fp,"file '%s'\n",files[i]);
	}
	fclose(fp);
	filename=PathFindFileName(files[0]);
	strncpy(path,files[0],filename-files[0]);
	path[filename-files[0]]=0;
	sprintf(cmd,RAWCMD,path,filename);
	system(cmd);
	DeleteFile(LISTFILE);
	return 0;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
	//初始化对话框
    case WM_INITDIALOG:
    {
    }
    return TRUE;
    //关闭对话框
    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;
    //丢文件
    case WM_DROPFILES:
	{
		char files[100][MAXLEN];
		char buf[MAXLEN];
		HDROP hdrop=(HDROP)wParam;
		int i,dropcount=DragQueryFile(hdrop,-1,0,0);
		for(i=0;i<dropcount;i++){
			DragQueryFile(hdrop,i,files[i],MAXLEN);
		}
		ProcessFiles(hwndDlg,files,dropcount);
	}
	return TRUE;
    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
