#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <time.h>
#include    <gx.h>

dc_t   *dc_screen;                      // 화면 Device Context

int     view_width;                     // 화면 폭
int     view_height;                    // 화면 높이
int     half_width;                     // 화면 폭의 절반 크기
int     half_height;                    // 화면 높이의 절반 크기
int     center_x;                       // 화면 중앙 x 좌표
int     center_y;                       // 화면 중앙 y 좌표

void press_any_key( void)
{
    printf( "press any key......\n");
    getchar();
}

/** ----------------------------------------------------------------------------
    @brief 선 그리기 예제
*/
void test_draw_line( void)
{
    int     ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));                              // 화면을 흑색으로 clear

    gx_move_to( dc_screen, rand() % view_width, rand() % view_height);          // 임의의 좌표로 이동
    for ( ndx= 0; ndx < 100; ndx++)                                             // gxline_to()를 이용하여 여러 개의 선을 출력
    {
       dc_screen->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
       gx_line_to( dc_screen, rand() % view_width, rand() % view_height);
    }
}

void test_get_set_pixel( void)
{
    color_t	color;
    int     coor_x;
    int     coor_y;
    int     ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));                              // 화면을 흑색으로 clear

    // 화면의 왼쪽 반 부분에 임의의 선을 그림
    gx_move_to( dc_screen, rand() % half_width, rand() % view_width);           // 임의의 좌표로 이동
    for ( ndx= 0; ndx < 100; ndx++)
    {
       dc_screen->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
       gx_line_to( dc_screen, rand() % half_width, rand() % view_height);
    }
    // 화면 왼쪽 반을 오른쪽 반에 복사
    for ( coor_y = 0; coor_y < view_height; coor_y++)
    {
        for ( coor_x = 0; coor_x < half_width; coor_x++)
        {
            gx_get_pixel( dc_screen, coor_x           , coor_y, &color);
            gx_set_pixel( dc_screen, coor_x+half_width, coor_y,  color);
        }
    }
}

void  test_rectangle( void)
{
    int     x1, y1, x2, y2;
    int     ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));
    dc_screen->brush_color   = gx_color( 0, 0, 0, 0);

    for ( ndx= 0; ndx < 50; ndx++)
    {
        x1  = rand() % view_width;
        y1  = rand() % view_height;
        x2  = rand() % view_width;
        y2  = rand() % view_height;

        switch ( rand() % 3)
        {
        case 0   :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( 0, 0, 0, 0);
                 break;
        case 1   :
                 dc_screen->pen_color     = gx_color( 0, 0, 0, 0);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        default  :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        }
        gx_rectangle( dc_screen, x1, y1, x2, y2);
        usleep( 50 *1000);                                                      // 50 msec
    }
}

void  test_circle( void)
{
    int      coor_x, coor_y;
    int      radius;
    int      ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));
    for ( ndx = 0; ndx < 50; ndx++)
    {
        coor_x         = rand() % view_width;
        coor_y         = rand() % view_height;
        radius         = rand() % half_width;

        switch ( rand() % 3)
        {
        case 0   :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( 0, 0, 0, 0);
                 break;
        case 1   :
                 dc_screen->pen_color     = gx_color( 0, 0, 0, 0);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        default  :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        }
        gx_circle( dc_screen, coor_x, coor_y, radius);
        usleep( 50 *1000);
    }
}

void test_ellipse( void)
{
    int      coor_x, coor_y;
    int      width,  height;
    int      ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));
    for ( ndx = 0; ndx < 50; ndx++)
    {
        coor_x         = rand() % view_width;
        coor_y         = rand() % view_height;
        width          = rand() % half_width;
        height         = rand() % half_height;

        switch ( rand() % 3)
        {
        case 0   :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( 0, 0, 0, 0);
                 break;
        case 1   :
                 dc_screen->pen_color     = gx_color( 0, 0, 0, 0);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        default  :
                 dc_screen->pen_color     = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 dc_screen->brush_color   = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
                 break;
        }
        gx_ellipse( dc_screen, coor_x, coor_y, width, height);
        usleep( 50 *1000);
    }
}

