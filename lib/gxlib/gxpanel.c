#include <stdio.h>
#include <stdlib.h>
#include <gx.h>
#include <gxpanel.h>

#define BUFFER_INC_SIZE     10

static void add_invalid( panel_t *panel, int left, int top, int right, int bottom)
{
    if ( 0 > panel->left)
    {
        panel->inv_left     = left;
        panel->inv_top      = top;
        panel->inv_right    = right;
        panel->inv_bottom   = bottom;
    }
    else
    {
        if ( left   < panel->inv_left  )    panel->inv_left     = left  ;
        if ( top    < panel->inv_top   )    panel->inv_top      = top   ;
        if ( right  > panel->inv_right )    panel->inv_right    = right ;      
        if ( bottom > panel->inv_bottom)    panel->inv_bottom   = bottom;      
    }
}

static int is_in_invalid( panel_t *panel, panel_item_t *item)
{
    int     right;
    int     bottom;
    
    right   = item->left +item->dc->width;
    bottom  = item->top  +item->dc->height;
    
    if ( panel->inv_top     > bottom    )       return GX_FALSE;
    if ( panel->inv_left    > right     )       return GX_FALSE;
    if ( panel->inv_right   < item->left)       return GX_FALSE;
    if ( panel->inv_bottom  < item->top )       return GX_FALSE;
        
    return GX_TRUE;             
}
        
