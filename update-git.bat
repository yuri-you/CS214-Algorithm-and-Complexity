@echo off
set name=lab
set /p name=please input commit name:
git add .
git commit -m %name%
git push origin master
@echo finished
pause
