@echo off

cd prj_win32
call compile.bat %1
cd..

cd..
cd..
cd t3-venus\TPadMainCtrlPlat\loadtpad
call compile.bat %1
cd..
cd loadnewtpad
call compile.bat %1
cd..
cd..
cd..
cd t5-neith\tpad

call setup.bat %1

@echo on
