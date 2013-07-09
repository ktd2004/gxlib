/*******************************************************************************
������Ʈ :  gxLib
������ȣ :  0.0.1
��⳻�� :  bmp, jpg, png ������ ó��
�ۼ���   :  ��漮(jwjwmx@gmail.com)
Ȩ������ :  http://forum.falinux.com
�������� :
           2011-05-11	�ۼ� ����

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>                                                              // malloc srand
#include <string.h>                                                              // abs
#include <stdarg.h>

#include <unistd.h>                                                              // open/close
#include <fcntl.h>                                                               // O_RDWR
#include <sys/ioctl.h>                                                           // ioctl
#include <sys/mman.h>                                                            // mmap PROT_
#include <linux/fb.h>

#include <gxpng.h>
#include <gxjpg.h>
#include <gx.h>
#include <gxfile.h>

int gx_open_file( dc_t *dc, char *filename)
//-------------------------------------------------------------------------------
// ����: �μ��� ������ filename�� �̹��� ������ ȭ�鿡 ���
// ����: BitBlt�� ������ ó���ϱ� ���� DC Type�� DCTYPE_SCREEN���� �����Ѵ�.
// �μ�: width       ������ ��
//       height      ������ ����
// ��ȯ: ���� Device Context �ڵ�
{
    dc_t    *bmp;
    dc_t    *png;
    dc_t    *jpg;
    int      sz_filename;
    char     file_ext[4];

    sz_filename = strlen(filename);
    if ( 4 > sz_filename)
    {
        return GXERR_FILE_NAME;
    }


    memcpy( file_ext, filename+strlen(filename)-3, 3);
    file_ext[3] = '\0';

    if ( 0 == strcasecmp( file_ext, "bmp"))
    {
        bmp = gx_bmp_open( filename);
        if ( NULL == bmp)
            printf( "gx_open_file() : %s is not exists.\n", filename);
        else
        {
            gx_bitblt( dc, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
            gx_bmp_close( bmp);
        }
    }
    else if ( 0 == strcasecmp( "jpg", file_ext))
    {
        jpg = gx_jpg_open( filename);
        if ( NULL == jpg)
            printf( "gx_open_file() : %s is not exists.\n", filename);
        else
        {
            gx_bitblt( dc, 0, 0, ( dc_t *)jpg, 0, 0, jpg->width, jpg->height);
            gx_jpg_close( jpg);
        }
    }
    else if ( 0 == strcasecmp( "png", file_ext))
    {
        png = gx_png_open( filename);
        if ( NULL == png)
            printf( "gx_open_file() : %s is not exists.\n", filename);
        else
        {
            gx_bitblt( dc, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);
            gx_png_close( png);
        }
    }
    else
    {
        printf( "gx_open_file() : %s is not valid graphic format.\n", file_ext);
        return GXERR_FILE_NAME;
    }
    return GXERR_NONE;
}




