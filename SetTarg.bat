set location=C:\U4L\P
set projectname=CPP_FLY
set projectdirname=CPP_FLY
set projectdir=%location%\%projectdirname%
set sniploc=C:\U4L\snip\
set TargUtil=%sniploc%SetTargUtil.bat
set ModePostfix=_Main
start /B %TargUtil% %projectname% %projectdir% %ModePostfix%
