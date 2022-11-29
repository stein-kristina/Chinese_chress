需要软件：python

1、打开文件夹，找到.exe文件所在路径，把路径复制。
2、然后打开cmd，输入下面两行（目录就是那个路径）
	cd 目录
	python -m serv 文件名（有easy跟hard两个难度）
3、最后打开浏览器，在地址栏输入localhost即可

win11：由于localhost默认端口80被占用，请在serv\_main_.py 里修改port_为81，
	再在浏览器地址栏输入localhost:81即可