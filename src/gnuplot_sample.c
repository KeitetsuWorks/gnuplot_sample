/**
 * @file        gnuplot_sample.c
 * @brief       gnuplotによるグラフ描画のサンプルプログラム
 * @author      Keitetsu
 * @date        2013/09/21
 * @copyright   Copyright (c) 2013 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "SakuraGraph.h"


/**
 * @brief   メイン関数
 * @retval          EXIT_SUCCESS    正常終了
 * @retval          EXIT_FAILURE    異常終了
 */
int main(int argc, char *argv[])
{
    int opt, optlong_index;
    struct option longopts[] = {
        { "delta",      required_argument,  NULL,   'd' },
        { "output",     required_argument,  NULL,   'o' },
        { "plot",       optional_argument,  NULL,   'p' },
        { "show",       no_argument,        NULL,   's' },
        { 0,            0,                  0,      0   }
    };

    int flag_error;
    int flag_plot;
    int flag_show;
    
    GRAPH_T *SakuraGraph;
    double delta_deg;
    
    char *csv_fname;
    const char *csv_fname_default = "SakuraGraph.csv";
    
    char *gnuplot_scr_fname;
    const char *gnuplot_scr_fname_default = "SakuraGraph.plt";
    
    FILE *gnuplot_fp;
    char *gnuplot_cmd;
    int gnuplot_retval;
    int retval;


    flag_error = 0;
    flag_plot = 0;
    flag_show = 0;

    SakuraGraph = NULL;
    delta_deg = 0.01;

    csv_fname = NULL;
    gnuplot_scr_fname = NULL;

    gnuplot_fp = NULL;
    gnuplot_cmd = NULL;


    while (flag_error == 0) {
        opt = getopt_long(argc, argv, "d:o:p::s", longopts, &optlong_index);
        if (opt == -1) {
            break;
        }
        
        switch(opt) {
            case 'd':
                delta_deg = atof(optarg);
                printf("Info:   delta degree: %f\n", delta_deg);
                break;
            case 'o':
                csv_fname = strdup(optarg);
                printf("Info:   CSV file: %s\n", csv_fname);
                break;
            case 'p':
                flag_plot = 1;
                if (optarg != 0) {
                    gnuplot_scr_fname = strdup(optarg);
                }
                else {
                    gnuplot_scr_fname = strdup(gnuplot_scr_fname_default);
                }
                printf("Info:   gnuplot script file: %s\n", gnuplot_scr_fname);
                break;
            case 's':
                flag_show = 1;
                break;
            default:
                flag_error = 1;
                printf("Error:  invalid argument\n");
                break;
        }
    }

    if (flag_error != 0) {
        free(csv_fname);
        free(gnuplot_scr_fname);

        exit(EXIT_FAILURE);
    }

    if (csv_fname == NULL) {
        csv_fname = strdup(csv_fname_default);
    }


    /* 桜形グラフのデータ作成 */
    SakuraGraph = SakuraGraph_createGraphData(delta_deg);
    
    if (flag_show != 0) {
        SakuraGraph_printGraphData(SakuraGraph);
    }
    
    SakuraGraph_saveGraphDataToFile(SakuraGraph, csv_fname);
    free(csv_fname);
    
    SakuraGraph_eraseGraphData(SakuraGraph);


    /* gnuplotによるグラフ描画 */
    if (flag_plot != 0) {
        retval = asprintf(&gnuplot_cmd, "gnuplot -persist %s", gnuplot_scr_fname);
        if (retval == -1) {
            flag_error = 1;
            printf("Error:  unexpected error\n");
        }
        else {
            gnuplot_fp = popen(gnuplot_cmd, "w");
            
            fflush(gnuplot_fp);
            
            gnuplot_retval = pclose(gnuplot_fp);
            if (gnuplot_retval != 0) {
                flag_error = 1;
                printf("Error:  gnuplot error: %d\n", gnuplot_retval);
            }
            
            free(gnuplot_cmd);
        }
        
        free(gnuplot_scr_fname);
    }


    if (flag_error != 0) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

