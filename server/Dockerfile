FROM mlcollard/linux-dev

WORKDIR server

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y \
    build-essential \
    postgresql-client \
    libpq-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libavdevice-dev \
    libavfilter-dev \
    libcurl4-openssl-dev

# Создание директории проекта и копирование файлов
RUN mkdir -p /app
COPY . /app

# Установка зависимостей проекта
RUN cd /app && \
    make install

# Запуск приложения
CMD ["./app"]
