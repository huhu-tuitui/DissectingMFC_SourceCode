// stdafx.cpp : source file that includes just the standard includes
//	JBACKUP.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file




#include <windows.h>
#include <stdio.h>
#include <string.h>

#define FILEMAX 300  // allow max. 300 files in each directory

typedef struct _DESTFILE
{
    WIN32_FIND_DATA fd;
    BOOL bMatch;
} DESTFILE;

typedef struct _SRCFILE
{
    WIN32_FIND_DATA fd;
    BOOL bIsNew;
} SRCFILE;


void main(int argc, char* argv[])
{
int i, j, iSrcFiles, iDestFiles;
HANDLE hFile;
WIN32_FIND_DATA fd;
BOOL bRet = TRUE;
char src[MAX_PATH+1], dest[MAX_PATH+1], destpath[MAX_PATH+1];
SRCFILE  srcFiles[FILEMAX];
DESTFILE destFiles[FILEMAX];
BOOL bFound = FALSE;
DWORD dwcNameSize = MAX_PATH+1;
char szBuffer[MAX_PATH+1];

  if (argc < 2) {
      printf("jbackup <SrcDir> <DstDir> \n");
      printf("���� jbackup g: k: \n\n");

      printf("�� SrcDir ���n����ؐ�� DstDir \n");
      printf("�K�� DstDir ��٘�N�n������ \n\n");

      printf("����]��ָ�� DstDir���A�O�� k: \n");
      printf("�K�� k: ��Ŀ��Ŀ��O���c SrcDir ͬ \n\n");

      printf("���� jbackup g: <Enter> \n");
      printf("��Ŀǰ g: �� g:\\u002\\doc \n");
      printf("�ஔ춰� g:\\u002\\doc ��ݵ� k:\\u002\\doc �� \n");
      return;
  }

  // for (i=0; i< argc; i++)
  //     printf("argv[%d]: %s \n", i, argv[i]);

  strcpy(src, argv[1]);
  if (argc == 2) {
      GetCurrentDirectory(dwcNameSize, &szBuffer);
      strcpy(dest, szBuffer);
      // printf("current directory : %s \n", dest);
      dest[0] = 'k';
      strcpy(destpath, dest); // destpath should be something like "k:\u002\doc\".
      strcat(destpath, "\\"); // just prepare for use latter (when updating and deleting).

      strcat(dest, "\\*.*");  // dest should be something like "k:\u002\doc\*.*"
  }
  else {
      strcpy(destpath, argv[2]); // destpath should be something like "k:"
                                 // just prepare for usage latter (when updating and deleting).
      strcpy(dest, argv[2]);
      strcat(dest, "*.*");       // then dest should be something like "k:*.*"
  }

  strcat(src, "*.*");         // src should be something like g:*.*
  // printf("src=%s \n", src);
  // printf("dest=%s \n", dest);
  // printf("destpath=%s \n", destpath);


  // prepare srcFiles[]...
  bRet = TRUE;
  iSrcFiles = 0;
  // printf("Directory listing of %s\n", src);
  hFile = FindFirstFile(src, &fd);
  while (hFile != INVALID_HANDLE_VALUE && bRet)
  {
      if (fd.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE) {
          srcFiles[iSrcFiles].fd = fd;
          srcFiles[iSrcFiles].bIsNew = FALSE;
          // printf("%s\n", srcFiles[iSrcFiles].fd.cFileName);
          iSrcFiles++;
      }
      bRet = FindNextFile(hFile, &fd);
  }


  // prepare destFiles[]...
  bRet = TRUE;
  iDestFiles = 0;
  // printf("Directory listing of %s\n", dest);
  hFile = FindFirstFile(dest, &fd);
  while (hFile != INVALID_HANDLE_VALUE && bRet)
  {
      if (fd.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE) {
          destFiles[iDestFiles].fd = fd;
          destFiles[iDestFiles].bMatch = FALSE;
          // printf("%s\n", destFiles[iDestFiles].fd.cFileName);
          iDestFiles++;
      }
      bRet = FindNextFile(hFile, &fd);
  }


  // check for new files and redudant files...
  for (i=0; i<iSrcFiles; i++) {
    bFound = FALSE;
    for (j=0; j<iDestFiles; j++) {
      if (!(destFiles[j].bMatch))  {
        if (strcmpi(destFiles[j].fd.cFileName, srcFiles[i].fd.cFileName) == 0) {
            // find same files in dest directory
            destFiles[j].bMatch = TRUE;
            bFound = TRUE;

            if (CompareFileTime(&destFiles[j].fd.ftLastWriteTime,
                                &srcFiles[i].fd.ftLastWriteTime) < 0) {
                // src file is new than dest file
                srcFiles[i].bIsNew = TRUE;
            }
            break;  // break j loop, because found!
        }
      }
    }

    // printf("j=%d  ", j);
    if (bFound == FALSE) // not found, so is new.
        srcFiles[i].bIsNew = TRUE;
  }


  // updating new files ...
  for (i=0, j=0; i<iSrcFiles; i++) {  // j for new files counter
    if (srcFiles[i].bIsNew) {
        printf("%s\n", srcFiles[i].fd.cFileName);
        j++;
    }
  }

  if (j==0) {
      // printf("no file new \n");
      printf("�]���κΙn����Ҫ���� \n");
  }
  else {
      // printf("There are %d files need to be updated \n", j);
      // printf("if you do not want to update these files, press Ctrl-Break \n");
      // printf("otherwise anykey...\n");
      printf("������ %d �n����Ҫ���� \n", j);
      printf("����㲻����������@Щ�n����Ո�� Ctrl-Break \n");
      printf("��tՈ�������I...\n");
      getch();
  }

  for (i=0; i<iSrcFiles; i++) {
      // printf("srcFiles[%d].filename = %s \n", i, srcFiles[i].fd.cFileName);
      // printf("srcFiles[%d].bIsNew = %d \n", i, srcFiles[i].bIsNew);

      if (srcFiles[i].bIsNew) {
          strcpy(dest, destpath);
          strcat(dest, srcFiles[i].fd.cFileName);
          CopyFile(srcFiles[i].fd.cFileName, dest, FALSE); // FALSE means overwrite
          // printf("copy %s %s \n", srcFiles[i].fd.cFileName, dest);
      }
  }


  // deleting redudant files...
  // printf("redundant files :\n");
  for (j=0, i=0; j<iDestFiles; j++) {  // i for redudant files counter
    if (!destFiles[j].bMatch) {
        printf("%s\n", destFiles[j].fd.cFileName);
        i++;
    }
  }

  if (i==0) {
      // printf("no redudant file \n");
      printf("�]���κ�٘�N�n����Ҫ�h�� \n");
  }
  else {
      // printf("There are %d files need to be deleted \n", i);
      // printf("if you do not want to delete those files, press Ctrl-Break \n");
      // printf("otherwise anykey...\n");
      printf("������ %d �n����Ҫ�h�� \n", i);
      printf("����㲻�뚢���@Щ�n����Ո�� Ctrl-Break \n");
      printf("��tՈ�������I...\n");
      getch();
  }

  for (j=0; j<iDestFiles; j++) {
      // printf("destFiles[%d].filename = %s \n", j, destFiles[j].fd.cFileName);
      // printf("destFiles[%d].bMatch = %d \n", j, destFiles[j].bMatch);

      if (!destFiles[j].bMatch) {
          strcpy(dest, destpath);
          strcat(dest, destFiles[j].fd.cFileName);
          DeleteFile(dest);
          // printf("delete %s \n", dest);
      }
  }
}