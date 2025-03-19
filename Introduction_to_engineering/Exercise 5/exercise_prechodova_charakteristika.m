clc
plot(out.tout, out.y)
title('Prechodová charakteristika systému')
xlabel('Čas [s]')
ylabel('y(t)')
grid on
axis([0 5 0 0.7])