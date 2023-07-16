export PATH=~/cc65/bin:$PATH
cp sdhrmaster.hdv sdhr.hdv
cc65 -I ~/cc65/include/ -t apple2enh -Osir -Cl src/sdhr.c -o build/sdhr.s
ca65 -t apple2enh --include-dir ~/cc65/asminc build/sdhr.s -o build/sdhr.o
ca65 -t apple2enh --include-dir ~/cc65/asminc src/sp_dispatch.s -o build/sp_dispatch.o
ld65 -t apple2enh --cfg-path ~/cc65/cfg/ --lib-path ~/cc65/lib/ -o sdhr build/sdhr.o build/sp_dispatch.o --lib apple2enh.lib -m mapfile -vm
java -jar ~/AppleCommander-linux64-gtk-1.5.0.jar -as sdhr.hdv SDHR BIN < sdhr

cc65 -I ~/cc64/include -t apple2enh -Osir -Cl src/borderset.c -o build/borderset.s
ca65 -t apple2enh --include-dir ~/cc65/asminc build/borderset.s -o build/borderset.o
ld65 -t apple2enh --cfg-path ~/cc65/cfg --lib-path ~/cc65/lib -o borderset build/borderset.o --lib apple2enh.lib -m mapfile -vm
java -jar ~/AppleCommander-linux64-gtk-1.5.0.jar -as sdhr.hdv BORDERSET BIN < borderset

cc65 -I ~/cc64/include -t apple2enh -Osir -Cl src/textset.c -o build/textset.s
ca65 -t apple2enh --include-dir ~/cc65/asminc build/textset.s -o build/textset.o
ld65 -t apple2enh --cfg-path ~/cc65/cfg --lib-path ~/cc65/lib -o textset build/textset.o --lib apple2enh.lib -m mapfile -vm
java -jar ~/AppleCommander-linux64-gtk-1.5.0.jar -as sdhr.hdv TEXTSET BIN < textset

cc65 -I ~/cc64/include -t apple2enh -Osir -Cl src/time_app.c -o build/time_app.s
ca65 -t apple2enh --include-dir ~/cc65/asminc build/time_app.s -o build/time_app.o
ld65 -t apple2enh --cfg-path ~/cc65/cfg --lib-path ~/cc65/lib -o time_app build/time_app.o --lib apple2enh.lib -m mapfile -vm
java -jar ~/AppleCommander-linux64-gtk-1.5.0.jar -as sdhr.hdv TIMEAPP BIN < time_app 



cp sdhr.hdv ~/shared/sdhr/
