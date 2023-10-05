## DNSquery 执行格式

`./DNSquery [@IP:PORT] NAME Y/N`

表示查询的 DNS 服务器 IP 及端口为 IP:PORT（不指定默认为 8.8.8.8:53），NAME 为待查询的域名，Y/N 表示是否使用递归查询。

例子：
`./DNSquery @8.8.8.8:53 www.baidu.com Y`