void test_bitmap( void)
{
    bmp_t   *bmp;

    bmp = gx_bmp_open( "bpp-01.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-01.bmp");                                         // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-04.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-04.bmp");                                         // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-08.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-08.bmp");                                         // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-24.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-24.bmp");                                         // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-32.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-32.bmp");                                         // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }
}

void test_jpg( void)
{
    char    *jpg_name = "jpeg-image.jpg";
    jpg_t   *jpg;

    jpg = gx_jpg_open( jpg_name);
    if ( NULL == jpg)
        gx_print_error( jpg_name);                                              // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)jpg, 0, 0, jpg->width, jpg->height);
        gx_jpg_close( jpg);
    }
}

void test_png( void)
{
    png_t   *png;

    png = gx_png_open( "png-08bpp.png");
    if ( NULL == png)
        gx_print_error( "png-08bpp.png");                                       // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 100, ( dc_t *)png, 0, 0, png->width, png->height);
        gx_png_close( png);
        usleep( 300 *1000);                                                     // 300 msec
    }

    png = gx_png_open( "png-24bpp.png");
    if ( NULL == png)
        gx_print_error( "png-24bpp.png");                                       // 실행 중 에러 내용을 출력
    else
    {
        gx_bitblt( dc_screen, 0, 200, ( dc_t *)png, 0, 0, png->width, png->height);
        gx_png_close( png);
        usleep( 300 *1000);                                                     // 300 msec
    }
}

void test_text( void)
{
    if ( gx_set_font( "nbold32.bdf"))
            gx_print_error("nbold32.bdf");
    else
    {
       dc_screen->pen_color = gx_color( 0, 0, 0, 255);
       gx_text_out( dc_screen, 50 , 270, "FALINUX 포럼!!"  );
    }
}

void test_list( void)
{
    image_list_t  *list;                // 이미지 리스트 객체 핸들
    png_t         *png_cell;
    int            ndx;

    if ( !( list = gx_imagelist_create( "sample-list.png", 90, 90)))
        gx_print_error( "gx_imagelist_create()");
    else
    {
        for ( ndx = 0; ndx < list->count; ndx++)
        {
                                        // 이미지 리스트에서 인덱스에 해당하는 이미지를 구함
            png_cell = gx_imagelist_get( list, ndx);
            gx_bitblt( dc_screen, 200, 200,
                        (dc_t *)png_cell, 0, 0, png_cell->width, png_cell->height);
            usleep( 500 *1000);                                                 // 500 msec
        }
        gx_imagelist_close( list);
    }
}

void test_mosaic( void)
{
    mosaic_t   *mosaic;
    int         ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));

                                        // 모자익 객체를 생성

    mosaic = gx_mosaic_create(  (dc_t *)gx_png_open( "fore.png"),               // 평소에 출력되는 이미지
                                (dc_t *)gx_png_open( "back.png"),               // 색상에 따라 출력될 이미지
                                (dc_t *)gx_png_open( "color_table.png"),        // 출력 영역을 선택하는 이미지
                                100, 100);          // 출력 대상 DC에 출력할 x, y 위치

                                        // 이미지 내의 아이템별 좌표 정보를 등록

    gx_mosaic_add( mosaic,  0,  0, 30, 91,                                      // 아이템에 해당하는 이미지의 left, top, width, height
                            8, 37);                                             // 해당 아이템의 색상을 구하는 x, y 좌표.
    gx_mosaic_add( mosaic, 23,  2, 59, 44, 40, 14);                             // 아이템 좌표는 계속 등록할 수 있다.
    gx_mosaic_add( mosaic, 60, 10, 36, 42, 75, 28);
    gx_mosaic_add( mosaic, 22, 37, 55, 47, 46, 62);
    gx_mosaic_add( mosaic, 31, 56, 65, 41, 83, 84);

    for ( ndx = 0; ndx < mosaic->count; ndx++)
    {
        gx_mosaic_draw( dc_screen, mosaic, ndx);
        usleep( 500 *1000);                                                     // 500 msec
    }

    gx_mosaic_close( mosaic);
}

