#ifndef __GXBDF_H__
#define __GXBDF_H__

/// ��Ʈ�� ����ϱ� ���� ���⸦ �Ѵ�.
extern font_t *gx_open_font( char *font_filename);
/// DC�� ��Ʈ�� �����Ѵ�.
extern void gx_set_font( dc_t *dc, font_t *font);
/// DC�� ���ڿ��� ����Ѵ�. * ����: coo_y�� ���ڿ� ����� �ϴ� ��ǥ. ��, coor_x=���� ��ǥ, coor_y=�ϴ� ��ǥ
extern int gx_text_out( dc_t *dc, int coor_x, int coor_y, char *text);

#endif
