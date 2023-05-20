FROM mlcollard/linux-dev

WORKDIR server

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y \
    build-essential \
    libpq-dev \
    postgresql-server-dev-all \
    libgtest-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libavdevice-dev \
    libavfilter-dev \
    libcurl4-openssl-dev

COPY . .

RUN cmake ./
RUN make

CMD ["./server"]
