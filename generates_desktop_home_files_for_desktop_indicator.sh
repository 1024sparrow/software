rm ~/.desktop_indicator.fifo
mkfifo ~/.desktop_indicator.fifo
echo "echo d\$1 > /home/user/.desktop_indicator.fifo" > ~/.desktop_indicator__desktop
echo "echo mb > /home/user/.desktop_indicator.fifo" > ~/.desktop_indicator__mode_backward
echo "echo mf > /home/user/.desktop_indicator.fifo" > ~/.desktop_indicator__mode_forward
