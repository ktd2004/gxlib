#include <stdio.h>
#include <stdlib.h>
#include <gx.h>
#include <gxlayer.h>

#define BUFFER_INC_SIZE     10

static void add_invalid( layer_t *layer, int left, int top, int right, int bottom)
{
    if ( 0 > layer->left)
    {
        layer->inv_left     = left;
        layer->inv_top      = top;
        layer->inv_right    = right;
        layer->inv_bottom   = bottom;
    }
    else
    {
        if ( left   < layer->inv_left  )    layer->inv_left     = left  ;
        if ( top    < layer->inv_top   )    layer->inv_top      = top   ;
        if ( right  > layer->inv_right )    layer->inv_right    = right ;      
        if ( bottom > layer->inv_bottom)    layer->inv_bottom   = bottom;      
    }
}

static int is_in_invalid( layer_t *layer, layer_item_t *item)
{
    int     right;
    int     bottom;
    
    right   = item->left +item->dc->width;
    bottom  = item->top  +item->dc->height;
    
    if ( layer->inv_top     > bottom    )       return 0;
    if ( layer->inv_left    > right     )       return 0;
    if ( layer->inv_right   < item->left)       return 0;
    if ( layer->inv_bottom  < item->top )       return 0;
        
    return 1;             
}
        
void gx_layer_move_to( layer_t *layer, int ndx, int coor_x, int coor_y)
{
    layer_item_t   *item;

    if ( ndx < layer->count)
    {
        item    = layer->items+ndx;                                             // ndx에 해당하는 레이어 구하기
        
        add_invalid( layer, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        item->left= coor_x;
        item->top = coor_y;        
        add_invalid( layer, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !layer->manual_refresh)  gx_layer_redraw( layer);
    }
}

void gx_layer_move( layer_t *layer, int ndx, int inc_x, int inc_y)
{
    layer_item_t   *item;

    if ( ndx < layer->count)
    {
        item    = layer->items+ndx;        
        add_invalid( layer, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        item->left+= inc_x;
        item->top += inc_y;        
        add_invalid( layer, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !layer->manual_refresh)  gx_layer_redraw( layer);
    }
}

void gx_layer_visible( layer_t *layer, int ndx, int visibled)
{
    layer_item_t   *item;

    if ( ndx < layer->count)
    {
        item    = layer->items+ndx;        
        item->visibled = visibled;
        add_invalid( layer, item->left, item->top, item->left+item->dc->width, item->top+item->dc->height);
        if ( !layer->manual_refresh)  gx_layer_redraw( layer);
    }
}

void gx_layer_manual( layer_t *layer, int manual)
{
    layer->manual_refresh = manual;      
}

void gx_layer_redraw( layer_t *layer)
{
    layer_item_t   *item;
    int             ndx;

    if ( 0 > layer->inv_left)
    {
        for ( ndx = layer->count-1; 0 <= ndx; ndx--)                                // 제일 하단 레이어부터 그려 나간다.
        {
            item    = layer->items+ndx;        
            if ( GX_TRUE == item->visibled)
            {
                gx_bitblt( ( dc_t *)layer->dc_canvas, item->left, item->top, ( dc_t *)item->dc, 0, 0, item->dc->width, item->dc->height);
            }
        }
        gx_bitblt( layer->dc_output, layer->left, layer->top, layer->dc_canvas, 0, 0, layer->width, layer->height);
    }
    else
    {
        for ( ndx = layer->count-1; 0 <= ndx; ndx--)                                // 제일 하단 레이어부터 그려 나간다.
        {
            item    = layer->items+ndx;        
            if ( GX_TRUE == item->visibled)
            {
                if ( is_in_invalid( layer, item))
                {
                    gx_bitblt( ( dc_t *)layer->dc_canvas, item->left, item->top, ( dc_t *)item->dc, 0, 0, item->dc->width, item->dc->height);
                }
            }
        }
        gx_bitblt(  layer->dc_output, 
                    layer->left+layer->inv_left, layer->top+layer->inv_top, 
                    layer->dc_canvas, 
                    layer->inv_left, layer->inv_top, 
                    layer->inv_right  -layer->inv_left, 
                    layer->inv_bottom -layer->height);
    }        
    layer->inv_left     = -1;
}
                                     
int gx_layer_add( layer_t *layer, dc_t *dc, int left, int top, int visibled)
{         
    if ( ( layer->count+1) == layer->buffer_count)
    {
        layer->buffer_count += BUFFER_INC_SIZE;
        layer->items        = realloc( layer->items, sizeof( layer_item_t) * layer->buffer_count);        
    }                                
    layer->items[layer->count].dc       = dc;
    layer->items[layer->count].left     = left;
    layer->items[layer->count].top      = top;
    layer->items[layer->count].visibled = visibled;
    layer->count++;                

    return layer->count-1;
}

void gx_layer_close( layer_t *layer)
{   
    layer_item_t   *item;
    int             ndx;
              
    gx_release_dc( layer->dc_canvas);
    for ( ndx = 0; ndx < layer->count; ndx++)
    {
        item    = layer->items+ndx;        
        gx_release_dc( item->dc);
    }
    free( layer->items);    
    free( layer);
}

layer_t *gx_layer_create ( dc_t *dc, int left, int top, int width, int height)
{         
    layer_t    *layer = NULL;
    
    layer = malloc( sizeof( layer_t));
    if ( NULL != layer)                                                         // 메모리 구하기에 성공
    {
        layer->items = malloc( sizeof( layer_item_t) *BUFFER_INC_SIZE);         // 셀별 아에템 정보를 위한 메모리 확보
        if ( NULL != layer->items)
        {
            layer->dc_canvas = gx_get_buffer_dc( width, height);
            if ( NULL != layer->dc_canvas)
            {
                layer->dc_output        = dc;
                layer->left             = left;
                layer->top              = top;
                layer->width            = width;
                layer->height           = height;
                layer->manual_refresh   = GX_FALSE;                             // 수동 화면 갱신 사용 여부
                layer->count            = 0;                                    // 추가된 아이템 개수 확인
                layer->buffer_count     = BUFFER_INC_SIZE;                      // 아이템을 담을 수 있는 아이템 버퍼 크기
                layer->inv_left         = -1;
            }
            else
            {
                free( layer);     
                gx_error_code  = GXERR_NO_CANVAS;
            }                
        }
        else
        { 
            free( layer);     
            gx_error_code  = GXERR_OUT_OF_MEMORY;
        }    
    }
    else
    {    
        gx_error_code  = GXERR_OUT_OF_MEMORY;
    }    
    return layer;
}
