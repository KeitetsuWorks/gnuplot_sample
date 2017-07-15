/**
 * @file        SakuraGraph.h
 * @brief       桜形グラフのデータ作成
 * @author      Keitetsu
 * @date        2013/09/21
 * @copyright   Copyright (c) 2013 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    /* __SAKURAGRAPH_H__ */


#include "LinkedList.h"


/**
 * @typedef GRAPH_T
 * @brief   グラフデータリスト構造体
 */
typedef LIST_ELEMENT_T GRAPH_T;


/**
 * @struct  graph_coord_st
 * @brief   グラフ座標データ構造体
 *
 * @typedef GRAPH_COORD_T
 * @brief   グラフ座標データ構造体
 */
typedef struct graph_coord_st {
    double x;       /*!< X座標 */
    double y;       /*!< Y座標 */
} GRAPH_COORD_T;


/**
 * @brief   グラフデータを作成する
 * @param[in]       delta_deg       角度の刻み幅
 * @retval          NULL            グラフデータリストの作成に失敗
 * @retval          Others          グラフデータリストの先頭要素のポインタ
 */
GRAPH_T *SakuraGraph_createGraphData(double delta_deg);


/**
 * @brief   グラフ座標データを表示する
 * @param[in]       object          グラフ座標データのポインタ
 */
void SakuraGraph_printGraphCoord(void *object);


/**
 * @brief   グラフデータを表示する
 * @param[in]       graph_head      グラフデータリストの先頭要素のポインタ
 */
void SakuraGraph_printGraphData(GRAPH_T *graph_head);


/**
 * @brief   グラフデータをファイルに保存する
 * @param[in]       graph_head      グラフデータリストの先頭要素のポインタ
 * @param[in]       csv_fname       ファイル名
 */
int SakuraGraph_saveGraphDataToFile(GRAPH_T *graph_head, char *csv_fname);


/**
 * @brief   グラフデータを消去する
 * @param[in]       graph_head      グラフデータリストの先頭要素のポインタ
 * @retval          NULL            グラフデータリストの消去に成功
 * @retval          Others          グラフデータリストの消去に失敗
 */
GRAPH_T *SakuraGraph_eraseGraphData(GRAPH_T *graph_head);

