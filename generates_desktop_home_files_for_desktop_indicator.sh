mkfifo ~/.desktop_indicator.fifo
echo "echo d\$1 > /home/boris/.desktop_indicator.fifo" > ~/.desktop_indicator__desktop
echo "echo mb > /home/boris/.desktop_indicator.fifo" > ~/.desktop_indicator__mode_backward
echo "echo mf > /home/boris/.desktop_indicator.fifo" > ~/.desktop_indicator__mode_forward
