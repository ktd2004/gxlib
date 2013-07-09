#ifndef _GX_LAYER_H_
#define _GX_LAYER_H_

typedef struct layer_t_ layer_t;

typedef struct
{
    dc_t           *dc;             // ���̾ ������ �ִ� Device Context
    int             left;           // ���̾��� ��ġ
    int             top;            // ���̾��� ��ġ
    int             visible;        // ���̾� ��� ����
    int             invalid;        // ȭ�� ���� ����
} layer_item_t;

struct layer_t_
{                           
    layer_item_t   *items;          // ���̾� ������ ���
    int             count;          // �߰��� ���̾� ����    
    int             buffer_count;   // ���̾ �߰��ϱ� ���� ������ ���� ũ��
};

typedef struct 
{                           
    int     left;
    int     top;
    int     right;
    int     bottom;
} layer_rect_t;


// ���̾ ����
extern layer_t  *gx_layer_create( void);
// ���̾ �Ҹ�
extern void      gx_layer_close( layer_t *layer);
// ���ο� ���̾ �߰�
extern int       gx_layer_add( layer_t *layer, dc_t *dc, int left, int top, int visible);
// Ư�� ���̾��� visible �Ӽ��� ����
extern void      gx_layer_visible( layer_t *layer, int ndx, int visible);
// ���̾� ��ü�� ���� DC�� ���
extern void      gx_layer_redraw( dc_t *dc_target, dc_t *dc_canvas, layer_t *layer);
// ���̾� ��ü�� ���� DC�� ���
extern void      gx_layer_draw( dc_t *dc_target, dc_t *dc_canvas, layer_t *layer);
// ���̾ ���� DC�� ���Ѵ�.
extern dc_t     *gx_layer_get_dc( layer_t *layer, int ndx_layer);
// ���̾ ���� ���� �������� �����Ѵ�.
extern void      gx_layer_invalid( layer_t *layer, int ndx_layer);

#endif
