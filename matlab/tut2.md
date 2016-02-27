# tut2

---

### 1)

_Save Q10 from tut1 in a .m file and call it_:

```matlab
plotsine
```

### 2)

_Load data and plot a histogram of the first row_:

```matlab
load('data.mat')
hist(X(1,:))
```

_Write a function to plot histograms of every row as subplots_:

```matlab
function plothists(data)
  numplots = length(data(:,1));
  n = ceil(sqrt(numplots));
  for i = 1:numplots
    subplot(n,n,i);
    hist(data(i,:));
  end
end
```

### 3)

_Write a function for Q9 from tut1_:

```matlab
function [sequence] = mysequence(upper)
  sequence = [];
  for value = 1:upper;
    if test(value)
      sequence = [sequence value];
    end
  end
end

function [result] = test(value)
  mag = floor(log10(value)) + 1;
  remainder = rem(value^2, 10^mag);
  result = (remainder == value);
end
```

### 4)

_Import data_:

```matlab
A = importdata('steps.csv')
B = importdata('activity_mix.csv')
```

_Compute step score_:

(Found in [step_scores.m](lifelogging/step_scores.m))

```matlab
lifelogging.step_scores(A)
```

_Compute activity score_:

(Found in [activity_scores.m](lifelogging/activity_scores.m))

```matlab
lifelogging.activity_scores(B)
```

_Compute the mean score per user_:

(Found in [mean_scores.m](lifelogging/mean_scores.m))

```matlab
lifelogging.mean_scores(users,scores)
```

_Create a struct array_:

(Found in [summarise_data.m](lifelogging/summarise_data.m) 

This solution currently does not take into account different user_ids in A and B.

```matlab
 S = lifelogging.summarise_data(A,B)
```

_Plot a scattergraph_:

```matlab
plot(S.steps, S.act)
```

### 5)

_Load an image and view it_:

```matlab
X = imread('image.jpg')
image(X)
```

Requires a toolbox for the rest of the question.
