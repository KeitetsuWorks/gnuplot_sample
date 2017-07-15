##
## @file        SakuraGraph.plt
## @brief       gnuplot script for Sakura Graph
## @author      Keitetsu
## @date        2013/09/21
## @copyright   Copyright (c) 2013 Keitetsu
## @par         License
##              This software is released under the MIT License.
##

# 入力ファイル設定
set datafile separator ","


# グラフ表示設定
set title "Sakura Graph" font "Helvetica,9"

set key font "Helvetica,9"

set xlabel "x" font "Helvetica,9"
set format x "%.1f"
set xrange[-1.5:1.5]
set xtics 0.5
set mxtics 2

set ylabel "y" font "Helvetica,9"
set format y "%.1f"
set yrange[-1.5:1.5]
set ytics 0.5
set mytics 2


# グラフ描画
plot "SakuraGraph.csv" using 1:2 with lines linewidth 1 title "Sakura"


# グラフ画像保存
set terminal png
set output "SakuraGraph.png"
replot

