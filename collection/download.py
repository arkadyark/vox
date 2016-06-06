# This file will grab all of the youtube links specified and download them to /data

from __future__ import unicode_literals
import youtube_dl

yt_links = []
with open(links_file) as f:
  for line in f:
    yt_links.append(line)
  

# Define output filename template, specify to use .wav format
ydl_opts = {}
with youtube_dl.YoutubeDL(ydl_opts) as ydl:
    ydl.download(yt_links)
