---
title: HEXO Hacker 主题中文说明
date: 2021/4/23
categories:
  - python
toc: true # 是否启用内容索引
---

---
### demo 
---
~~~bash
import argparseparser = argparse.ArgumentParser('introduce how to use')#创建一个解析器
parser.add_argument('integers', #必选参数                            
                    metavar='number', #'usage'显示成'number'                    
                    type=int, #整形变量                    
                    nargs='+', #至少有一个参数值                    
                    help='an inter for the accumulator')#帮助文档显示
parser.add_argument('--test-para',#可选参数                    
                    required=False,#是否必须携带                    
                    default='this is just a test',#默认值                    
                    help='wirte some instruction here')#帮助文档
args = parser.parse_args()#解析
print(args)
~~~ 
