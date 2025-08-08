Для работы сервера необходимы пакеты - redis, hiredis, spdlog

Пример для Ububtu
```
sudo apt install libspdlog-dev
                 redis-server
                 libhiredis-dev
```

Для запуска com портов, необходимо ввести в файл .env выведенные порты
```
socat -d -d pty,raw,echo=0 pty,raw,echo=0
```

Для запуска redis
```
redis-server
```

