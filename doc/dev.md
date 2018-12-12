#2018-12-06

### h264 정보 구하기

ffmpeg -i 20181130104010.mp4 -vcodec copy -vbsf h264_mp4toannexb -an of.h264

ngx_rtmp_hls_video