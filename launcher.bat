
@echo off
python clear_dat.py
echo.
echo                       3x3 Median Filter      
echo                SKEL4673-01: DSP Architectures      
echo                           Group 4
echo.
echo ================ Converting image to greyscale ===================
echo.
python img_to_dat.py
echo.
echo ================ Applying filter =================================
echo.
g++ 3x3_median_filter.cpp -o 3x3_median_filter.exe 
3x3_median_filter.exe
del 3x3_median_filter.exe
echo.
echo ================ Converting processed data to PNG ================
echo.
python dat_to_img.py
echo.
pause