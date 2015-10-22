#!/bin/sh
echo Usage: ./total_shader_make.sh YYY.png YYY.fra
DATA=output/test_data
MODEL=output/test_model
./gp_color_table_data_make.out ./filter_standard.png $1 $DATA 
./abs_model_simple3d.out $DATA $MODEL 
./turnModelToGLSL.py $MODEL $2
