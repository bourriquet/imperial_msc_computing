x = linspace(-5,5,101);
y = (sin(pi*x)./(pi*x));
y(isnan(y)) = 1;
figure;
plot(x,y,'g-')