void test_layer( void)
{
    png_t      *png;                    // PNG 이미지를 로드하기 위해 사용
    bmp_t      *bmp;                    // BmP 이미지를 로드하기 위해 사용
    layer_t    *layer;                  // 레이어 객체
    int         ndx_fish;               // 물고기 그림 레이어 인덱스 번호
    int         ndx_chimpanzee;         // 침팬지 그림 레이어 인덱스 번호
    int         ndx_lft_button;         // 왼쪽 버튼의 평상 시 레이어 인덱스  번호
    int         ndx_lft_clicked;        // 왼쪽 버튼이 눌렸을 때 레이어 인덱스 번호
    int         ndx_top_button;         // 위쪽 버튼의 평상 시 레이어 인덱스 번호
    int         ndx_top_clicked;        // 위쪽 버튼이 눌렸을 때 레이어 인덱스 번호
    int         ndx_rht_button;         // 오른쪽 버튼의 평상 시 레이어 인덱스 번호
    int         ndx_rht_clicked;        // 오른쪽 버튼이 눌렸을 때 레이어 인덱스 번호
    int         ndx_btm_button;         // 아래쪽 버튼의 평상 시 레이어 인덱스 번호
    int         ndx_btm_clicked;        // 아래쪽 버튼이 눌렸을 때 레이어 인덱스 번호
    int         ndx;

                                        // layer 객체 생성

    layer = gx_layer_create(  dc_screen,            // 출력 대상 DC
                              50 ,  25,             // Layer의 Screen 상의 위치
                              300, 250);            // Layer의 폭과 넓이

                                        // 파일을 이용하여 레이어를 추가

    png = gx_png_open( "fish.png");             ndx_fish        = gx_layer_add( layer, (dc_t *)png,-100, 200, GX_FALSE);
    png = gx_png_open( "chimpanzee.png");       ndx_chimpanzee  = gx_layer_add( layer, (dc_t *)png, 300,  10, GX_FALSE);
    png = gx_png_open( "left.png");             ndx_lft_button  = gx_layer_add( layer, (dc_t *)png,   5,  18, GX_TRUE );
    png = gx_png_open( "left-clicked.png");     ndx_lft_clicked = gx_layer_add( layer, (dc_t *)png,   5,  18, GX_FALSE);
    png = gx_png_open( "top.png");              ndx_top_button  = gx_layer_add( layer, (dc_t *)png,  18,   4, GX_TRUE );
    png = gx_png_open( "top-clicked.png");      ndx_top_clicked = gx_layer_add( layer, (dc_t *)png,  18,   4, GX_FALSE);
    png = gx_png_open( "right.png");            ndx_rht_button  = gx_layer_add( layer, (dc_t *)png, 110,  18, GX_TRUE );
    png = gx_png_open( "right-clicked.png");    ndx_rht_clicked = gx_layer_add( layer, (dc_t *)png, 110,  18, GX_FALSE);
    png = gx_png_open( "bottom.png");           ndx_btm_button  = gx_layer_add( layer, (dc_t *)png,  18, 107, GX_TRUE );
    png = gx_png_open( "bottom-clicked.png");   ndx_btm_clicked = gx_layer_add( layer, (dc_t *)png,  18, 107, GX_FALSE);
    bmp = gx_bmp_open( "bpp-32.bmp");                             gx_layer_add( layer, (dc_t *)bmp,   0,   0, GX_TRUE);
    gx_layer_redraw( layer);                                                    // 레이어 전체를 출력
    usleep( 500000);

                                        // 버튼을 갱신하면서 화면에 출력, 깜빡이는 현상이 발생

    gx_layer_visible( layer, ndx_lft_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_lft_clicked  , GX_TRUE );
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_lft_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_lft_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_top_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_top_clicked  , GX_TRUE );
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_top_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_top_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_rht_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_rht_clicked  , GX_TRUE );
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_rht_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_rht_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_btm_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_btm_clicked  , GX_TRUE );
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_btm_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_btm_clicked  , GX_FALSE);

                                        // 버튼의 출력 상태가 변해도 수동으로 출력, 깜빡임이 없음

    gx_layer_manual( layer, GX_TRUE);                                           // 레이어에 변화가 있어도 화면으로 출력하지 않음. gx_layer)redraw()를 호출해 주어야 함

    gx_layer_visible( layer, ndx_lft_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_lft_clicked  , GX_TRUE );
    gx_layer_redraw( layer);
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_lft_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_lft_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_top_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_top_clicked  , GX_TRUE );
    gx_layer_redraw( layer);
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_top_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_top_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_rht_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_rht_clicked  , GX_TRUE );
    gx_layer_redraw( layer);
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_rht_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_rht_clicked  , GX_FALSE);
    gx_layer_visible( layer, ndx_btm_button   , GX_FALSE);
    gx_layer_visible( layer, ndx_btm_clicked  , GX_TRUE );
    gx_layer_redraw( layer);
    usleep( 500 *1000);                                                         // 500 msec

    gx_layer_visible( layer, ndx_btm_button   , GX_TRUE );
    gx_layer_visible( layer, ndx_btm_clicked  , GX_FALSE);
    gx_layer_redraw( layer);

    gx_layer_manual( layer, GX_FALSE);                                  // 레이어에 변화가 있으면 바로 화면 갱신

                                        // 침팬지와 물고기를 이동

    gx_layer_visible( layer, ndx_fish        , GX_TRUE );
    gx_layer_visible( layer, ndx_chimpanzee  , GX_TRUE );
    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       ,  1, -1);
        gx_layer_move( layer, ndx_chimpanzee , -1,  0);
    }
    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       ,  1, 1);
        gx_layer_move( layer, ndx_chimpanzee , -1, -1);
    }
    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       , -1, 0);
        gx_layer_move( layer, ndx_chimpanzee ,  1, 1);
    }

    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       , 0, -1);
        gx_layer_move( layer, ndx_chimpanzee , 0,  1);
    }
    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       , -1,  0);
        gx_layer_move( layer, ndx_chimpanzee ,  0, -1);
    }
    for ( ndx = 0; ndx < 200; ndx++)
    {
        gx_layer_move( layer, ndx_fish       ,  1,  0);
        gx_layer_move( layer, ndx_chimpanzee ,  0,  1);
    }
    for ( ndx = 0; ndx < 300; ndx++)
    {
        gx_layer_move( layer, ndx_fish       ,  0,  1);
        gx_layer_move( layer, ndx_chimpanzee ,  1,  1);
    }

    gx_layer_move_to( layer, ndx_fish        ,  120,  100);
    gx_layer_move_to( layer, ndx_chimpanzee  ,   80,    0);

    gx_layer_close( layer);
}

