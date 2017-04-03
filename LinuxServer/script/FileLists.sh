#/bin/bash

echo mkdir /var/penguin
mkdir /var/penguin
echo mkdir /var/penguin
mkdir /var/penguin/test

echo cp 小说.txt
cp ./小说.txt /var/penguin/test

echo mkdir /var/penguin/test/英语
mkdir /var/penguin/test/英语
echo cp ch01.pdf
cp ./ch01.pdf /var/penguin/test/英语

echo mkdir /var/penguin/test/gcc
mkdir /var/penguin/test/gcc
echo gcc.zip libevent-2.1.8-stable.tar.gz libstdc++-api.pdf
cp ./gcc.zip /var/penguin/test/gcc
cp ./libevent-2.1.8-stable.tar.gz /var/penguin/test/gcc
cp ./libstdc++-api.pdf /var/penguin/test/gcc

echo /var/penguin/test/image
mkdir /var/penguin/test/image
echo cp Lighthouse.jpg
cp ./Lighthouse.jpg /var/penguin/test/image

echo /var/penguin/test/文档
mkdir /var/penguin/test/文档
echo cp 期中测试提交模板.docx
cp ./期中测试提交模板.docx /var/penguin/test/文档

echo 创建完成
