import requests
from lxml import etree

#发送给谁
url = 'https://dldl1.nsbuket.cc/xiaoshuo/douluodalu/1.html'
while True:

  #伪装自己
  headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36 Edg/123.0.0.0'
  }

  resp = requests.get(url, headers=headers)

  resp.encoding = 'utf-8'
  #print(resp.text)

  e = etree.HTML(resp.text)
  info ='\n'.join (e.xpath('//div[@class="m-post"]/p/text()'))
  title = e.xpath('//h1/text()')[0]
  url = f'https://dldl1.nsbuket.cc/{e.xpath("//td[2]/a/@href")[0]}'
  #print(info)
  #print(title)
  #保存
  with open('斗罗大陆.txt', 'a', encoding='utf-8') as f:
    f.write(title + '\n\n'+info + '\n\n')
