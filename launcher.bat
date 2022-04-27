
@echo off

rem ******************  MAIN CODE SECTION
set STARTTIME=%TIME%
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

set ENDTIME=%TIME%

rem ******************  END MAIN CODE SECTION

echo ================ Time profiling ==================================
echo.
rem Change formatting for the start and end times
for /F "tokens=1-4 delims=:.," %%a in ("%STARTTIME%") do (
    set /A "start=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100"
)

for /F "tokens=1-4 delims=:.," %%a in ("%ENDTIME%") do ( 
    IF %ENDTIME% GTR %STARTTIME% set /A "end=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100" 
    IF %ENDTIME% LSS %STARTTIME% set /A "end=((((%%a+24)*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100" 
)

rem Calculate the elapsed time by subtracting values
set /A elapsed=end-start

rem Format the results for output
set /A hh=elapsed/(60*60*100), rest=elapsed%%(60*60*100), mm=rest/(60*100), rest%%=60*100, ss=rest/100, cc=rest%%100
if %hh% lss 10 set hh=0%hh%
if %mm% lss 10 set mm=0%mm%
if %ss% lss 10 set ss=0%ss%
if %cc% lss 10 set cc=0%cc%

set DURATION=%hh%:%mm%:%ss%.%cc%

echo Start    : %STARTTIME%
echo Finish   : %ENDTIME%
echo          ---------------
echo Duration : %DURATION% 
echo.
pause