void gx_panel_move_to( panel_t *panel, int ndx, int coor_x, int coor_y)
{
    panel_item_t   *item;

    if ( ndx < panel->count)
    {
        item    = panel->items+ndx;                                             // ndx�� �ش��ϴ� �г� ���ϱ�
        
        add_invalid( panel, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        item->left= coor_x;
        item->top = coor_y;        
        add_invalid( panel, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !panel->manual_refresh)  gx_panel_redraw( panel);
    }
}

void gx_panel_move( panel_t *panel, int ndx, int inc_x, int inc_y)
{
    panel_item_t   *item;

    if ( ndx < panel->count)
    {
        item    = panel->items+ndx;        
        add_invalid( panel, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        item->left+= inc_x;
        item->top += inc_y;        
        add_invalid( panel, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !panel->manual_refresh)  gx_panel_redraw( panel);
    }
}

void gx_panel_visible( panel_t *panel, int ndx, int visibled)
{
    panel_item_t   *item;

    if ( ndx < panel->count)
    {
        item    = panel->items+ndx;        
        item->visibled = visibled;
        add_invalid( panel, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !panel->manual_refresh)  gx_panel_redraw( panel);
    }
}

void gx_panel_manual( panel_t *panel, int manual)
{
    panel->manual_refresh = manual;      
}

void gx_panel_redraw( panel_t *panel)
{
    panel_item_t   *item;
    int             ndx;

    if ( 0 > panel->inv_left)
    {
        gx_bitblt( panel->dc_canvas, 0, 0, panel->dc_backgnd, 0, 0, panel->width, panel->height);    // ��� ��ü�� �ٽ� �׸���.
        for ( ndx = panel->count-1; 0 <= ndx; ndx--)                                // ���� �ϴ� �гκ��� �׷� ������.
        {
            item    = panel->items+ndx;        
            if ( GX_TRUE == item->visibled)
            {
                gx_bitblt( ( dc_t *)panel->dc_canvas, item->left, item->top, ( dc_t *)item->dc, 0, 0, item->dc->width, item->dc->height);
            }
        }
        gx_bitblt( panel->dc_output, panel->left, panel->top, panel->dc_canvas, 0, 0, panel->width, panel->height);
    }
    else
    {
        gx_bitblt(  panel->dc_canvas,
                    panel->inv_left, panel->inv_top, 
                    panel->dc_backgnd, 
                    panel->inv_left, panel->inv_top, 
                    panel->inv_right  -panel->inv_left, 
                    panel->inv_bottom -panel->height);
        for ( ndx = panel->count-1; 0 <= ndx; ndx--)                                // ���� �ϴ� �гκ��� �׷� ������.
        {
            item    = panel->items+ndx;        
            if ( GX_TRUE == item->visibled)
            {
                if ( is_in_invalid( panel, item))
                {
                    gx_bitblt( ( dc_t *)panel->dc_canvas, item->left, item->top, ( dc_t *)item->dc, 0, 0, item->dc->width, item->dc->height);
                }
            }
        }
        gx_bitblt(  panel->dc_output, 
                    panel->left+panel->inv_left, panel->top+panel->inv_top, 
                    panel->dc_canvas, 
                    panel->inv_left, panel->inv_top, 
                    panel->inv_right  -panel->inv_left, 
                    panel->inv_bottom -panel->height);
    }        
    panel->inv_left     = -1;
}
                                     
int gx_panel_add( panel_t *panel, dc_t *dc, int left, int top, int visibled)
{         
    if ( ( panel->count+1) == panel->buffer_count)
    {
        panel->buffer_count += BUFFER_INC_SIZE;
        panel->items        = realloc( panel->items, sizeof( panel_item_t) * panel->buffer_count);        
    }                                
    panel->items[panel->count].dc       = dc;
    panel->items[panel->count].left     = left;
    panel->items[panel->count].top      = top;
    panel->items[panel->count].visibled = visibled;
    panel->count++;                

    return panel->count-1;
}

void gx_panel_close( panel_t *panel)
{   
    panel_item_t   *item;
    int             ndx;
              
    gx_release_dc( panel->dc_canvas);
    gx_release_dc( panel->dc_backgnd);
    
    for ( ndx = 0; ndx < panel->count; ndx++)
    {
        item    = panel->items+ndx;        
        gx_release_dc( item->dc);
    }
    free( panel->items);    
    free( panel);
}

panel_t *gx_panel_create ( dc_t *dc, int left, int top, int width, int height)
{         
    panel_t    *panel = NULL;
    
    panel = malloc( sizeof( panel_t));
    if ( NULL != panel)                                                         // �޸� ���ϱ⿡ ����
    {
        panel->items = malloc( sizeof( panel_item_t) *BUFFER_INC_SIZE);         // ���� �ƿ��� ������ ���� �޸� Ȯ��, BUFFER_INC_SIZE: ���۰� ���ڸ� �� �� ���� ������Ű�� ��
        if ( NULL != panel->items)
        {
            panel->dc_canvas = gx_get_buffer_dc( width, height);
            if ( NULL != panel->dc_canvas)
            {
                panel->dc_backgnd = gx_get_compatible_dc( panel->dc_canvas);
                if ( NULL != panel->dc_backgnd)
                {
                    panel->dc_output        = dc;
                    panel->left             = left;
                    panel->top              = top;
                    panel->width            = width;
                    panel->height           = height;
                    panel->manual_refresh   = GX_TRUE;                              // ���� ȭ�� ���� ��� ����
                    panel->count            = 0;                                    // �߰��� ������ ���� Ȯ��
                    panel->buffer_count     = BUFFER_INC_SIZE;                      // �������� ���� �� �ִ� ������ ���� ũ��
                    panel->inv_left         = -1;
                }
                else
                {
                    gx_release_dc( panel->dc_canvas);                               // ������ ĵ������ ����
                    free( panel);     
                    panel   = NULL;
                    printf( "gx_panel_create() : no canvas.\n");        
                }                    
            }
            else
            {
                free( panel);     
                panel   = NULL;
                printf( "gx_panel_create() : no canvas.\n");        
            }                
        }
        else
        { 
            free( panel);     
            panel   = NULL;
            printf( "gx_panel_create() : out of memroy.\n");        
        }    
    }
    else
    {    
        printf( "gx_panel_create() : out of memroy.\n");        
    }    
    return panel;
}
