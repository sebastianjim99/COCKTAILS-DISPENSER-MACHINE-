# COCKTAILS DISPENSER MACHINE
This project contains all the information to create an intelligent machine capable of dispensing four different cocktails by implementing the Curiosity Nano Development board PIC16F15244 and other electronic components easily available.

# What's the use?
This system allows to dispense 4 drinks with different flavors and proportions that can be displayed on a 20x4 LCD screen by means of buttons, the preferred choice is made.

#  Information about PIC16F15244
<p> •<a href= "https://www.microchip.com/wwwproducts/en/PIC16F15244"  target="_blank">PIC16F15244 </a> </p>
<p>• <a href= "http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15244-Curiosity-Nano-Hardware-User-Guide-DS50003045A.pdf"  target="_blank">Curiosity-Nano-Hardware-User-Guide</a>  </p>
<p> • <a href= "http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15213-14-23-24-43-44-Data-Sheet-DS40002195B.pdf"  target="_blank">PIC16F15213-14-23-24-43-44-Data-Sheet </a> </p>
<p> • <a href= "https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15244_Curiosity_Nano_Schematics.pdf"   target="_blank">PIC16F15244_Curiosity_Nano_Schematics.pdf </a> </p>

# Software
<p> •<a href= "https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide" target="_blank">MPLAB-X-IDE</a> </p>
<p>•  <a href= "https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-ecosystem-downloads-archive" target="_blank"> MPLAB XC8 </a> </p>

# Necessary materials
<p> • wooden structure </p>

![wooden structure](https://user-images.githubusercontent.com/80067586/119345046-031b4a80-bc5e-11eb-9c2d-351f99cf705d.jpg)


<p> • PIC16F15224</p>

![PIC16F15244](https://user-images.githubusercontent.com/80067586/118411455-4cfea200-b65a-11eb-9ae4-bb4275377dec.png)

<p> •  4  <a href="https://articulo.mercadolibre.com.co/MCO-545623259-mini-bomba-de-agua-3v-12v-arduino-acuario-_JM?matt_tool=99279475&matt_word=&matt_source=google&matt_campaign_id=11584883659&matt_ad_group_id=115595145969&matt_match_type=&matt_network=g&matt_device=c&matt_creative=478554425908&matt_keyword=&matt_ad_position=&matt_ad_type=pla&matt_merchant_id=116847301&matt_product_id=MCO545623259&matt_product_partition_id=311407048681&matt_target_id=pla-311407048681&gclid=CjwKCAjwhYOFBhBkEiwASF3KGVqKQa5jqAIFlsY4M6TgXeG_9Y0eAMzziLuogY2b7mwjIfVgFeqwpxoCUusQAvD_BwE" target="_blank">liquid motors </a> with a voltage range between 9-12v </p>

![motor](https://user-images.githubusercontent.com/80067586/118411520-a070f000-b65a-11eb-9a2b-62c22cb361c9.jpg)

<p>• <a href= "https://articulo.mercadolibre.com.co/MCO-540590452-cinta-led-3528-12v-5mts-siliconada-tira-luz-leds-fuente-_JM?searchVariation=46050582191#searchVariation=46050582191&position=7&search_layout=stack&type=item&tracking_id=f24ae44c-6730-4047-9268-c3f183562990" target="_blank">led strip</a> of different colors </p>

![tira_led](https://user-images.githubusercontent.com/80067586/118411590-e0d06e00-b65a-11eb-8f76-88d59be46161.jpg)

<p>• 5-channel 5v <a href= "https://articulo.mercadolibre.com.co/MCO-450495614-modulo-rele-4-canales-relay-arduino-5v-microcontrolador-pic-_JM#position=8&search_layout=stack&type=pad&tracking_id=e3a3ac68-22ad-48f9-895f-ef01dc14511c&is_advertising=true&ad_domain=VQCATCORE_LST&ad_position=8&ad_click_id=ODg2MGU1ZmEtN2VmNC00YWRkLWI4MmItYTk0NmE3NjU5MjVm" target="_blank">relay</a> </p>

![rele](https://user-images.githubusercontent.com/80067586/118411613-fcd40f80-b65a-11eb-9ac9-2d8438e9d4c4.jpg)


<p>• Adapter 12v 1A </p>

![cargador ](https://user-images.githubusercontent.com/80067586/118411722-a5826f00-b65b-11eb-9d74-4ef92be8d855.jpg)


<p>• <a href= "https://ferretronica.com/products/pantalla-display-lcd-4x20-azul-con-backlight?variant=12507901689949" target="_blank">lcd</a> display 4x20 </p>

![lcd](https://user-images.githubusercontent.com/80067586/118411657-386ed980-b65b-11eb-9776-75b2dbb37d45.jpg)

<p>• Dc-dc  <a href= "https://articulo.mercadolibre.com.co/MCO-600862443-fuente-dc-dc-lm2596-buck-converter-step-down-3a-voltaje-adj-_JM#position=7&search_layout=stack&type=item&tracking_id=a6d063ee-11fd-44a8-9150-0b5ddeb0d40a" target="_blank">source</a> </p>

<p>• Micro-USB to USB 2.0 cable </p>

<p>• Protoboard </p>

<p>• Jumpers </p>

<p>• Small hose </p>

<p>• Push button </p>

# How to install it?

For its installation, 4 different beverage bottles are required, which are located at the back of the machine with suction hoses. Then, it is necessary to supply power through a 12V charger in this way the LCD screen and the buttons ready for selection are initialized.

# How to use?

A glass is placed in the center of the device, then the menu appears on the LCD and a drink is selected using the buttons. Pressing a button will turn on a suction motor for a certain liquid and in turn a sequence of LEDs with a certain waiting time; then another motor of the complementary liquid is activated and its respective waiting sequence. And in this way the drink falls into a glass located in the center and a message will appear on the LCD screen to remove the glass.

# Conclusions

Through the development of this project, it was possible to solve the problem posed, by means of a machine capable of dispensing drinks supported by an LCD screen and buttons, implementing a PIC16F15244 MCU that controls all the processes carried out by the machine and its components.
Due to the limited pins and the series operation of the MCU, different interruptions were implemented in the time that were achieved with the use of the sequences of the led strips and delays between them.

# Schematic circuit

![Schematic circuit](https://user-images.githubusercontent.com/80067586/119347070-9eadba80-bc60-11eb-882d-6c8f73d66ce2.png)

