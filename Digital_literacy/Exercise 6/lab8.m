%Shishmarev Viktor

%% Exercise 2
p1 = [-1 6 -5];
p2 = [1 3 0];
pn = conv(p1, p2)
roots(pn)

%% Exercise 3
i1 = -4:0.1:4;
i2 = -2:0.1:2;
figure()
subplot(2, 1, 1)
hold on
plot(i1, polyval(p1, i1), "r")
plot(i1, polyval(p2, i1), "g")
plot(i1, polyval(pn, i1), "b")
subplot(2, 1, 2)
grid on
hold on
ax = gca;
ax.XAxisLocation = "origin";
ax.YAxisLocation = "origin";
plot(i2, polyval(p1, i2), "r")
plot(i2, polyval(p2, i2), "g")
plot(i2, polyval(pn, i2), "b")

%% Exercise 4
%close("all")
i1 = -2:0.1:2;
i2 = -2:0.4:2;
figure()
hold on
plot(i1, polyval(pn, i1), "r")
stem(i2, polyval(pn, i2), "b")

%% Exercise 5
%close("all")
i1 = -2:0.1:2;
i2 = -2:0.4:2;
pn1 = diff(polyval(pn, i1))/0.1;
pn2 = diff(polyval(pn, i2))/0.4;
figure()
hold on
plot(i1(:,1:length(pn1)), pn1, "r")
stem(i2(:,1:length(pn2)), pn2, "b")