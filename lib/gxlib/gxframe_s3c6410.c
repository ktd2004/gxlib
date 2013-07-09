/*
 * gxframe_s3c6410.c
 *
 *  Created on: 2011. 5. 12.
 *      Author: jwjw
 *      ���� ���� : \\eabi\staff\freefrug\kernel\linux-2.6.29\drivers\video\samsung\s3cfb_fimd4x.c
 *      ���� ���� : \\eabi\staff\freefrug\kernel\linux-2.6.29\drivers\video\samsung\s3cfb.h
 */

#include <stdio.h>
#include <stdlib.h>                                                              // malloc srand
#include <string.h>                                                              // abs
#include <stdarg.h>

#include <unistd.h>                                                              // open/close
#include <fcntl.h>                                                               // O_RDWR
#include <sys/ioctl.h>                                                           // ioctl
#include <sys/mman.h>                                                            // mmap PROT_
#include <linux/fb.h>

#include <gx.h>
#include <gxframe.h>

//typedef struct {
//  unsigned int colval_red;
//  unsigned int colval_green;
//  unsigned int colval_blue;
//} s3cfb_color_val_info_t;


//  color_val_info.colval_red   = 0x1f;
//  color_val_info.colval_green = 0;
//  color_val_info.colval_blue  = 0;

//  ioctl( fb_1->fd, _IOW( 'F', 305, s3cfb_color_val_info_t), &color_val_info);                     // Color Key Setup

//printf( "color_val_info.colval_red  =%d\n", color_val_info.colval_red  );
//printf( "color_val_info.colval_green=%d\n", color_val_info.colval_green);
//printf( "color_val_info.colval_blue =%d\n", color_val_info.colval_blue );

typedef struct {
    int direction;
    unsigned int compkey_red;
    unsigned int compkey_green;
    unsigned int compkey_blue;
} s3cfb_color_key_info_t;


//-------------------------------------------------------------------------------
// ����   v_sync Ÿ���� ��ٸ���.
// �μ�   a_filedesc  : ȭ�� ��� ���� ��ũ����
// ��ȯ   ���� : ���� ����. ��ǥ���� ��) -EDEFAULT( -14)
static int wait_v_sync( int a_filedesc){

    int n_arg = 0;

    return ioctl( a_filedesc, _IOW( 'F', 32, unsigned int), &n_arg);                             // FBIO_WAITFORVSYNC
}
//-------------------------------------------------------------------------------
// ����: ������ �������� ȭ�鿡 ���
// �μ�: a_fb : ȭ�鿡 ����� ������ ����
int gx_show_frame( frame_buffer_t   *a_fb)
{
    if ( 0 > wait_v_sync( a_fb->fd) ){
        printf( "wait v sync error\n");
        return -1;
    }
    ioctl( a_fb->fd, _IO( 'F', 201), NULL);                                     // OSD Start
    return 0;
}

//-------------------------------------------------------------------------------
// ����: �������� ȭ�鿡�� ����
// �μ�: a_fb : ȭ�鿡 ����� ������ ����
int gx_hide_frame( frame_buffer_t   *a_fb)
{
    if ( 0 > wait_v_sync( a_fb->fd) ){
        printf( "wait v sync error\n");
        return -1;
    }
    ioctl(a_fb->fd, _IO('F', 202), NULL); // OSD Stop
    return 0;
}

//-------------------------------------------------------------------------------
// ����: �����ӿ��� �������� Ư�� ������ �����ϰ� ó�� ����
// �μ�: a_fb : ȭ�鿡 ����� ������ ����
int gx_start_frame_trans( frame_buffer_t *a_fb)
{
    if ( 0 > wait_v_sync( a_fb->fd) ){
        printf( "wait v sync error\n");
        return -1;
    }
    ioctl( a_fb->fd, _IO( 'F', 300), NULL);                                 // Color Key Stop
    return 0;
}

//-------------------------------------------------------------------------------
// ����: �������� ���� ���� ó���� ����
// �μ�: a_fb : ȭ�鿡 ����� ������ ����
int gx_stop_frame_trans( frame_buffer_t *a_fb)
{
    if ( 0 > wait_v_sync( a_fb->fd) ){
        printf( "wait v sync error\n");
        return -1;
    }
    ioctl( a_fb->fd, _IO( 'F', 301), NULL);                                 // Color Key Stop
    return 0;
}
//-------------------------------------------------------------------------------
// ����: �������� �Ϻ� ������ Ư�� ������ ���� ������ ����
// �μ�: a_fb : ȭ�鿡 ����� ������ ����
// �μ�: a_color  : �����ϰ� ������ ����
int gx_set_frame_trans_color( frame_buffer_t *a_fb, color_t a_color)
{
    s3cfb_color_key_info_t  color_key_info;

    color_key_info.direction        = 0;
    switch( a_fb->colors)
    {
    case 16 :
        color_key_info.compkey_red      = a_color.red   >> 3;
        color_key_info.compkey_green    = a_color.green >> 2;
        color_key_info.compkey_blue     = a_color.blue  >> 3;
        break;
    default :
        color_key_info.compkey_red      = a_color.red;
        color_key_info.compkey_green    = a_color.green;
        color_key_info.compkey_blue     = a_color.blue;
        break;
    }

    if ( 0 > wait_v_sync( a_fb->fd) ){
        printf( "wait v sync error\n");
        return -1;
    }
    ioctl( a_fb->fd, _IOW( 'F', 304, s3cfb_color_key_info_t), &color_key_info); // Color Key Setup

    return gx_start_frame_trans( a_fb);
}
