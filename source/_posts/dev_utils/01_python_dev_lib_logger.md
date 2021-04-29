---
title: HEXO Hacker 主题中文说明
date: 2021/4/23
categories:
  - python
toc: true # 是否启用内容索引
---

---
### install lib 
---
~~~bash 
  pip install GitPython #在线安装会自动安装其依赖模块
~~~
---
### clone 
---
~~~bash 
  Repo.clone_from("git远程给仓库地址",to_path="将要克隆到的本地仓库地址")
~~~
---
### init
---
~~~bash 
  Repo.init(r"C:\Users\Icey\Desktop\aa") #aa为要初始化的本地仓库
~~~
---
### commit
---
~~~bash 
  repo = Repo(r"C:\Users\Icey\Desktop\aa") #获取本地仓库对象
  index = repo.index #获取本地仓库的暂存区对象
  #index.add(r'*') #将本地所有改动提交到暂存区
  index.add(['aaaa.txt']) #将aaaa.txt文件提交到暂存区
  index.commit("此次提交备注信息")
~~~
---
### branch 
---
~~~bash 
  repo.git.branch("dev") #新建dev分支
  repo.git.checkout("dev") #切换到dev分支
~~~

---
### demo
---
~~~bash 
  import os
  from git import Repo
  from git.repo.fun import is_git_dir

  class GitRepository(object):
    #初始化
    def __init__(self,local_path,repo_url,branch = 'master'):
      self.local_path = local_path
      self.repo_url = repo_url
      self.repo = None
      self.initial(repo_url,branch)
    def initial(self,repo_url,branch):
      #判断本地仓库存在否，不存在则新建一个
      if not os.path.exists(self.local_path):
        os.makedirs(self.local_path)
      git_local_path = os.path.join(self.local_path,".git")
      if not is_git_dir(git_local_path):
        self.repo = Repo.clone_from(repo_url,to_path = self.local_path,branch = branch)
      else:
      self.repo = Repo(self.local_path)
      
    #拉取远程代码
    def pull(self):
      self.repo.git.pull()
      
    #将本地提交推送到远程
    def push(self):
      self.repo.git.push('master')
      
    #切换分支
    def change_to branch(self,ch_branch):
      self.repo.git.checkout(ch_branch)
      
    #新建tag并推送远程
    def tags(self,new_tag,new_msg):
      self.repo.create_tag(new_tag,m = new_msg)
      self.repo.git.push('origin',new_tag)
      
  if __name__ == '__main__':
    local_path = input('请输入本地仓库地址：')
    repo_url = input('请输入远程仓库地址：')
    repo = GitRepository(local_path,repo_url)
    
    ch_branch = input("请输入要切换的分支名称:")
    repo.change_to_branch(ch_branch)
    repo.pull()
    
    new_tag = input("请输入新建的tag:")
    new_msg = input("请输入本次推送的备注信息：")
    repo.tags()
~~~