void test_gx_open_file( void)
{
    dc_t       *dc_comp;

    dc_comp = gx_get_compatible_dc( dc_screen);             // dc_screen의 클론을 만듦

    gx_open_file( dc_comp, "bpp-32.bmp");                   // 파일을 open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_open_file( dc_comp, "jpeg-image.jpg");               // 파일을 open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_open_file( dc_comp, "png-24bpp.png");                // 파일을 open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_release_dc( dc_comp);
}

void test_bitblt_mask( void)
{
    dc_t       *dc_fore;                                                        // 평소 출력할 이미지
    dc_t       *dc_back;                                                        // 색상이 선택되었을 때 출력할 이미지
    dc_t       *dc_mask;                                                        // mask 이미지

    color_t     color;

    dc_fore = gx_get_compatible_dc( dc_screen);
    dc_back = gx_get_compatible_dc( dc_screen);
    dc_mask = gx_get_compatible_dc( dc_screen);

    gx_open_file( dc_fore, "gx_bitblt_mask_fore.bmp");
    gx_open_file( dc_back, "gx_bitblt_mask_back.bmp");
    gx_open_file( dc_mask, "gx_bitblt_mask_mask.bmp");

    gx_bitblt( dc_screen, 0, 0, dc_fore, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_get_pixel( dc_mask, 200, 300, &color);

    gx_bitblt_mask( dc_screen, dc_back, dc_mask, color, 24, 45, 530, 414);
    press_any_key();
    gx_bitblt_mask( dc_screen, dc_fore, dc_mask, color, 24, 45, 530, 414);
    press_any_key();

    gx_get_pixel( dc_mask, 365, 165, &color);

    gx_bitblt_mask( dc_screen, dc_back, dc_mask, color, 333, 133, 82, 89);
    press_any_key();
    gx_bitblt_mask( dc_screen, dc_fore, dc_mask, color, 333, 133, 82, 89);

    gx_release_dc( dc_back);
    gx_release_dc( dc_mask);
    gx_release_dc( dc_fore);
}

void test_gx_get_compatible_dc( void)
/** ----------------------------------------------------------------------------
    @brief dc_screen에 출력하기 전에 dc_screen의 복사본을 만들어 놓고, 복사본에 축력을 모두 처리한 후에 한번에 화면으로 출력. test_gx_png_create() 와는 달리 화면 깜빡임이 없다.
*/
{
    dc_t       *scr;                                        // dc_screen 의 클론
    png_t      *png;                                        // 파형 부분만 그리고 나머지는 투명 영역으로 이용
    bmp_t      *bmp;                                        // 배경 이미지용 bmp
    int         loop;
    int         ndx;                                        // 루프를 위한 인덱스

    scr = gx_get_compatible_dc( dc_screen);                 // dc_screen의 클론을 만듬
    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // 배경에 출력하기 위한 그림을 로딩
    png = gx_png_create( bmp->width, bmp->height);          // 투명 영역을 제공하기 위한 PNG 생성, BMP 크기로

    // 화면에 BMP 위에 선을 긋는 것을 10회 반복
    for ( loop = 0; loop < 10; loop++)
    {
        gx_clear( ( dc_t *)png, gx_color( 0, 0, 0, 0));

        // 난수를 이용하여 여러 개의 직선을 PNG 에 그려서 PNG를 완성

        gx_move_to( ( dc_t *)png, rand() % png->width, rand() % png->height);   // 난수로 특정 좌표로 이동
        for ( ndx = 0; ndx < 50; ndx++)
        {
           png->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
           gx_line_to( (dc_t *)png, rand() % png->width, rand() % png->height);
        }

        // 화면에 출력할 모든 내용을 우선 scr에 출력
        gx_clear ( scr, gx_color( 0, 0, 0, 255));                             // 화면을 깨끗하게 지움
        gx_bitblt( scr, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp를 화면에 출력
        gx_bitblt( scr, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png를 화면에 출력

        // 모두 그려진 scr을 한번에 화면으로 출력. test_gx_png_create()와는 달리 깜빡임이 없다
        gx_bitblt( dc_screen, 0, 0, scr, 0, 0, scr->width, scr->height);

        // 0.5초간 대기
        usleep( 500 * 1000);
    }

    gx_png_close( png);
    gx_bmp_close( bmp);
    gx_release_dc( scr);
}

void test_gx_png_create( void)
/** ----------------------------------------------------------------------------
    @brief PNG를 파일없이 생성하여 투명영역을 이용하는 예를 보여줌
*/
{
    png_t      *png;                                        // 파형 부분만 그리고 나머지는 투명 영역으로 이용
    bmp_t      *bmp;                                        // 배경 이미지용 bmp
    int         loop;
    int         ndx;                                        // 루프를 위한 인덱스

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // 배경에 출력하기 위한 그림을 로딩
    png = gx_png_create( bmp->width, bmp->height);          // 투명 영역을 제공하기 위한 PNG 생성, BMP 크기로

    // 화면에 BMP 위에 선을 긋는 것을 10회 반복
    for ( loop = 0; loop < 10; loop++)
    {
        gx_clear( ( dc_t *)png, gx_color( 0, 0, 0, 0));         //

        // 난수를 이용하여 여러 개의 직선을 PNG 에 그려서 PNG를 완성

        gx_move_to( ( dc_t *)png, rand() % png->width, rand() % png->height);   // 난수로 특정 좌표로 이동
        for ( ndx = 0; ndx < 50; ndx++)
        {
           png->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
           gx_line_to( (dc_t *)png, rand() % png->width, rand() % png->height);
        }

        // 화면에 배경 BMP를 출력하고, 다시 그 위에 선들이 그려져 있는 PNG를 출력
        gx_clear ( dc_screen, gx_color( 0, 0, 0, 255));                             // 화면을 깨끗하게 지움
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp를 화면에 출력
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png를 화면에 출력

        // 0.5초간 대기
        usleep( 500 * 1000);
    }

    gx_png_close( png);
    gx_bmp_close( bmp);
}
/** ----------------------------------------------------------------------------
    @brief PNG의 투명 영역을 이용하여 좌로 흐르는 파형 그래프를 출력하는 예제
*/
void draw_wave_with_create_png( void)
{
    #define     WAVE_WIDTH      10                          // 파형의 간격
    png_t      *png;                                        // 파형 부분만 그리고 나머지는 투명 영역으로 이용
    bmp_t      *bmp;                                        // 배경 이미지용 bmp
    int         coor_y;                                     // 파형을 그리기 위한 새로 구한 Y 좌표
    int         old_y          = 0;                         // 이전 파형과 연결하여 그리기 위한 이전 Y 좌표
    int         ndx;                                        // 루프를 위한 인덱스

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // 배경에 출력하기 위한 그림을 로딩
    png = gx_png_create( bmp->width, bmp->height);          // 투명 영역을 제공하기 위한 PNG 생성, BMP 크기로

    for( ndx = 0; ndx < 50; ndx++)                          // 파형 출력을 50까지
    {
        coor_y  = rand() %png->height;                      // 난수로 새(新) Y 좌표

        png->pen_color  = gx_color( 255, 255, 0, 255);
        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png 폭 - WAVE_WIDTH, 이전   Y 좌표에서
                    png->width-1         , coor_y);         // png 폭             , 새(新) Y 좌표까지 선을 긋기


        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp를 화면에 출력
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png를 화면에 출력


        // 다음 새(新) 파형을 오른쪽 끝에 그리기 위한 준비를 한다.
        // 참고로 이 과정에는 화면 출력이 없다. 즉, 화면에 변화가 없다
        // png의 오른쪽 부분을 왼쪽으로 이동
        gx_bitblt(  ( dc_t *)png, 0, 0,
                    ( dc_t *)png, WAVE_WIDTH, 0, png->width-WAVE_WIDTH, png->height);

        // 옮긴 후에 새로 그린 선을 투명색으로 다시 그려 지운다
        png->pen_color  = gx_color( 0, 0, 0, 0);
        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png 폭 - WAVE_WIDTH, 이전   Y 좌표에서
                    png->width-1         , coor_y);         // png 폭             , 새(新) Y 좌표까지 선을 긋기

        // 그래프 이동을 천천히
        old_y   = coor_y;                                   // 새로 구한 Y 좌표를 old_y 로 대입, 다음 그래프에 사용
        usleep(  100 *1000);
    }
    gx_png_close( png);
    gx_bmp_close( bmp);
}

void draw_wave_with_clear_area( void)
/** ----------------------------------------------------------------------------
    @brief gx_clear_area() 함수를 이용하여 좌로 흐르는 파형 그래프를 출력하는 예제
*/
{
    #define     WAVE_WIDTH      10                          // 파형의 간격
    png_t      *png;                                        // 파형 부분만 그리고 나머지는 투명 영역으로 이용
    bmp_t      *bmp;                                        // 배경 이미지용 bmp
    int         coor_y;                                     // 파형을 그리기 위한 새로 구한 Y 좌표
    int         old_y          = 0;                         // 이전 파형과 연결하여 그리기 위한 이전 Y 좌표
    int         ndx;                                        // 루프를 위한 인덱스

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // 배경에 출력하기 위한 그림을 로딩
    png = gx_png_create( bmp->width, bmp->height);          // 투명 영역을 제공하기 위한 PNG 생성, BMP 크기로
    png->pen_color  = gx_color( 255, 255, 0, 255);          // 파형의 색깔을 노랑색으로

    for( ndx = 0; ndx < 50; ndx++)                          // 파형 출력을 50까지
    {
        coor_y  = rand() %png->height;                      // 난수로 새(新) Y 좌표

        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png 폭 - WAVE_WIDTH, 이전   Y 좌표에서
                    png->width-1         , coor_y);         // png 폭             , 새(新) Y 좌표까지 선을 긋기

        old_y   = coor_y;                                   // 새로 구한 Y 좌표를 old_y 로 대입, 다음 그래프에 사용


        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp를 화면에 출력
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png를 화면에 출력

        // 다음 새(新) 파형을 오른쪽 끝에 그리기 위한 준비를 한다.
        // 참고로 이 과정에는 화면 출력이 없다. 즉, 화면에 변화가 없다
        // png의 오른쪽 부분을 왼쪽으로 이동
        gx_bitblt(  ( dc_t *)png, 0, 0,
                    ( dc_t *)png, WAVE_WIDTH, 0, png->width-WAVE_WIDTH, png->height);

        // 옮기고 남은 오른쪽 나머지 부분을 깨끗이 지운다.
        gx_clear_area( (dc_t *)png,
                        png->width-WAVE_WIDTH, 0,
                        png->width           , png->height,
                        gx_color( 0, 0, 0, 0));
        // 그래프 이동을 천천히
        usleep(  100 *1000);
    }
    gx_png_close( png);
    gx_bmp_close( bmp);
}

