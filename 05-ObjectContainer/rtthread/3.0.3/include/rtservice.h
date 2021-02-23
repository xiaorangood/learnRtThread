#ifndef __RT_SERVICE_H__
#define __RT_SERVICE_H__

#include <rtdef.h>

/*******************************************************
 * 初始化链表节点
 *******************************************************/
rt_inline void rt_list_init(rt_list_t *l)
{
    l->next = l->prev = l;
}

/* 在双向链表头部插入一个节点 */
rt_inline void rt_list_insert_after(rt_list_t *l, rt_list_t *n)
{
    n->prev       = l;
    n->next       = l->next;
    n->next->prev = n;
    l->next       = n;
}

/* 在双向链表头部插入一个节点 */
rt_inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
    n->next       = l;
    n->prev       = l->prev;
    l->prev->next = n;
    l->prev       = n;
}

rt_inline void rt_list_remove(rt_list_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;
    n->prev       = n;
    n->next       = n;
}

rt_inline int rt_list_isempty(const rt_list_t *l)
{
    return l->next == l;
}

#endif
