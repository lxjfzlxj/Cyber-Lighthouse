## resolver 执行格式

`./resolver [FILENAME]`

解析 FILENAME 文件中的 DNS 二进制报文

例如：
`./resolver testcase1.bin`

## generator 执行格式

`./generator [TYPE] [DOMAINNAME] [FILENAME]`

生成 TYPE 类型的查询域名为 DOMAINNAME 的 DNS 二进制报文，将结果保存在 FILENAME 中。

例如：
`./generator A dns.msftncsi.com outputDNS1.bin`