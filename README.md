# gl-lab

## 개발 환경

Ubuntu 22.04.2 LTS (`x86_64`)

```
$ sudo apt update && sudo apt install build-essential git
$ sudo apt install libgles2-mesa-dev libglvnd-dev libx11-dev libxrandr-dev \
    libxi-dev libxcursor-dev libxinerama-dev libxkbcommon-dev mesa-utils
```

## 빌드 방법

```console
$ git clone https://github.com/team-iwd/gl-lab && cd gl-lab
```

### GNU/Linux ➡️ GNU/Linux

```console
$ make
```

### GNU/Linux ➡️ Windows

```console
$ make -f Makefile.mingw
```