# arduino-watertank
A project for water tank measurement

Si quieres saber cómo funciona el proyecto, puedes ver el video aqui: 
https://youtu.be/yYn_Z0BiK4Q

(Disculpas por la demora a todos los que pidieron el código, mi anterior web quedó fuera de línea y con ella el código. Ahora, teniendo el código en github no volverá a pasar ese percance). Alguna duda o pregunta escribir a dwonga@gmail.com). Éxitos!

Aquí estan disponibles dos versiones del mismo programa. La versión 1 es la del video youtube y en la versión 2, se hicieron los siguientes cambios:
- Sensor a prueba de agua (JSN-SR04T), con el mismo comportamiento/uso que el sensor SNR-04, que es el que mostré en el video.
- Lolin v3 ESP8266 en lugar del arduino uno. Esto permite que pueda mostrar la información en una página web en lugar de un LCD.

Los requerimientos de la versión dos son: 
- Dos sensores JSN-SR04T (puede trabajar con uno solo, si solo tienes un tanque de agua)
https://www.aliexpress.com/item/4001111845577.html?spm=a2g0o.productlist.0.0.62c11421J924eN&s=p&ad_pvid=202008301640045026365450573250027294546_1&algo_pvid=9a5c3ad0-2240-4033-919c-59bd97830a35&algo_expid=9a5c3ad0-2240-4033-919c-59bd97830a35-0&btsid=0ab6fab215988308041497889ec192&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_
- NodeMCU (versión v3 Lolin):
https://www.aliexpress.com/item/32951391024.html?spm=a2g0o.productlist.0.0.bd8852e4aniPb7&algo_pvid=09b6a731-60d0-4e66-9d4f-7524896e5e74&algo_expid=09b6a731-60d0-4e66-9d4f-7524896e5e74-0&btsid=0ab50f6115988310496925215e0ca8&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_

La versión 1 requiere:
- Sensor SNR-04 o JSN-SR04T (dos, uno para tanque superior, otro para tanque inferior. Si solo tienes un tanque descarta todo lo que diga upper tank)
- Arduino Uno
- Crystal led 16x2 caracteres estándar.

