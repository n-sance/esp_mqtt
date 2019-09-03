                    Установка и работа с драйвером для ESP
                    
                    
                    1.  Настраиваем ArduinoIDE, для этого в Файл - Настройки в поле «Дополнительные ссылки для Менеджера плат:»   вставляем строку:
                    "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
                    2.  Инструменты - Плата - Менеджеры плат: ищем и устанавливаем пакет "esp8266 by ESP8266 Community"
                    3.  В настройках выбираем плату "Generic ESP8266 Module"
                    4.  Настройки платы:   
                    Flash size: 512K(64 SPIFFS)
                    Flash mode: DIO
                    Upload using: Serial
                    Остальное можно оставить по умолчанию
                    4.5 Скачиваем и устанавливаем библиотеку ArduinoJSON
                    4.6 Заходим Скетч - Подключить библиотеку - Добавить ZIP библиотеку и выбираем файл pubsubclient.zip из папки с проектом.
                    5.  Открываем скетч, изменяем переменные SSID и Password для своего вайфая.
                    6.  Прошиваем(не забыть притянуть пин GP0 к земле), перезагружаем.  
                    В мониторе порта должны появиться сообщения: 
                    Connecting to <SSID>
                    Connected to <SSID>
                    Connected to MQTT
                    
                    


                                        Формат сообщений и протокол
                    
                    После того как установлено соединение с MQTT можно отправлять сообещния в следующем формате:  
                    
                    topic&message\n
                    
                    topic - имя топика, например: "dev/uuid/mp3/"
                    & - разделительный символ
                    message - сообщение для передачи на сервер, например: "{'temp: 30', 'voltage: 3.7'}"
                    
                    Если в качестве первого символа сообщения ввести "*", то кроме передачи на сервер, контроллер будет выполнять служебные команды. Каждой служебной команде присвоен собственный символ. Актуальный список служебных символов:
                    
                    "d" - переход в режим deep sleep
                    "s" -  переход в режим soft sleep(light sleep)
                    "m" - переход в режим modem sleep
                    "n" - переход в режим none sleep
                    
                    Пример сообщения, включающего режим глубокого сна: "dev/service/lowpower&*d"
                    
                                            Энергосбережение
                    
                    На данный момент самым стабильным режимом является deepsleep, остальные режимы либо не дают существенного энергосбережения, либо неконтроллируемо вырубаются сигналом reset от watchdog таймера, который невозможно игнорировать при работе внутри цикла(по крайней мере пока). 


                    
                                            Прием сообщений от MQTT


                    Прием сообщений возможен только от топика формата devices/uid/#



                    UPDATE:

                    При включении устройства устройство начинает отправлять в UART сообщения: "Waiting_config"
                    
                    В JSON нужно указать: Точки доступа и пароли к ним(SSID1 - SSID3, PASSWD1 - PASSWD3); MQTT: сервер, порт, UID и пароль; 9 топиков для подписки на сообщения; timeout на переподключение к WiFi и отправку сообщения "Waiting_config" в секундах. Сейчас происходит автоматическое переподключение к WiFi точкам прописанным в JSON с интервалом в 4 секунды. 

                    Пример сообщения для отправки:


                    {"wificonfig":[{"ssid":"Redmi 4X","passwd":"199508021"},{"ssid":"Redmi 4X","passwd":"199508021"},{"ssid":"Redmi3","passwd":"123456"},{"ssid":"Murzik","passwd":"19871987"}],"mqtt":[{"server":"super-carpenter.cloudmqtt.com"},{"port":"18028"},{"mqtt_pass":"ssvwYnWja9uww80kHuvVxv27pVWk1QGz"},{"mqtt_uid":"3fb985fd-2030-4e4b-8ddb-8f55fb2731b9"}],"mqtt_topics1":[{"mqtt_subscribe_topic":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/#"},{"mqtt_topic_1":"/devices/uuid/panel/ping"},{"mqtt_topic_volume_set":"/devices/mqtt_uid/device/volume/set"},{"mqtt_topic_audio_start":"/devices/mqtt_uid/device/audio/start"}],"mqtt_topics2":[{"mqtt_topic_audio_pause":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/audio/pause"},{"mqtt_topic_audio_play":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/audio/play"},{"mqtt_topic_audio_stop":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/audio/stop"},{"mqtt_topic_question_play":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/game/question/play"}],"mqtt_topics3":[{"mqtt_topic_phrase_play":"/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/game/phrase/play"}],"timeout":5}\n



                    При первом подключении к WiFi точки будет выведено сообщение Connecting to <WiFI>. И далее Connected to MQTT в случае успеха.  При последующих переподключениях к той же точке будет сразу выведено Connected to MQTT. После этого возможна повторная отправка JSON с настройками. Для этого нужно отправить сообщение на любой топик с служебным символом "j". Например: device/service&j\n   
                    Устройство выполнит перезагрузку и опять начнет посылать сообщение о запросе настроек.

