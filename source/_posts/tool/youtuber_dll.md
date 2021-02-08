---
title: Youtube-dl youtube视频批量下载
categories:
- tools
date: 2021/2/8
toc: true # 是否启用内容索引
---

### what is Youtube-dl ？
--- 
Youtube-dl 是一个自由开源的命令行视频下载工具，可以用来从 Youtube 等类似的网站上下载视频，目前它支持的网站除了 Youtube 还有 Facebook、Dailymotion、Google Video、Yahoo 等等。它构架于 pygtk 之上，需要 Python 的支持来运行。它支持很多操作系统，包括 Windows、Mac 以及 Unix。Youtube-dl 还有断点续传、下载整个频道或者整个播放清单中的视频、添加自定义的标题、代理等等其他功能。

~~~bash
    sudo apt-get update -y
    sudo apt-get upgrade -y
    sudo apt-get install curl -y
    curl -L https://yt-dl.org/latest/youtube-dl -o /usr/bin/youtube-dl
    chmod 755 /usr/bin/youtube-dl
~~~
~~~bash
    # 显示所有视频格式
    youtube-dl -F https://www.youtube.com/watch?v=j_JgXJ-apXs  

    [info] Available formats for j_JgXJ-apXs:
    format code  extension  resolution note
    139          m4a        audio only DASH audio   56k , m4a_dash container, mp4a.40.5@ 48k (22050Hz), 756.44KiB
    249          webm       audio only DASH audio   56k , opus @ 50k, 724.28KiB
    250          webm       audio only DASH audio   69k , opus @ 70k, 902.75KiB
    171          webm       audio only DASH audio  110k , vorbis@128k, 1.32MiB
    251          webm       audio only DASH audio  122k , opus @160k, 1.57MiB
    140          m4a        audio only DASH audio  146k , m4a_dash container, mp4a.40.2@128k (44100Hz), 1.97MiB
    278          webm       256x144    144p   97k , webm container, vp9, 24fps, video only, 1.33MiB
    160          mp4        256x144    DASH video  102k , avc1.4d400c, 24fps, video only, 731.53KiB
    133          mp4        426x240    DASH video  174k , avc1.4d4015, 24fps, video only, 1.36MiB
    242          webm       426x240    240p  221k , vp9, 24fps, video only, 1.74MiB
    134          mp4        640x360    DASH video  369k , avc1.4d401e, 24fps, video only, 2.90MiB
    243          webm       640x360    360p  500k , vp9, 24fps, video only, 4.15MiB
    135          mp4        854x480    DASH video  746k , avc1.4d401e, 24fps, video only, 6.11MiB
    244          webm       854x480    480p  844k , vp9, 24fps, video only, 7.27MiB
    247          webm       1280x720   720p 1155k , vp9, 24fps, video only, 9.21MiB
    136          mp4        1280x720   DASH video 1300k , avc1.4d401f, 24fps, video only, 9.66MiB
    248          webm       1920x1080  1080p 1732k , vp9, 24fps, video only, 14.24MiB
    137          mp4        1920x1080  DASH video 2217k , avc1.640028, 24fps, video only, 15.28MiB
    17           3gp        176x144    small , mp4v.20.3, mp4a.40.2@ 24k
    36           3gp        320x180    small , mp4v.20.3, mp4a.40.2
    43           webm       640x360    medium , vp8.0, vorbis@128k
    18           mp4        640x360    medium , avc1.42001E, mp4a.40.2@ 96k
    22           mp4        1280x720   hd720 , avc1.64001F, mp4a.40.2@192k (best)
~~~

然后使用 -f 指定你想要下载的格式，如下所示：
~~~bash
    youtube-dl -f 18 https://www.youtube.com/watch?v=j_JgXJ-apXs

    [youtube] j_JgXJ-apXs: Downloading webpage
    [youtube] j_JgXJ-apXs: Downloading video info webpage
    [youtube] j_JgXJ-apXs: Extracting video information
    [youtube] j_JgXJ-apXs: Downloading MPD manifest
    [download] Destination: B.A. PASS 2 Trailer no 2 _ Filmybox-j_JgXJ-apXs.mp4
    [download] 100% of 6.90MiB in 00:47
~~~

### 下载音频 
~~~bash
    youtube-dl https://www.youtube.com/watch?v=j_JgXJ-apXs -x --audio-format mp3
~~~

### 下载视频
~~~bash
    youtube-dl -citw https://www.youtube.com/channel/UCatfiM69M9ZnNhOzy0jZ41A
~~~

### 指定代理
~~~bash
    youtube-dl --proxy http://proxy-ip:port https://www.youtube.com/watch?v=j_JgXJ-apXs
~~~

### youtube-list
若想一条命令下载多个 Youtube 视频，那么首先把所有要下载的 Youtube 视频 URL 存在一个文件中（假设这个文件叫 youtube-list.txt），然后运行下面命令：
~~~bash
    youtube-dl -a youtube-list.txt
~~~

