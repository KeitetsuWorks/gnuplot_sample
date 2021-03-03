/**
 * @file        LinkedList.h
 * @brief       連結リスト管理
 * @author      Keitetsu
 * @date        2013/09/21
 * @copyright   Copyright (c) 2013 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    /* __LINKEDLIST_H__ */


/**
 * @struct  list_element_st
 * @brief   連結リスト要素構造体
 *
 * @typedef LIST_ELEMENT_T
 * @brief   連結リスト要素構造体
 */
typedef struct list_element_st {
    void *object;                   /**< 要素データのポインタ */
    struct list_element_st *prev;   /**< 前の要素のポインタ */
    struct list_element_st *next;   /**< 次の要素のポインタ */
} LIST_ELEMENT_T;


/**
 * @brief   連結リストを作成する
 * @param[in]       object          要素データのポインタ
 * @retval          NULL            連結リストの作成に失敗
 * @retval          Others          連結リストの先頭要素のポインタ
 */
LIST_ELEMENT_T *LinkedList_createList(
        void *object);


/**
 * @brief   連結リスト要素を作成する
 * @param[in]       object          要素データのポインタ
 * @retval          NULL            連結リスト要素の作成に失敗
 * @retval          Others          作成した連結リスト要素のポインタ
 */
LIST_ELEMENT_T *LinkedList_createElement(
        void *object);


/**
 * @brief   連結リスト要素を作成し、連結リスト終端に追加する
 * @param[in]       head            連結リストの先頭要素のポインタ
 * @param[in]       object          要素データのポインタ
 * @retval          NULL            連結リスト要素の作成に失敗
 * @retval          Others          作成した連結リスト要素のポインタ
 */
LIST_ELEMENT_T *LinkedList_addElementTail(
        LIST_ELEMENT_T *head,
        void *object);


/**
 * @brief   連結リストの全要素データを表示する
 * @param[in]       head            連結リストの先頭要素のポインタ
 * @param[in]       show            要素データ表示関数の関数ポインタ
 */
void LinkedList_showList(
        LIST_ELEMENT_T *head,
        void (*show)(void *));


/**
 * @brief   連結リストを消去する
 * @param[in]       head            連結リストの先頭要素のポインタ
 * @retval          NULL            連結リストの消去に成功
 * @retval          Others          連結リストの消去に失敗
 */
LIST_ELEMENT_T *LinkedList_eraseList(
        LIST_ELEMENT_T *head);

