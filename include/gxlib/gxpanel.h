#ifndef __GX_PANEL_H__
#define __GX_PANEL_H__

typedef struct panel_t_ panel_t;

typedef struct
{
    dc_t           *dc;             // ���̾ ������ �ִ� Device Context
    int             left;           // ���̾��� ��ġ
    int             top;            // ���̾��� ��ġ
    int             visibled;       // ���̾� ��� ����
} panel_item_t;

struct panel_t_
{                           
    dc_t           *dc_output;      // ��� ��� Device Context
    dc_t           *dc_canvas;      // ���̾��� ��ü ��� Device Context
    dc_t           *dc_backgnd;     // ���̾��� ��ü ��� Device Context
    panel_item_t   *items;          // ���̾� ������ ���
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
extern panel_t  *gx_panel_create ( dc_t *dc, int left, int top, int width, int height);
// ���̾ �Ҹ�
extern void      gx_panel_close( panel_t *panel);
// ���ο� ���̾ �߰�
extern int       gx_panel_add( panel_t *panel, dc_t *dc, int left, int top, int visibled);
// ��ü ���̾ ȭ�鿡 ���
extern void      gx_panel_redraw( panel_t *panel);
// Ư�� ���̾��� visible �Ӽ��� ����
extern void      gx_panel_visible( panel_t *panel, int ndx, int visibled);
// Ư�� ���̾��� ��ġ�� ���ϱ� ������ �̵�
extern void      gx_panel_move( panel_t *panel, int ndx, int inc_x, int inc_y);
// Ư�� ���̾��� ��ġ�� ������ ��ǥ�� �̵�
extern void      gx_panel_move_to( panel_t *panel, int ndx, int coor_x, int coor_y);
// ���̾� ����� ���� �Ǵ� �ڵ����� ����
extern void      gx_panel_manual( panel_t *panel, int manual);

#endif
