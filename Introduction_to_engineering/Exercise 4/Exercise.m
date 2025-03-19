clear
close("all")
clc
%% Exercise 1
i1 = -180:1:180;
i2 = -2*pi:0.1:2*pi;
i3 = 0:0.2:50;
i4 = -5:0.1:5;
figure()
subplot(2,2,1)
h1 = plot(i1, sind(i1));
subplot(2,2,2)
h2 = plot(i2, cos(i2));
subplot(2,2,3)
h3 = plot(i3, log(i3));
subplot(2,2,4)
h4 = plot(i4, i4.^2);
set(h1, 'LineWidth', 4);
set(h2, 'LineStyle', '-.');
set(h3, 'Color', 'k');
%% Exercise 2
x = [-1, 1, 0];
y = [-1/sqrt(3), -1/sqrt(3), 2/sqrt(3)];
figure()
fill(x, y, 'r', 'EdgeColor', 'b', 'LineWidth', 4);
hold on;
text(0, 0, 'TROJUHOLNIK', 'HorizontalAlignment', 'center', 'FontSize', 8);
%% Exercise 3
[x, y] = meshgrid(-2:0.05:2, -2:0.05:2);
z = x.*exp(-x.^2-y.^2);
figure()
AX = gca;
AX.XLim = [-2.5, 2.5];
AX.YLim = [-2.5, 2.5];
S = surface(x, y, z);