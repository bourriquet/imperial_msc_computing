# tut1

---

### 1 - 4)

No coding needed.

### 5)

_Test if two matrices are equal_:

```matlab
all(all(D==E))
```

### 6)

No coding needed.

### 7)

_Numerical approximation of a vector_:

```matlab
v = sin([1:6].^2).*([1:6].^2)
```

_Round up for +ve values, round down for -ve values_:

```matlab
v2 = sign(v).*ceil(abs(v))
```

### 8)

_Create matrices with certain diagonals_:

```matlab
X = diag([1:5],1)
Y = diag([10:-1:6],-1)
M = X+Y
```

_Compute eigenvalues and eigenvectors_:

```matlab
[vec,val] = eig(M)
```

### 9)

_Find numbers that when squared are the last digits of their square_:

```matlab
find([([1:9] == ([1:9].^2 - (floor([1:9].^2 / 10)*10))) ...
([10:99] == ([10:99].^2 - (floor([10:99].^2 / 100)*100))) ...
([100:999] == ([100:999].^2 - (floor([100:999].^2 / 1000)*1000)))])
```

### 10)

_Plot two functions and decorate the plot_:

```matlab
x = linspace(0,5,101)
y = sin(x)
y2 = x - (x.^3/factorial(3)) + (x.^5/factorial(5))
figure
plot(x,y,'b-',x,y2,'r.')
title('sin(x) and 5th order approximation')
xlabel('x')
ylabel('y')
legend('y = sin(x)', 'y = x - (x^3/3!) + (x^5/5!)')
```

### 11)

_Plotting sinc(x)_:

```matlab
x = linspace(-5,5,101)
y = (sin(pi*x)./(pi*x))
y(isnan(y)) = 1
figure
plot(x,y,'g-')
```

_Plotting surface plot_:

```matlab
[X,Y] = meshgrid(-5:.1:5)
R = sqrt(X.^2 + Y.^2)
Z = sin(pi*R)./(pi*R)
Z(isnan(Z)) = 1
surf(X,Y,Z)
```