int   main( void)
/** ----------------------------------------------------------------------------
    @brief gxLib 사용 예제 메인 함수
*/
{
    if  ( gx_init( "/dev/fb"))                                                  // gxLib 초기화
        gx_print_error( "메인에서 호출");                                       // 실행 중 에러 내용을 출력
    else
    {
        if ( !( dc_screen = gx_get_screen_dc()))                                // 화면 출력을 위한 스크린 DC 구함
            gx_print_error( "메인에서 호출");                                   // 실행 중 에러 내용을 출력
        else
        {
            srand( (unsigned)time(NULL)+(unsigned)getpid());

            view_width  = dc_screen->width;                                     // 화면 폭
            view_height = dc_screen->height;                                    // 화면 높이
            half_width  = view_width  / 2;                                      // 화면 폭의 절반 크기
            half_height = view_height / 2;                                      // 화면 높이의 절반 크기
            center_x    = half_width;                                           // 화면 중앙 x 좌표
            center_y    = half_height;                                          // 화면 중앙 y 좌표

            gx_clear( dc_screen, gx_color( 255, 255, 255, 255));

            test_draw_line();               press_any_key();                    // 선 긋기 테스트
            test_get_set_pixel();           press_any_key();                    // 점 색상 읽기 및 쓰기 테스트
            test_rectangle();               press_any_key();                    // 사각형 그리기 테스트
            test_circle();                  press_any_key();                    // 원 그리기 테스트
            test_ellipse();                 press_any_key();                    // 타원 그리기 테스트
            test_bitmap();                  press_any_key();                    // 비트맵 파일 출력
            test_jpg();                     press_any_key();                    // JPG 파일 출력
            test_png();                     press_any_key();                    // PNG 파일 출력
            test_text();                    press_any_key();
            test_list();                    press_any_key();
            test_mosaic();                  press_any_key();                    // 모자이크 테스트
            test_layer();                                                       // 레이어 테스트
            test_gx_open_file();
            test_bitblt_mask();
            test_gx_get_compatible_dc();    press_any_key();                    // gx_get_compatible_dc() 활용 예
            test_gx_png_create();           press_any_key();
            draw_wave_with_create_png();                                        // 파일 없이 PNG 이미지를 만들어 사용하는 예
            draw_wave_with_clear_area();                                        // 특정 영역을 지우는 gx_clear_area()를 이용하는 예
            gx_release_dc( dc_screen);
        }
        gx_close();
    }
    return   0;
}
