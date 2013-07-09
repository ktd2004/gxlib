#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <time.h>
#include    <gx.h>

dc_t   *dc_screen;                      // ȭ�� Device Context

int     view_width;                     // ȭ�� ��
int     view_height;                    // ȭ�� ����
int     half_width;                     // ȭ�� ���� ���� ũ��
int     half_height;                    // ȭ�� ������ ���� ũ��
int     center_x;                       // ȭ�� �߾� x ��ǥ
int     center_y;                       // ȭ�� �߾� y ��ǥ

void press_any_key( void)
{
    printf( "press any key......\n");
    getchar();
}

/** ----------------------------------------------------------------------------
    @brief �� �׸��� ����
*/
void test_draw_line( void)
{
    int     ndx;

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));                              // ȭ���� ������� clear

    gx_move_to( dc_screen, rand() % view_width, rand() % view_height);          // ������ ��ǥ�� �̵�
    for ( ndx= 0; ndx < 100; ndx++)                                             // gxline_to()�� �̿��Ͽ� ���� ���� ���� ���
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

    gx_clear( dc_screen, gx_color( 0, 0, 0, 255));                              // ȭ���� ������� clear

    // ȭ���� ���� �� �κп� ������ ���� �׸�
    gx_move_to( dc_screen, rand() % half_width, rand() % view_width);           // ������ ��ǥ�� �̵�
    for ( ndx= 0; ndx < 100; ndx++)
    {
       dc_screen->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
       gx_line_to( dc_screen, rand() % half_width, rand() % view_height);
    }
    // ȭ�� ���� ���� ������ �ݿ� ����
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
        gx_print_error( "bpp-01.bmp");                                         // ���� �� ���� ������ ���
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-04.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-04.bmp");                                         // ���� �� ���� ������ ���
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-08.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-08.bmp");                                         // ���� �� ���� ������ ���
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-24.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-24.bmp");                                         // ���� �� ���� ������ ���
    else
    {
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);
        gx_bmp_close( bmp);
        usleep( 300 *1000);                                                     // 300 msec
    }

    bmp = gx_bmp_open( "bpp-32.bmp");
    if ( NULL == bmp)
        gx_print_error( "bpp-32.bmp");                                         // ���� �� ���� ������ ���
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
        gx_print_error( jpg_name);                                              // ���� �� ���� ������ ���
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
        gx_print_error( "png-08bpp.png");                                       // ���� �� ���� ������ ���
    else
    {
        gx_bitblt( dc_screen, 0, 100, ( dc_t *)png, 0, 0, png->width, png->height);
        gx_png_close( png);
        usleep( 300 *1000);                                                     // 300 msec
    }

    png = gx_png_open( "png-24bpp.png");
    if ( NULL == png)
        gx_print_error( "png-24bpp.png");                                       // ���� �� ���� ������ ���
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
       gx_text_out( dc_screen, 50 , 270, "FALINUX ����!!"  );
    }
}

