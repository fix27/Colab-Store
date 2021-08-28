echo Author: fix@inbox.ru 
echo donate https://yasobe.ru/na/razvitie_po
echo Start date: 07.04.2020
echo Update date: 07.10.2020
echo https://bintray.com/ookla/download/download_file?file_path=ookla-speedtest-1.0.0-win64.zip
cd ookla-speedtest-1.0.0-win64
echo YES|speedtest.exe
cd ..
cd iperf-3.1.3-win64
iperf3 -c bouygues.iperf.fr -p 9127
iperf3 -c bouygues.iperf.fr -p 9222
iperf3 -c speedtest.serverius.net -p 5002
iperf3 -c iperf.eenet.ee
iperf3 -c iperf.it-north.net -p 5205
iperf3 -c iperf.biznetnetworks.com -p 5201 
iperf3 -c iperf.scottlinux.com -p 5201 	
iperf3 -c iperf.he.net -p 5201 
iperf3 -c rrru.ru
cd..
cd wget-1.21.1-1-win64
wget --tries=1 -O nul --no-check-certificate  https://cache-mskm905.cdn.yandex.net/internetometr.download.cdn.yandex.net/bigfile.png?1111111111111
wget --tries=1 -O nul http://speedtest.tele2.net/100MB.zip
wget --tries=1 -O nul http://speedtest6.tele2.net/100MB.zip
wget --tries=1 -O nul --no-check-certificate  https://speedtest.serverius.net/files/100mb.bin
wget --tries=1 -O nul http://ipv4.download.thinkbroadband.com/100MB.zip
wget --tries=1 -O nul http://ipv6.download.thinkbroadband.com/100MB.zip
wget --tries=1 -O nul http://download.thinkbroadband.com/100MB.zip
wget --tries=1 -O nul http://speedtest-ny.turnkeyinternet.net/100mb.bin
wget --tries=1 -O nul http://speedtest.ftp.otenet.gr/files/test100Mb.db
wget --tries=1 -O nul http://ovh.net/files/100Mio.dat
wget --tries=1 -O nul http://speedcheck.cdn.on.net/100meg.test
wget --tries=1 -O nul http://mirror.filearena.net/pub/speed/SpeedTest_64MB.dat?_ga=2.34952033.1572673891.1586208526-1150274045.1586208526
wget --tries=1 -O nul http://212.183.159.230/100MB.zip
wget --tries=1 -O nul http://speedtest.belwue.net/100M
wget --tries=1 -O nul http://speedtest-sgp1.digitalocean.com/100mb.test
wget --tries=1 -O nul http://speedtest.as5577.net/100mb.bin
wget --tries=1 -O nul http://speedtest.sea01.softlayer.com/downloads/test100.zip
wget --tries=1 -O nul --no-check-certificate https://fastest.fish/lib/downloads/100MB.bin
wget --tries=1 -O nul --no-check-certificate https://speedtest.selectel.ru/100MB
wget --tries=1 -O nul --no-check-certificate https://yandex.ru/internet/
wget --tries=1 -O nul --no-check-certificate https://cache-mskstoredata03.cdn.yandex.net/internetometr.download.cdn.yandex.net/bigfile.png?1586248555096
wget --tries=1 -O nul http://ip.mail.ru/
wget --tries=1 -O nul http://ip.mail.ru/files/2mb.png?rnd=0.34026986463155295&t=&_=1586248874132
wget --tries=1 -O nul http://speedtest.newark.linode.com/100MB-newark.bin
wget --tries=1 -O nul http://speedtest-blr1.digitalocean.com/10mb.test
wget --tries=1 -O nul --no-check-certificate https://mc.yandex.ru/pixel/4436647312949346741?rnd=0.5
wget --tries=1 -O nul --no-check-certificate https://yadi.sk/i/DPZVlvZQHarJBg
echo start count +1
cd ..
PING ipv6.google.com
cd node-v14.16.0-win-x64
if not exist "fast.cmd" (
    echo WARNING
    npm install --global fast-cli
) 
fast -u
echo the end
pause
