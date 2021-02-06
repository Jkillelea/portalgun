OPENOCD="$HOME/.platformio/packages/tool-openocd/bin/openocd"
$OPENOCD -d2 \
    -s /home/jacob/.platformio/packages/tool-openocd/scripts \
    -f board/st_nucleo_l4.cfg \
    -c "program {build/nucleo32l4_spimaster.elf} verify reset; shutdown;"
