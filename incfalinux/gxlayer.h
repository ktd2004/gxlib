#ifndef _GX_LAYER_H_
#define _GX_LAYER_H_

typedef struct layer_t_ layer_t;

typedef struct
{
    dc_t           *dc;             // ���̾ ������ �ִ� Device Context
    int             left;           // ���̾��� ��ġ
    int             top;            // ���̾��� ��ġ
    int             visibled;       // ���̾� ��� ����
} layer_item_t;

struct layer_t_
{                           
    dc_t           *dc_output;      // ��� ��� Device Context
    dc_t           *dc_canvas;      // ���̾��� ��ü ��� Device Context
    layer_item_t   *items;          // ���̾� ������ ���
    int             left;           // ���̾ dc_output������ ��ġ
    int             top;            // ���̾ dc_output������ ��ġ
    int             width;          // ���̾��� ��
    int             height;         // ���̾��� ����
    int             inv_left;       // ���� �ʿ� ���� left
    int             inv_top;        // ���� �ʿ� ���� top
    int             inv_right;      // ���� �ʿ� ���� right
    int             inv_bottom;     // ���� �ʿ� ���� bottom
    int             count;          // �߰��� ���̾� ����    
    int             buffer_count;   // ���̾ �߰��ϱ� ���� ������ ���� ũ��
    int             manual_refresh; // ���̾ ������ ���� ��, �ڵ����� ȭ������ ��������� ����
};

// ���̾ ����
extern layer_t  *gx_layer_create ( dc_t *dc, int left, int top, int width, int height);
// ���̾ �Ҹ�
extern void      gx_layer_close( layer_t *layer);
// ���ο� ���̾ �߰�
extern int       gx_layer_add( layer_t *layer, dc_t *dc, int left, int top, int visibled);
// ��ü ���̾ ȭ�鿡 ���
extern void      gx_layer_redraw( layer_t *layer);
// Ư�� ���̾��� visible �Ӽ��� ����
extern void      gx_layer_visible( layer_t *layer, int ndx, int visibled);
// Ư�� ���̾��� ��ġ�� ���ϱ� ������ �̵�
extern void      gx_layer_move( layer_t *layer, int ndx, int inc_x, int inc_y);
// Ư�� ���̾��� ��ġ�� ������ ��ǥ�� �̵�
extern void      gx_layer_move_to( layer_t *layer, int ndx, int coor_x, int coor_y);
// ���̾� ����� ���� �Ǵ� �ڵ����� ����
extern void      gx_layer_manual( layer_t *layer, int manual);

#endif
