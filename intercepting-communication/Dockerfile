# syntax=docker/dockerfile:1

FROM python:3.13-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        iptables \
        iproute2 && \
    rm -rf /var/lib/apt/lists/*

ADD --chown=0:0 --chmod=6755 http://github.com/pwncollege/exec-suid/releases/latest/download/exec-suid /usr/bin/exec-suid

RUN pip install --no-cache-dir \
    flask \
    psutil \
    requests \
    https://github.com/pwncollege/dojjail/archive/refs/heads/master.zip \
    https://github.com/secdev/scapy/archive/refs/heads/master.zip

