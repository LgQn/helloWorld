sslocal -c /etc/shadowsocks.json
sudo /etc/init.d/privoxy restart
export http_proxy="127.0.0.1:8118"
export https_proxy="127.0.0.1:8118"
