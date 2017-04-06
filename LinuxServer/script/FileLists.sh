#/bin/bash

echo mkdir /var/penguin
mkdir /var/penguin\n
echo mkdir /var/penguin
mkdir /var/penguin/test\n

echo cp 小说.txt
cp ./小说.txt /var/penguin/test\n

echo mkdir /var/penguin/test/英语
mkdir /var/penguin/test/英语\n
echo cp ch01.pdf
cp ./ch01.pdf /var/penguin/test/英语\n

echo mkdir /var/penguin/test/gcc
mkdir /var/penguin/test/gcc\n
echo gcc.zip libevent-2.1.8-stable.tar.gz libstdc++-api.pdf
cp ./gcc.zip /var/penguin/test/gcc\n
cp ./libevent-2.1.8-stable.tar.gz /var/penguin/test/gcc\n
cp ./libstdc++-api.pdf /var/penguin/test/gcc\n

echo /var/penguin/test/image
mkdir /var/penguin/test/image\n
echo cp Lighthouse.jpg
cp ./Lighthouse.jpg /var/penguin/test/image\n

echo /var/penguin/test/文档
mkdir /var/penguin/test/文档\n
echo cp 期中测试提交模板.docx
cp ./期中测试提交模板.docx /var/penguin/test/文档\n

echo 创建完成
