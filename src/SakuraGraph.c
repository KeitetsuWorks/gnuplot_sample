/**
 * @file        SakuraGraph.c
 * @brief       桜形グラフのデータ作成
 * @author      Keitetsu
 * @date        2013/09/21
 * @copyright   Copyright (c) 2013 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LinkedList.h"

#include "SakuraGraph.h"


/**
 * @brief   X座標を計算する
 * @param[in]       theta           角度（ラジアン）
 * @return          X座標
 */
static double SakuraGraph_calcX(double theta);


/**
 * @brief   Y座標を計算する
 * @param[in]       theta           角度（ラジアン）
 * @return          Y座標
 */
static double SakuraGraph_calcY(double theta);


/**
 * @brief   グラフ座標データを作成する
 * @param[in]       x               X座標
 * @param[in]       y               Y座標
 * @retval          NULL            グラフ座標データの作成に失敗
 * @retval          Others          作成したグラフ座標データのポインタ
 */
static GRAPH_COORD_T *SakuraGraph_createGraphCoord(double x, double y);


static double SakuraGraph_calcX(double theta)
{
    double x;

    x = cos(theta) * (1 + 0.5 * sin(5 * theta) + 0.3 * cos(10 * theta));

    return x;
}


static double SakuraGraph_calcY(double theta)
{
    double y;

    y = sin(theta) * (1 + 0.5 * sin(5 * theta) + 0.3 * cos(10 * theta));

    return y;
}


static GRAPH_COORD_T *SakuraGraph_createGraphCoord(double x, double y)
{
    GRAPH_COORD_T *coord;
    
    coord = (GRAPH_COORD_T *)malloc(sizeof(GRAPH_COORD_T));
    if (coord != NULL) {
        coord->x = x;
        coord->y = y;
    }
    
    return coord;
}


GRAPH_T *SakuraGraph_createGraphData(double delta_deg)
{
    GRAPH_T *graph_head;
    double deg;
    double rad;
    GRAPH_COORD_T *coord;

    graph_head = NULL;
    
    for (deg = 0.0; deg < 360.0; deg += delta_deg) {
        rad = deg * (M_PI / 180.0);
        coord = SakuraGraph_createGraphCoord(
                SakuraGraph_calcX(rad),
                SakuraGraph_calcY(rad));
        
        if (graph_head == NULL) {
            graph_head = LinkedList_createList(coord);
        }
        else {
            LinkedList_addElementTail(graph_head, coord);
        }
    }

    return graph_head;
}


void SakuraGraph_printGraphCoord(void *object)
{
    GRAPH_COORD_T *coord;
    
    coord = (GRAPH_COORD_T *)object;
    printf("(x, y) = (%f, %f)\n", coord->x, coord->y);

    return;
}


void SakuraGraph_printGraphData(GRAPH_T *graph_head)
{
    LinkedList_showList(graph_head, SakuraGraph_printGraphCoord);

    return;
}


int SakuraGraph_saveGraphDataToFile(GRAPH_T *graph_head, char *csv_fname)
{
    FILE *csv_fp;
    GRAPH_T *graph_tmp;
    GRAPH_T *graph_tail;

    csv_fp = fopen(csv_fname, "w");
    if (csv_fp == NULL) {
        printf("Error:  failed to open CSV file: %s\n", csv_fname);

        return 1;
    }

    graph_tail = graph_head->prev;
    graph_tmp = graph_head;
    while (1) {
        fprintf(
                csv_fp,
                "%f,%f\n",
                ((GRAPH_COORD_T *)(graph_tmp->object))->x,
                ((GRAPH_COORD_T *)(graph_tmp->object))->y);

        if (graph_tmp == graph_tail) {
            break;
        }
        else {
            graph_tmp = graph_tmp->next;
        }
    }

    fclose(csv_fp);

    return 0;
}


GRAPH_T *SakuraGraph_eraseGraphData(GRAPH_T *graph_head)
{
    graph_head = LinkedList_eraseList(graph_head);
    
    return graph_head;
}