void test_list( void)
{
    image_list_t  *list;                // �̹��� ����Ʈ ��ü �ڵ�
    png_t         *png_cell;
    int            ndx;

    if ( !( list = gx_imagelist_create( "sample-list.png", 90, 90)))
        gx_print_error( "gx_imagelist_create()");
    else
    {
        for ( ndx = 0; ndx < list->count; ndx++)
        {
                                        // �̹��� ����Ʈ���� �ε����� �ش��ϴ� �̹����� ����
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

                                        // ������ ��ü�� ����

    mosaic = gx_mosaic_create(  (dc_t *)gx_png_open( "fore.png"),               // ��ҿ� ��µǴ� �̹���
                                (dc_t *)gx_png_open( "back.png"),               // ���� ���� ��µ� �̹���
                                (dc_t *)gx_png_open( "color_table.png"),        // ��� ������ �����ϴ� �̹���
                                100, 100);          // ��� ��� DC�� ����� x, y ��ġ

                                        // �̹��� ���� �����ۺ� ��ǥ ������ ���

    gx_mosaic_add( mosaic,  0,  0, 30, 91,                                      // �����ۿ� �ش��ϴ� �̹����� left, top, width, height
                            8, 37);                                             // �ش� �������� ������ ���ϴ� x, y ��ǥ.
    gx_mosaic_add( mosaic, 23,  2, 59, 44, 40, 14);                             // ������ ��ǥ�� ��� ����� �� �ִ�.
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
    png_t      *png;                    // PNG �̹����� �ε��ϱ� ���� ���
    bmp_t      *bmp;                    // BmP �̹����� �ε��ϱ� ���� ���
    layer_t    *layer;                  // ���̾� ��ü
    int         ndx_fish;               // ����� �׸� ���̾� �ε��� ��ȣ
    int         ndx_chimpanzee;         // ħ���� �׸� ���̾� �ε��� ��ȣ
    int         ndx_lft_button;         // ���� ��ư�� ��� �� ���̾� �ε���  ��ȣ
    int         ndx_lft_clicked;        // ���� ��ư�� ������ �� ���̾� �ε��� ��ȣ
    int         ndx_top_button;         // ���� ��ư�� ��� �� ���̾� �ε��� ��ȣ
    int         ndx_top_clicked;        // ���� ��ư�� ������ �� ���̾� �ε��� ��ȣ
    int         ndx_rht_button;         // ������ ��ư�� ��� �� ���̾� �ε��� ��ȣ
    int         ndx_rht_clicked;        // ������ ��ư�� ������ �� ���̾� �ε��� ��ȣ
    int         ndx_btm_button;         // �Ʒ��� ��ư�� ��� �� ���̾� �ε��� ��ȣ
    int         ndx_btm_clicked;        // �Ʒ��� ��ư�� ������ �� ���̾� �ε��� ��ȣ
    int         ndx;

                                        // layer ��ü ����

    layer = gx_layer_create(  dc_screen,            // ��� ��� DC
                              50 ,  25,             // Layer�� Screen ���� ��ġ
                              300, 250);            // Layer�� ���� ����

                                        // ������ �̿��Ͽ� ���̾ �߰�

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
    gx_layer_redraw( layer);                                                    // ���̾� ��ü�� ���
    usleep( 500000);

                                        // ��ư�� �����ϸ鼭 ȭ�鿡 ���, �����̴� ������ �߻�

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

                                        // ��ư�� ��� ���°� ���ص� �������� ���, �������� ����

    gx_layer_manual( layer, GX_TRUE);                                           // ���̾ ��ȭ�� �־ ȭ������ ������� ����. gx_layer)redraw()�� ȣ���� �־�� ��

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

    gx_layer_manual( layer, GX_FALSE);                                  // ���̾ ��ȭ�� ������ �ٷ� ȭ�� ����

                                        // ħ������ ����⸦ �̵�

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

    dc_comp = gx_get_compatible_dc( dc_screen);             // dc_screen�� Ŭ���� ����

    gx_open_file( dc_comp, "bpp-32.bmp");                   // ������ open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_open_file( dc_comp, "jpeg-image.jpg");               // ������ open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_open_file( dc_comp, "png-24bpp.png");                // ������ open
    gx_bitblt( dc_screen, 0, 0, dc_comp, 0, 0, dc_screen->width, dc_screen->height);
    press_any_key();

    gx_release_dc( dc_comp);
}

void test_bitblt_mask( void)
{
    dc_t       *dc_fore;                                                        // ��� ����� �̹���
    dc_t       *dc_back;                                                        // ������ ���õǾ��� �� ����� �̹���
    dc_t       *dc_mask;                                                        // mask �̹���

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
    @brief dc_screen�� ����ϱ� ���� dc_screen�� ���纻�� ����� ����, ���纻�� ����� ��� ó���� �Ŀ� �ѹ��� ȭ������ ���. test_gx_png_create() �ʹ� �޸� ȭ�� �������� ����.
*/
{
    dc_t       *scr;                                        // dc_screen �� Ŭ��
    png_t      *png;                                        // ���� �κи� �׸��� �������� ���� �������� �̿�
    bmp_t      *bmp;                                        // ��� �̹����� bmp
    int         loop;
    int         ndx;                                        // ������ ���� �ε���

    scr = gx_get_compatible_dc( dc_screen);                 // dc_screen�� Ŭ���� ����
    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // ��濡 ����ϱ� ���� �׸��� �ε�
    png = gx_png_create( bmp->width, bmp->height);          // ���� ������ �����ϱ� ���� PNG ����, BMP ũ���

    // ȭ�鿡 BMP ���� ���� �ߴ� ���� 10ȸ �ݺ�
    for ( loop = 0; loop < 10; loop++)
    {
        gx_clear( ( dc_t *)png, gx_color( 0, 0, 0, 0));

        // ������ �̿��Ͽ� ���� ���� ������ PNG �� �׷��� PNG�� �ϼ�

        gx_move_to( ( dc_t *)png, rand() % png->width, rand() % png->height);   // ������ Ư�� ��ǥ�� �̵�
        for ( ndx = 0; ndx < 50; ndx++)
        {
           png->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
           gx_line_to( (dc_t *)png, rand() % png->width, rand() % png->height);
        }

        // ȭ�鿡 ����� ��� ������ �켱 scr�� ���
        gx_clear ( scr, gx_color( 0, 0, 0, 255));                             // ȭ���� �����ϰ� ����
        gx_bitblt( scr, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp�� ȭ�鿡 ���
        gx_bitblt( scr, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png�� ȭ�鿡 ���

        // ��� �׷��� scr�� �ѹ��� ȭ������ ���. test_gx_png_create()�ʹ� �޸� �������� ����
        gx_bitblt( dc_screen, 0, 0, scr, 0, 0, scr->width, scr->height);

        // 0.5�ʰ� ���
        usleep( 500 * 1000);
    }

    gx_png_close( png);
    gx_bmp_close( bmp);
    gx_release_dc( scr);
}

void test_gx_png_create( void)
/** ----------------------------------------------------------------------------
    @brief PNG�� ���Ͼ��� �����Ͽ� �������� �̿��ϴ� ���� ������
*/
{
    png_t      *png;                                        // ���� �κи� �׸��� �������� ���� �������� �̿�
    bmp_t      *bmp;                                        // ��� �̹����� bmp
    int         loop;
    int         ndx;                                        // ������ ���� �ε���

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // ��濡 ����ϱ� ���� �׸��� �ε�
    png = gx_png_create( bmp->width, bmp->height);          // ���� ������ �����ϱ� ���� PNG ����, BMP ũ���

    // ȭ�鿡 BMP ���� ���� �ߴ� ���� 10ȸ �ݺ�
    for ( loop = 0; loop < 10; loop++)
    {
        gx_clear( ( dc_t *)png, gx_color( 0, 0, 0, 0));         //

        // ������ �̿��Ͽ� ���� ���� ������ PNG �� �׷��� PNG�� �ϼ�

        gx_move_to( ( dc_t *)png, rand() % png->width, rand() % png->height);   // ������ Ư�� ��ǥ�� �̵�
        for ( ndx = 0; ndx < 50; ndx++)
        {
           png->pen_color  = gx_color( rand() %128 +128, rand() %128 +128, rand() %128 +128, 255);
           gx_line_to( (dc_t *)png, rand() % png->width, rand() % png->height);
        }

        // ȭ�鿡 ��� BMP�� ����ϰ�, �ٽ� �� ���� ������ �׷��� �ִ� PNG�� ���
        gx_clear ( dc_screen, gx_color( 0, 0, 0, 255));                             // ȭ���� �����ϰ� ����
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp�� ȭ�鿡 ���
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png�� ȭ�鿡 ���

        // 0.5�ʰ� ���
        usleep( 500 * 1000);
    }

    gx_png_close( png);
    gx_bmp_close( bmp);
}
/** ----------------------------------------------------------------------------
    @brief PNG�� ���� ������ �̿��Ͽ� �·� �帣�� ���� �׷����� ����ϴ� ����
*/
void draw_wave_with_create_png( void)
{
    #define     WAVE_WIDTH      10                          // ������ ����
    png_t      *png;                                        // ���� �κи� �׸��� �������� ���� �������� �̿�
    bmp_t      *bmp;                                        // ��� �̹����� bmp
    int         coor_y;                                     // ������ �׸��� ���� ���� ���� Y ��ǥ
    int         old_y          = 0;                         // ���� ������ �����Ͽ� �׸��� ���� ���� Y ��ǥ
    int         ndx;                                        // ������ ���� �ε���

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // ��濡 ����ϱ� ���� �׸��� �ε�
    png = gx_png_create( bmp->width, bmp->height);          // ���� ������ �����ϱ� ���� PNG ����, BMP ũ���

    for( ndx = 0; ndx < 50; ndx++)                          // ���� ����� 50����
    {
        coor_y  = rand() %png->height;                      // ������ ��(��) Y ��ǥ

        png->pen_color  = gx_color( 255, 255, 0, 255);
        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png �� - WAVE_WIDTH, ����   Y ��ǥ����
                    png->width-1         , coor_y);         // png ��             , ��(��) Y ��ǥ���� ���� �߱�


        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp�� ȭ�鿡 ���
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png�� ȭ�鿡 ���


        // ���� ��(��) ������ ������ ���� �׸��� ���� �غ� �Ѵ�.
        // ����� �� �������� ȭ�� ����� ����. ��, ȭ�鿡 ��ȭ�� ����
        // png�� ������ �κ��� �������� �̵�
        gx_bitblt(  ( dc_t *)png, 0, 0,
                    ( dc_t *)png, WAVE_WIDTH, 0, png->width-WAVE_WIDTH, png->height);

        // �ű� �Ŀ� ���� �׸� ���� ��������� �ٽ� �׷� �����
        png->pen_color  = gx_color( 0, 0, 0, 0);
        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png �� - WAVE_WIDTH, ����   Y ��ǥ����
                    png->width-1         , coor_y);         // png ��             , ��(��) Y ��ǥ���� ���� �߱�

        // �׷��� �̵��� õõ��
        old_y   = coor_y;                                   // ���� ���� Y ��ǥ�� old_y �� ����, ���� �׷����� ���
        usleep(  100 *1000);
    }
    gx_png_close( png);
    gx_bmp_close( bmp);
}

void draw_wave_with_clear_area( void)
/** ----------------------------------------------------------------------------
    @brief gx_clear_area() �Լ��� �̿��Ͽ� �·� �帣�� ���� �׷����� ����ϴ� ����
*/
{
    #define     WAVE_WIDTH      10                          // ������ ����
    png_t      *png;                                        // ���� �κи� �׸��� �������� ���� �������� �̿�
    bmp_t      *bmp;                                        // ��� �̹����� bmp
    int         coor_y;                                     // ������ �׸��� ���� ���� ���� Y ��ǥ
    int         old_y          = 0;                         // ���� ������ �����Ͽ� �׸��� ���� ���� Y ��ǥ
    int         ndx;                                        // ������ ���� �ε���

    bmp = gx_bmp_open  ( "bpp-16.bmp");                     // ��濡 ����ϱ� ���� �׸��� �ε�
    png = gx_png_create( bmp->width, bmp->height);          // ���� ������ �����ϱ� ���� PNG ����, BMP ũ���
    png->pen_color  = gx_color( 255, 255, 0, 255);          // ������ ������ ���������

    for( ndx = 0; ndx < 50; ndx++)                          // ���� ����� 50����
    {
        coor_y  = rand() %png->height;                      // ������ ��(��) Y ��ǥ

        gx_line( ( dc_t *)png,
                    png->width-WAVE_WIDTH, old_y,           // png �� - WAVE_WIDTH, ����   Y ��ǥ����
                    png->width-1         , coor_y);         // png ��             , ��(��) Y ��ǥ���� ���� �߱�

        old_y   = coor_y;                                   // ���� ���� Y ��ǥ�� old_y �� ����, ���� �׷����� ���


        gx_bitblt( dc_screen, 0, 0, ( dc_t *)bmp, 0, 0, bmp->width, bmp->height);   // bmp�� ȭ�鿡 ���
        gx_bitblt( dc_screen, 0, 0, ( dc_t *)png, 0, 0, png->width, png->height);   // png�� ȭ�鿡 ���

        // ���� ��(��) ������ ������ ���� �׸��� ���� �غ� �Ѵ�.
        // ����� �� �������� ȭ�� ����� ����. ��, ȭ�鿡 ��ȭ�� ����
        // png�� ������ �κ��� �������� �̵�
        gx_bitblt(  ( dc_t *)png, 0, 0,
                    ( dc_t *)png, WAVE_WIDTH, 0, png->width-WAVE_WIDTH, png->height);

        // �ű�� ���� ������ ������ �κ��� ������ �����.
        gx_clear_area( (dc_t *)png,
                        png->width-WAVE_WIDTH, 0,
                        png->width           , png->height,
                        gx_color( 0, 0, 0, 0));
        // �׷��� �̵��� õõ��
        usleep(  100 *1000);
    }
    gx_png_close( png);
    gx_bmp_close( bmp);
}

int   main( void)
/** ----------------------------------------------------------------------------
    @brief gxLib ��� ���� ���� �Լ�
*/
{
    if  ( gx_init( "/dev/fb"))                                                  // gxLib �ʱ�ȭ
        gx_print_error( "���ο��� ȣ��");                                       // ���� �� ���� ������ ���
    else
    {
        if ( !( dc_screen = gx_get_screen_dc()))                                // ȭ�� ����� ���� ��ũ�� DC ����
            gx_print_error( "���ο��� ȣ��");                                   // ���� �� ���� ������ ���
        else
        {
            srand( (unsigned)time(NULL)+(unsigned)getpid());

            view_width  = dc_screen->width;                                     // ȭ�� ��
            view_height = dc_screen->height;                                    // ȭ�� ����
            half_width  = view_width  / 2;                                      // ȭ�� ���� ���� ũ��
            half_height = view_height / 2;                                      // ȭ�� ������ ���� ũ��
            center_x    = half_width;                                           // ȭ�� �߾� x ��ǥ
            center_y    = half_height;                                          // ȭ�� �߾� y ��ǥ

            gx_clear( dc_screen, gx_color( 255, 255, 255, 255));

            test_draw_line();               press_any_key();                    // �� �߱� �׽�Ʈ
            test_get_set_pixel();           press_any_key();                    // �� ���� �б� �� ���� �׽�Ʈ
            test_rectangle();               press_any_key();                    // �簢�� �׸��� �׽�Ʈ
            test_circle();                  press_any_key();                    // �� �׸��� �׽�Ʈ
            test_ellipse();                 press_any_key();                    // Ÿ�� �׸��� �׽�Ʈ
            test_bitmap();                  press_any_key();                    // ��Ʈ�� ���� ���
            test_jpg();                     press_any_key();                    // JPG ���� ���
            test_png();                     press_any_key();                    // PNG ���� ���
            test_text();                    press_any_key();
            test_list();                    press_any_key();
            test_mosaic();                  press_any_key();                    // ������ũ �׽�Ʈ
            test_layer();                                                       // ���̾� �׽�Ʈ
            test_gx_open_file();
            test_bitblt_mask();
            test_gx_get_compatible_dc();    press_any_key();                    // gx_get_compatible_dc() Ȱ�� ��
            test_gx_png_create();           press_any_key();
            draw_wave_with_create_png();                                        // ���� ���� PNG �̹����� ����� ����ϴ� ��
            draw_wave_with_clear_area();                                        // Ư�� ������ ����� gx_clear_area()�� �̿��ϴ� ��
            gx_release_dc( dc_screen);
        }
        gx_close();
    }
    return   0;
}
