/*******************************************************************************
������Ʈ : gxLib
��⳻�� : BDF ��Ʈ ���
�������� : 2008-10-22
�ۼ���   : Ǫ������(ssseo88@chol.com)
������   : ��漮( jwjw, jwjwmx@gmail.com)
���۱�   : �ּ� ������ �������� �ʴ� �� ���� ����
�������� :
            - 2010-05-03
                ��Ʈ�� ������ ����� �� �ֵ��� ����
Ȩ������ : http://forum.falinux.com
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>                                                              // malloc srand
#include <string.h>                                                              // abs

#include <unistd.h>                                                              // open/close
#include <fcntl.h>                                                               // O_RDWR

#include <gx.h>
#include <gxbdf.h>
#include <fontinfo.h>
#include <ksc5601.h>

#define MAX_STRING_LENGTH     1024

//jwjw bdfFontCache   gx_fontcache;
//jwjw FILE*          gx_fontfile    = NULL;

static void  _text_out_( dc_t *dc, int org_x , int org_y, unsigned short* string)
//-------------------------------------------------------------------------------
{
    int             k , i, j ,m;
    int             xPixel, yPixel;
    int             save_x;
    unsigned int    nCode;
    bdfFont         Font;
    pbdfFont        pFont;
    
    for( k = 0 ; string[k] != 0x0000 ; k+=1 )
    {
        nCode = string[k];//(0xff00 & ( ((unsigned char ) str[strIndex][k]) << 8 )) | ( ( (unsigned char) str[strIndex][k+1]) & 0x00ff );
        
        if ( ReadFontOfCode( &dc->font->fontcache, dc->font->fontfile, dc->font->fndex, nCode ,&Font ))
            pFont = &Font;
        else
            pFont = NULL;
        
        if ( pFont != NULL )
        {
            save_x = xPixel = org_x + pFont->bbxoff;
            yPixel = org_y - pFont->bbyoff;
            
            for( i = pFont->bbh -1 ; i >=0   ; --i )
            {
                for ( j=0 ; j < (pFont->bbw+8)/8 ; ++ j)
                {
                    for( m = 0 ; m < 8 ; ++m )
                    {
                        if ( ( j*8 + m + 1) > pFont->bbw ) break;
                        if ((( pFont->data[(pFont->bbw+7)/8*i+j] & (1 << (8-m-1)) )>>(8-m-1)) == 1 )
                        {
                            gx_set_pixel( dc ,xPixel ,yPixel, dc->font_color);
                        }
                        else
                        {
                            //HBRUSH hOld = (HBRUSH)::SelectObject( pDC->GetSafeHdc() ,::GetStockObject(WHITE_BRUSH) );
                            //pDC->Rectangle(CRect(x,y,x+1 , y+1 ));
                            //::SelectObject( pDC->GetSafeHdc() , hOld );
                        }
                        xPixel++;
                    }
                }
                yPixel--;
                xPixel = save_x;
            }
            org_x+= pFont->dwidth;
        }
    }
}

int gx_text_out( dc_t *dc, int coor_x, int coor_y, char *text)
/**
    @brief  DC�� ���ڿ��� ����Ѵ�.\n
    ����: coo_y�� ���ڿ� ����� �ϴ� ��ǥ. ��, coor_x=���� ��ǥ, coor_y=�ϴ� ��ǥ
    @param  dc : Device Context
            coor_x : x ��ǥ
            coor_y : �ϴ� y ��ǥ 
            text : ����� ���ڿ�
*/
{
    static unsigned short   uniString[MAX_STRING_LENGTH+1];
    int                     szText;
                     
    if  ( NULL == dc->font)                                             // ������ ��Ʈ�� ���ٸ� ����
    {          
        printf( "gx_text_out() : no font assigned.\n");
        return GXERR_NO_ASSIGNED_FONT;
    }
    szText   = strlen( text);
    if ( MAX_STRING_LENGTH < szText)
    {
       text[MAX_STRING_LENGTH] = '\0';
       szText                  = MAX_STRING_LENGTH;
    }
    
    convertMultibyteToUnicodeString( (unsigned char*)text, szText, uniString, MAX_STRING_LENGTH);
    _text_out_( dc, coor_x ,coor_y, uniString);
    
    return GXERR_NONE;
}

void gx_set_font( dc_t *dc, font_t *font)
/**
    @brief  �μ��� ���� DC�� ��Ʈ�� �����Ѵ�.\n
    �� �Լ��� ������� �ʰ� DC�� font �Ӽ��� ���� �����ص� �ȴ�.
    @param  dc : Device Context
            font : �۲� ������
    @return\n
        ��Ʈ ����� ���� ������
        NULL : ��Ʈ ���⿡ ����
*/
{
    dc->font    = font;
}

font_t *gx_open_font( char *font_filename)
/**
    @brief  ��Ʈ�� ����ϱ� ���� �۲� ������ ���⸦ �Ѵ�.\n
    gxLib�� ��Ʈ�� ����ϱ� ���� gx_open_font()�� �����Ѵ�. \n
    �Ӻ���� �ý��ۿ����� �� �� ���⸦ �� ��Ʈ�� ���α׷� ������� ��� ���Ǳ⵵ ������, \n
    ��Ʈ ���� ó�� �Լ����� malloc() �Լ��� ȣ���ϴ� ��ƾ�� ���� �м��� �̾��ϱ� �����̴�. \n
    gx_close_font()�� �����Ϸ��� fontinfo.c ���� ȣ���ϴ� malloc()�� ���� free()�� ���־�� �Ѵ�.
    @param  font_filename : �۲� ���� �̸�
    @return\n
        ��Ʈ ����� ���� ������
        NULL : ��Ʈ ���⿡ ����
*/
{
    font_t  *font;
    
    font = malloc( sizeof( font_t));                                               // dc_t ����ü �޸� �Ҵ�
    if ( NULL != font)                                                             // �޸� ���ϱ⿡ �����Գ�
    {
        font->fontfile = fopen( font_filename, "r");                               // ��Ʈ ���� ����
        if ( NULL == font->fontfile)
        {
            free( font);
            printf( "gx_open_font() : no file->%s\n", font_filename);
            return NULL;
        }
        FontCacheInit( &font->fontcache);
        FontChanged(    font->fontfile,  &font->fontcache, font->fndex);
    }
    else
    {
        printf( "gx_open_font() : out of memory.\n");    
    }
    return font;
}
